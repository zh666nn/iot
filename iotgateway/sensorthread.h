#ifndef SENSORTHREAD_H
#define SENSORTHREAD_H

#include <QThread>
#include "sensordata.h"

class SensorThread : public QThread
{
    Q_OBJECT
public:
    explicit SensorThread(QObject *parent = nullptr);
    void stop();

signals:
    void newSensorData(const SensorData &data);

protected:
    void run() override;

private:
    bool m_running;
};

#endif // SENSORTHREAD_H
