#ifndef REALTIMEPAGE_H
#define REALTIMEPAGE_H

#include <QWidget>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QDateTimeAxis>
#include <QtCharts/QValueAxis>
#include "sensordata.h"

QT_CHARTS_USE_NAMESPACE

namespace Ui { class RealtimePage; }

class RealtimePage : public QWidget
{
    Q_OBJECT
public:
    // 不再需要 DatabaseManager 参数
    explicit RealtimePage(QWidget *parent = nullptr);
    ~RealtimePage();

public slots:
    // 接收 SensorThread 传来的数据，更新标签和曲线
    void updateData(const SensorData &data);

private:
    Ui::RealtimePage *ui;
    QLineSeries *tempSeries;
    QChart *chart;
    QDateTimeAxis *axisX;
    QValueAxis *axisY;
    // 删除了：QTimer *timer
    // 删除了：DatabaseManager *m_dbManager
};

#endif // REALTIMEPAGE_H
