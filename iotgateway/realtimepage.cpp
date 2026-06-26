#include "realtimepage.h"
#include "ui_realtimepage.h"
#include <QDateTime>
#include<QDebug>
RealtimePage::RealtimePage(QWidget *parent) :
    QWidget(parent), ui(new Ui::RealtimePage)
{
    ui->setupUi(this);

    // 初始化图表
    tempSeries = new QLineSeries;
    chart = new QChart;
    chart->addSeries(tempSeries);
    chart->setTitle("温度变化曲线");

    axisX = new QDateTimeAxis;
    axisX->setFormat("hh:mm:ss");
    axisY = new QValueAxis;
    axisY->setRange(15, 40);

    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY, Qt::AlignLeft);
    tempSeries->attachAxis(axisX);
    tempSeries->attachAxis(axisY);

    ui->chartview->setChart(chart);
    ui->chartview->setRenderHint(QPainter::Antialiasing);

    // 初始时间窗口：最近60秒
    QDateTime now = QDateTime::currentDateTime();
    axisX->setRange(now.addSecs(-60), now);

    // 不再启动任何定时器，数据由外部信号驱动
}

RealtimePage::~RealtimePage()
{
    delete ui;
}

void RealtimePage::updateData(const SensorData &data)
{
    qDebug() << "updateData called, temp:" << data.temperature;
    // 更新四个标签
    ui->tempLabel->setText(QString::number(data.temperature, 'f', 1) + " °C");
    ui->humLabel->setText(QString::number(data.humidity, 'f', 1) + " %");
    ui->smokeLabel->setText(QString::number(data.smoke) + " ppm");
    ui->pirLabel->setText(data.pir ? "有人" : "无触发");

    // 更新温度曲线
    QDateTime now = QDateTime::currentDateTime();
    tempSeries->append(now.toMSecsSinceEpoch(), data.temperature);

    // 滚动时间窗口，只显示最近60秒
    QDateTime minTime = now.addSecs(-60);
    axisX->setRange(minTime, now);
    while (tempSeries->count() > 0 &&
           tempSeries->at(0).x() < minTime.toMSecsSinceEpoch()) {
        tempSeries->remove(0);
    }
}
