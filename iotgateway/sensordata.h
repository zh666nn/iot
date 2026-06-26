#ifndef SENSORDATA_H
#define SENSORDATA_H

#include <QDateTime>

struct SensorData {
    qreal temperature = 0.0;
    qreal humidity    = 0.0;
    int   smoke       = 0;
    bool  pir         = false;
    QDateTime timestamp;
};

#endif // SENSORDATA_H
