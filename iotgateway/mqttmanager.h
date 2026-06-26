#ifndef MQTTMANAGER_H
#define MQTTMANAGER_H

#include <QObject>
#include <QMqttClient>
#include <QMqttTopicName>
#include "sensordata.h"

/**
 * 基于 Qt MQTT 模块的 MQTT 管理器
 * 负责连接 Broker、发布传感器数据、接收控制指令
 */
class MqttManager : public QObject
{
    Q_OBJECT
public:
    explicit MqttManager(const QString &host, quint16 port,
                         QObject *parent = nullptr);
    ~MqttManager();

    // 连接 MQTT Broker（异步）
    void connectToHost();

public slots:
    // 发布传感器数据（由采集线程信号触发）
    void publishSensorData(const SensorData &data);

signals:
    // 发送给控制页面的指令信号（保持与 Paho 版完全一致）
    void ledCommand(const QString &cmd);     // "on" 或 "off"
    void buzzerCommand(const QString &cmd);  // "on" 或 "off"

private slots:
    // Qt MQTT 事件回调
    void onConnected();
    void onMessageReceived(const QByteArray &message,
                           const QMqttTopicName &topic);

private:
    QMqttClient *m_client;   // Qt MQTT 客户端对象
};

#endif // MQTTMANAGER_H
