#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "customtabstyle.h"
#include "qlayout.h"

#include <QSerialPort>
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      m_ui(new Ui::MainWindow),
      m_console(new Console),
      m_settings(new SettingsWidget(this))
     // m_layout(new ControllerLayout(this))
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
    //qDebug() << "apply clicked";
    m_settings->updateSettings();
    //qDebug() << "Updated Baud: " << m_settings->settings().baudRate;
    terminalWindow *win = new terminalWindow(this, m_settings);
    if(win != nullptr){
        win->show();
    }
}

