#include "databasemanager.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include<QFileInfo>
DatabaseManager::DatabaseManager(const QString &dbName, QObject *parent)
    : QObject(parent)
{
    // 添加 SQLite 数据库驱动
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(dbName);

    if (!m_db.open()) {
        qFatal("无法打开数据库: %s", qPrintable(dbName));
        return;
    }
    QFileInfo info(dbName);
       qDebug() << "数据库文件绝对路径：" << info.absoluteFilePath();
    // 创建数据表（如果不存在）
    QSqlQuery query(m_db);
    QString createSql = "CREATE TABLE IF NOT EXISTS sensor_data ("
                            "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                            "timestamp DATETIME DEFAULT CURRENT_TIMESTAMP, "
                            "type TEXT NOT NULL, "
                            "value REAL NOT NULL)";
    if (!query.exec(createSql)) {
            qFatal("建表失败: %s", qPrintable(query.lastError().text()));
        } else {
            qDebug() << "数据库表 sensor_data 已就绪";
    }
}

DatabaseManager::~DatabaseManager()
{
    m_db.close();
}
void DatabaseManager::saveSensorData(const SensorData &data)
{
    QSqlQuery query(m_db);
    // 修改 SQL，显式插入 timestamp
    query.prepare("INSERT INTO sensor_data (type, value, timestamp) VALUES (:type, :value, :timestamp)");

    struct {
        QString type;
        qreal   value;
    } entries[] = {
        {"temperature", data.temperature},
        {"humidity",    data.humidity},
        {"smoke",       static_cast<qreal>(data.smoke)},
        {"pir",         data.pir ? 1.0 : 0.0}
    };

    for (const auto &e : entries) {
        query.bindValue(":type",  e.type);
        query.bindValue(":value", e.value);
        query.bindValue(":timestamp", data.timestamp.toString("yyyy-MM-dd hh:mm:ss"));  // 使用 Qt 获取的时间
        if (!query.exec()) {
            qWarning() << "插入失败:" << query.lastError().text();
        }
    }
}

QList<SensorData> DatabaseManager::queryData(const QString &type,
                                             const QDateTime &from,
                                             const QDateTime &to)
{
    QList<SensorData> result;
    QSqlQuery query(m_db);
    query.prepare("SELECT timestamp, value FROM sensor_data "
                  "WHERE type = :type AND timestamp BETWEEN :from AND :to "
                  "ORDER BY timestamp ASC");
    query.bindValue(":type", type);
    query.bindValue(":from", from.toString("yyyy-MM-dd hh:mm:ss"));
    query.bindValue(":to",   to.toString("yyyy-MM-dd hh:mm:ss"));

    if (!query.exec()) {
        qWarning() << "查询失败:" << query.lastError().text();
        return result;
    }

    while (query.next()) {
        SensorData d;
        d.timestamp = query.value(0).toDateTime();
        qreal val = query.value(1).toReal();

        // 仅填充本次查询类型对应的字段，其他字段为默认值
        if (type == "temperature")       d.temperature = val;
        else if (type == "humidity")     d.humidity = val;
        else if (type == "smoke")        d.smoke = static_cast<int>(val);
        else if (type == "pir")          d.pir = (val > 0.5);

        result.append(d);
    }
    return result;
}
