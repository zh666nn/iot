#ifndef HISTORYPAGE_H
#define HISTORYPAGE_H

#include <QWidget>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QDateTimeAxis>
#include <QtCharts/QValueAxis>
#include "databasemanager.h"

QT_CHARTS_USE_NAMESPACE

namespace Ui { class HistoryPage; }

class HistoryPage : public QWidget
{
    Q_OBJECT
public:
    explicit HistoryPage(DatabaseManager *dbMgr, QWidget *parent = nullptr);
    ~HistoryPage();

private slots:
    void onQuery();

private:
    Ui::HistoryPage *ui;
    DatabaseManager *m_dbManager;
    QLineSeries *m_series;
    QChart *m_chart;
    QDateTimeAxis *m_axisX;
    QValueAxis *m_axisY;
};

#endif
