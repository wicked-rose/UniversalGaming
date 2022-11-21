#ifndef TERMINALWINDOW_H
#define TERMINALWINDOW_H

#include <QMainWindow>
#include <QSerialPort>
#include <QLabel>
#include "console.h"
#include "settingswidget.h"

namespace Ui {
class terminalWindow;
}

class terminalWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit terminalWindow(QWidget *parent = nullptr);
    ~terminalWindow();

private slots:
    void openSerialPort();
    void closeSerialPort();
    void about();
    void writeData(const QByteArray &data);
    void readData();

    void handleError(QSerialPort::SerialPortError error);

private:
    void initActionsConnections();

private:
    void showStatusMessage(const QString &message);
    Ui::terminalWindow *m_ui;
    Console *m_console = nullptr;
    SettingsWidget *m_settingsWidget = nullptr;
    //QWidget *mySettingsWidget = nullptr;
    QSerialPort *m_serial = nullptr;
    QLabel *m_status = nullptr;
};

#endif // TERMINALWINDOW_H
