#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);

    m_mqttManager = new MqttManager("localhost", 1883, this);
    m_mqttManager->connectToHost();
     sensorThread = new SensorThread(this);
    dbManager = new DatabaseManager("gateway.db", this);
    realtimePage = new RealtimePage(this);          // 自定义实时页面
    controlPage = new ControlPage(this);            // 占位：控制页面
    historyPage  = new HistoryPage(dbManager, this);// 历史页面（传入数据库指针）
       // 替换 stackedWidget 中的页面，索引必须与菜单项顺序对应
       ui->stackedWidget_2->insertWidget(0, realtimePage);    // 索引0 → 实时数据
       ui->stackedWidget_2->insertWidget(1, historyPage); // 索引1 → 历史数据（暂时空白）
       ui->stackedWidget_2->insertWidget(2, controlPage); // 索引2 → 设备控制 // 插入到页面0
    ui->menuList->setCurrentRow(0);              // 默认显示实时数据页
    connect(ui->menuList,&QListWidget::currentRowChanged,ui->stackedWidget_2,&QStackedWidget::setCurrentIndex);
   // 5.1 采集数据 → 实时页面更新（标签+曲线）
   connect(sensorThread, &SensorThread::newSensorData,
           realtimePage, &RealtimePage::updateData);

   // 5.2 采集数据 → 数据库存储
   connect(sensorThread, &SensorThread::newSensorData,
           dbManager, &DatabaseManager::saveSensorData);

   // 5.3 采集数据 → MQTT 上报
   connect(sensorThread, &SensorThread::newSensorData,
          m_mqttManager, &MqttManager::publishSensorData);

//    // ======================== 6. MQTT 远程控制 ========================
   connect(m_mqttManager, &MqttManager::ledCommand,
           controlPage, &ControlPage::setLed);
   connect(m_mqttManager, &MqttManager::buzzerCommand,
          controlPage, &ControlPage::setBuzzer);
    // 启动采集线程（每5秒产生一次数据）
    sensorThread->start();
    bool conn = connect(sensorThread, &SensorThread::newSensorData,
                        realtimePage, &RealtimePage::updateData);
    qDebug() << "Signal-slot connected:" << conn;
}

MainWindow::~MainWindow()
{
    delete ui;
}

