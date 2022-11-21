#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "customtabstyle.h"
#include "qlayout.h"

#include <QSerialPort>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      m_ui(new Ui::MainWindow),
      m_console(new Console),
      m_settings(new SettingsWidget)
{
    m_ui->setupUi(this);
    m_ui->menuTabWidget->tabBar()->setStyle(new CustomTabStyle);
    connect(m_ui->applyButton, &QPushButton::clicked,
            this, &MainWindow::apply);
};

MainWindow::~MainWindow()
{
    delete m_ui;
}

void MainWindow::apply()
{
    m_settings->updateSettings();
    terminalWindow *win = new terminalWindow();
    if(win != nullptr){
        win->show();
    }
    //hide();
}
