#ifndef SETTINGS_H
#define SETTINGS_H
#include <QDialog>
#include <QSerialPort>

QT_BEGIN_NAMESPACE

namespace Ui {
class Settings;
}

class QIntValidator;

QT_END_NAMESPACE

class Settings : public QDialog
{
    Q_OBJECT

public:
    struct SettingsInfo {
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

    explicit Settings(QWidget *parent = nullptr);
    ~Settings();

    SettingsInfo settings() const;

private slots:
    void showPortInfo(int idx);
    void apply();
    void checkCustomBaudRatePolicy(int idx);
    void checkCustomDevicePathPolicy(int idx);

private:
    void fillPortsParameters();
    void fillPortsInfo();
    void updateSettings();

private:
    SettingsInfo m_currentSettings;
    Ui::Settings *m_ui = nullptr;
    QIntValidator *m_intValidator = nullptr;
};

#endif // SETTINGS_H
