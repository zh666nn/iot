#include "sensorthread.h"
#include <QtGlobal>
#include <QDateTime>
#include <QThread>

SensorThread::SensorThread(QObject *parent)
    : QThread(parent), m_running(true)
{
    qsrand(QDateTime::currentMSecsSinceEpoch());
}

void SensorThread::stop()
{
    m_running = false;
    quit();
    wait();
}

void SensorThread::run()
{
    while (m_running) {
        SensorData data;
        data.temperature = 20.0 + (qrand() % 150) / 10.0;   // 20.0 ~ 34.9
        data.humidity    = 40.0 + (qrand() % 400) / 10.0;   // 40.0 ~ 79.9
        data.smoke       = 50 + qrand() % 200;              // 50 ~ 249
        data.pir         = (qrand() % 2 == 1);
        data.timestamp   = QDateTime::currentDateTime();

        emit newSensorData(data);
        QThread::sleep(5);   // 每5秒采集一次
    }
}
