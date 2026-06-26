#include "mainwindow.h"
#include<QDebug>
#include <QApplication>
#include "sensordata.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // 注册自定义类型，使跨线程信号槽能够排队传递参数
        qRegisterMetaType<SensorData>("SensorData");
    MainWindow w;
    w.show();
    qDebug() << "可用的数据库驱动:" << QSqlDatabase::drivers();
    return a.exec();
}
