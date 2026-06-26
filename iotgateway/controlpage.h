#ifndef CONTROLPAGE_H
#define CONTROLPAGE_H
#include <QWidget>

namespace Ui { class ControlPage; }

class ControlPage : public QWidget {
    Q_OBJECT
public:
    explicit ControlPage(QWidget *parent = nullptr);
    ~ControlPage();
public slots:
    void setLed(const QString &on);        // 将来接收 MQTT 命令
    void setBuzzer(const QString &on);
private slots:
    void onLedClicked();
    void onBuzzerClicked();
private:
    Ui::ControlPage *ui;
    bool ledState;
    bool buzzerState;
};
#endif
