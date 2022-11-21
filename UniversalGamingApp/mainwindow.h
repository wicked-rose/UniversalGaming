#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>
#include <QStackedWidget>
#include "customtabstyle.h"
#include "console.h"
#include "settingswidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
/*
private slots:
    void openSerialPort();
    void closeSerialPort();
    void about();
    void writeData(const QByteArray &data);
    void readData();

    void handleError(QSerialPort::SerialPortError error);

private:
    void initActionsConnections();
*/
private:
    void showStatusMessage(const QString &message);
    Ui::MainWindow *m_ui;
    Console *m_console = nullptr;
    SettingsWidget *settingsWidget = nullptr;
    QWidget *mySettingsWidget = nullptr;
    QSerialPort *m_serial = nullptr;
};
#endif // MAINWINDOW_H
