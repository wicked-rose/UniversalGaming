#ifndef SETTINGSWIDGET_H
#define SETTINGSWIDGET_H

#include <QWidget>
#include <QSerialPort>

QT_BEGIN_NAMESPACE

namespace Ui {
class SettingsWidget;
}

class QIntValidator;

QT_END_NAMESPACE

class SettingsWidget : public QWidget
{
    Q_OBJECT

public:
    struct Settings {
        QString name;
        qint32 baudRate;
        QString stringBaudRate;
        QSerialPort::DataBits dataBits;
        QString stringDataBits;
        QSerialPort::Parity parity;
        QString stringParity;
        QSerialPort::StopBits stopBits;
        QString stringStopBits;
        QSerialPort::FlowControl flowControl;
        QString stringFlowControl;
        bool localEchoEnabled;
    };
    explicit SettingsWidget(QWidget *parent = nullptr);
    ~SettingsWidget();
    Settings settings() const;
    void updateSettings();

private slots:
    void showPortInfo(int idx);
    void checkCustomBaudRatePolicy(int idx);
    void checkCustomDevicePathPolicy(int idx);

private:
    void fillPortsParameters();
    void fillPortsInfo();


private:
    Ui::SettingsWidget *m_ui = nullptr;
    Settings m_currentSettings;
    QIntValidator *m_intValidator = nullptr;
};

#endif // SETTINGSWIDGET_H
