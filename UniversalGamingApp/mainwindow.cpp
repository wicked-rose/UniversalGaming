#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "customtabstyle.h"
//#include "qlayout.h"
#include "settingswidget.h"

#include <QSerialPort>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      m_ui(new Ui::MainWindow),
      m_console(new Console),
      settingsWidget(new SettingsWidget),
      m_serial(new QSerialPort(this))
{
    m_ui->setupUi(this);
    m_ui->menuTabWidget->tabBar()->setStyle(new CustomTabStyle);
/*
    m_ui->actionConnect->setEnabled(true);
    m_ui->actionDisconnect->setEnabled(false);
    m_ui->actionQuit->setEnabled(true);
    m_ui->actionConfigure->setEnabled(true);

    initActionsConnections();

    connect(m_serial, &QSerialPort::errorOccurred, this, &MainWindow::handleError);
    connect(m_serial, &QSerialPort::readyRead, this, &MainWindow::readData);
    connect(m_console, &Console::getData, this, &MainWindow::writeData);
*/
};

MainWindow::~MainWindow()
{
    delete m_ui;
}

