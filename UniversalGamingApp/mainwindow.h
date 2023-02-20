#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>
#include <QStackedWidget>
#include <QPushButton>
#include "customtabstyle.h"
#include "terminalwindow.h"
#include "settingswidget.h"
#include "console.h"
#include "controllerlayout.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
class Console;
class SettingsDialog;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void apply();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *m_ui;
//    terminalWindow *win = nullptr;
    SettingsWidget *m_settings = nullptr;
    Console *m_console = nullptr;
    ControllerLayout *m_layout = nullptr;
//    QSerialPort *m_serial = nullptr;
};
#endif // MAINWINDOW_H
