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
public slots:
    void displayStatusMessage(QString message);

private:
    Ui::MainWindow *m_ui;
    SettingsWidget *m_settings = nullptr;
    Console *m_console = nullptr;
    ControllerLayout *m_layout = nullptr;
};
#endif // MAINWINDOW_H
