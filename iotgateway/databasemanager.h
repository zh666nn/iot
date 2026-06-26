#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QObject>
#include <QSqlDatabase>
#include <QDateTime>
#include <QList>
#include "sensordata.h"

class DatabaseManager : public QObject
{
    Q_OBJECT
public:
    explicit DatabaseManager(const QString &dbName, QObject *parent = nullptr);
    ~DatabaseManager();

public slots:
    // 保存一次完整的传感器数据
    void saveSensorData(const SensorData &data);

    // 查询指定类型和时间范围的数据
    QList<SensorData> queryData(const QString &type,
                                const QDateTime &from,
                                const QDateTime &to);

private:
    QSqlDatabase m_db;
};

#endif // DATABASEMANAGER_H
