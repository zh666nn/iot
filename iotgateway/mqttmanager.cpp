#include "mqttmanager.h"
#include <QJsonObject>
#include <QJsonDocument>
#include <QDebug>
#include<QTimer>
MqttManager::MqttManager(const QString &host, quint16 port, QObject *parent)
    : QObject(parent)
{

    m_client = new QMqttClient(this);
    m_client->setHostname(host);
    m_client->setPort(port);

    connect(m_client, &QMqttClient::connected, this, &MqttManager::onConnected);
    connect(m_client, &QMqttClient::messageReceived, this, &MqttManager::onMessageReceived);

    // 处理连接错误
    connect(m_client, &QMqttClient::errorChanged, this, [this](QMqttClient::ClientError error) {
        if (error != QMqttClient::NoError) {
            qWarning() << "MQTT 连接错误:" << error;
            // 可在此处添加重连逻辑（例如延迟 3 秒后重试）
            QTimer::singleShot(3000, this, &MqttManager::connectToHost);
        }
    });
}


MqttManager::~MqttManager()
{
    if (m_client->state() != QMqttClient::Disconnected) {
        m_client->disconnectFromHost();
    }
}

void MqttManager::connectToHost()
{
    if (m_client->state() == QMqttClient::Connected) {
        qDebug() << "MQTT 已连接，无需重复连接";
        return;
    }
    qDebug() << "正在连接 MQTT Broker:" << m_client->hostname() << m_client->port();
    m_client->connectToHost();
}

void MqttManager::onConnected()
{
    qDebug() << "MQTT 已连接，订阅控制主题";
    // 订阅两个控制主题，QoS 为 0
    m_client->subscribe(QMqttTopicFilter("home/led/set"), 0);
    m_client->subscribe(QMqttTopicFilter("home/buzzer/set"), 0);
}

void MqttManager::onMessageReceived(const QByteArray &message,
                                    const QMqttTopicName &topic)
{
    QString payload = QString::fromUtf8(message).toLower().trimmed();
    qDebug() << "收到 MQTT 消息:" << topic.name() << "->" << payload;

    if (topic.name() == "home/led/set") {
        emit ledCommand(payload);
    } else if (topic.name() == "home/buzzer/set") {
        emit buzzerCommand(payload);
    }
}

void MqttManager::publishSensorData(const SensorData &data)
{
    // 构造 JSON
    QJsonObject obj;
    obj["temp"] = data.temperature;
    obj["humidity"] = data.humidity;
    obj["smoke"] = data.smoke;
    obj["pir"] = data.pir ? 1 : 0;
    QJsonDocument doc(obj);
    QByteArray payload = doc.toJson(QJsonDocument::Compact);

    // 发布到主题 home/sensors，QoS=0，不保留
    m_client->publish(QMqttTopicName("home/sensors"),
                      payload, 0, false);
}
