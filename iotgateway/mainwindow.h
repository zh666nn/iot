#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include"realtimepage.h"
#include"controlpage.h"
#include"historypage.h"
#include"databasemanager.h"
#include"mqttmanager.h"
#include"sensorthread.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    RealtimePage *realtimePage;
    ControlPage *controlPage;
    DatabaseManager *dbManager;
    HistoryPage *historyPage;
    MqttManager *m_mqttManager;
    SensorThread *sensorThread;
};
#endif // MAINWINDOW_H
