#include "historypage.h"
#include "ui_historypage.h"
#include <QDebug>
#include <QDateTime>
#include <QSqlError>

HistoryPage::HistoryPage(DatabaseManager *dbMgr, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HistoryPage),
    m_dbManager(dbMgr)
{
    ui->setupUi(this);

    // 表格
    ui->tableWidget->setColumnCount(2);
    ui->tableWidget->setHorizontalHeaderLabels({"时间", "数值"});
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);

    // 图表
    m_series = new QLineSeries();
    m_chart = new QChart();
    m_chart->addSeries(m_series);
    m_chart->setTitle("历史数据曲线");

    m_axisX = new QDateTimeAxis();
    m_axisX->setFormat("hh:mm:ss");
    m_axisY = new QValueAxis();

    m_chart->addAxis(m_axisX, Qt::AlignBottom);
    m_chart->addAxis(m_axisY, Qt::AlignLeft);
    m_series->attachAxis(m_axisX);
    m_series->attachAxis(m_axisY);

    ui->widget->setChart(m_chart);
    ui->widget->setRenderHint(QPainter::Antialiasing);

    // 默认时间范围
    QDateTime now = QDateTime::currentDateTime();
    ui->dateTimeEdit->setDateTime(now.addSecs(-3600));
    ui->dateTimeEdit_2->setDateTime(now);

    // 连接按钮（关键）
    connect(ui->pushButton, &QPushButton::clicked, this, &HistoryPage::onQuery);
    qDebug() << "HistoryPage 构造完成，信号槽连接状态："
             << connect(ui->pushButton, &QPushButton::clicked, this, &HistoryPage::onQuery);
}

HistoryPage::~HistoryPage()
{
    delete ui;
}

void HistoryPage::onQuery()
{
    qDebug() << "onQuery() 开始执行";

    // 1. 获取类型映射
    QString typeText = ui->comboBox->currentText().trimmed();
    QString dbType;
    if (typeText == "温度") dbType = "temperature";
    else if (typeText == "湿度") dbType = "humidity";
    else if (typeText == "烟雾") dbType = "smoke";
    else if (typeText == "红外") dbType = "pir";
    else {
        qDebug() << "未知类型：" << typeText;
        return;
    }

    // 2. 获取时间
    QDateTime from = ui->dateTimeEdit->dateTime();
    QDateTime to   = ui->dateTimeEdit_2->dateTime();
    qDebug() << "查询条件：" << dbType << from << to;

    // 3. 查询数据库
    QList<SensorData> dataList = m_dbManager->queryData(dbType, from, to);
    qDebug() << "查询结果数量：" << dataList.count();

    // 4. 清空表格和曲线
    ui->tableWidget->setRowCount(0);
    m_series->clear();

    // 5. 填充数据
    qreal minVal = 1e9, maxVal = -1e9;
    for (const auto &d : dataList) {
        qreal value = 0;
        if (dbType == "temperature")        value = d.temperature;
        else if (dbType == "humidity")      value = d.humidity;
        else if (dbType == "smoke")         value = d.smoke;
        else if (dbType == "pir")           value = d.pir ? 1.0 : 0.0;

        // 表格
        int row = ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(row);
        ui->tableWidget->setItem(row, 0, new QTableWidgetItem(d.timestamp.toString("yyyy-MM-dd hh:mm:ss")));
        ui->tableWidget->setItem(row, 1, new QTableWidgetItem(QString::number(value, 'f', 1)));

        // 曲线
        m_series->append(d.timestamp.toMSecsSinceEpoch(), value);

        if (value < minVal) minVal = value;
        if (value > maxVal) maxVal = value;
    }

    // 6. 调整坐标轴
    if (!dataList.isEmpty()) {
        m_axisY->setRange(minVal - 1, maxVal + 1);
        m_axisX->setRange(from, to);
    }

    qDebug() << "onQuery() 执行完毕";
}
