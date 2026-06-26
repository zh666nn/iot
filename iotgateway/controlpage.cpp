#include "controlpage.h"
#include "ui_controlpage.h"
#include<QDebug>
ControlPage::ControlPage(QWidget *parent) :
    QWidget(parent), ui(new Ui::ControlPage),
    ledState(false), buzzerState(false)
{
    ui->setupUi(this);
    connect(ui->ledbtn, &QPushButton::clicked, this, &ControlPage::onLedClicked);
    connect(ui->buzzerbtn, &QPushButton::clicked, this, &ControlPage::onBuzzerClicked);
}

ControlPage::~ControlPage() { delete ui; }

void ControlPage::setLed(const QString &cmd) {
    ledState = (cmd.toLower() == "on");
    ui->ledbtn->setText(ledState ? "LED 亮" : "LED 关");
    // 真实硬件控制，测试时可注释
    // writeSysfs("/sys/class/leds/user-led/brightness", ledState ? "1" : "0");
    qDebug() << "LED" << cmd;
}


void ControlPage::setBuzzer(const QString &cmd) {
    buzzerState = (cmd.toLower() == "on");
    ui->buzzerbtn->setText(buzzerState ? "蜂鸣器 开" : "蜂鸣器 关");
    // writeSysfs("/sys/class/gpio/gpio123/value", buzzerState ? "1" : "0");
    qDebug() << "Buzzer" << cmd;
}

void ControlPage::onLedClicked() {
    if (ledState)
        setLed("off");
    else
        setLed("on");
}

void ControlPage::onBuzzerClicked() {
    if (buzzerState)
        setBuzzer("off");
    else
        setBuzzer("on");
}
