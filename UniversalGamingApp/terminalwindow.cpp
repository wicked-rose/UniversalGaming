#include "terminalwindow.h"
#include "ui_terminalwindow.h"
#include "settingswidget.h"

#include <QLabel>
#include <QMessageBox>
#include <QDebug>

terminalWindow::terminalWindow(QWidget *parent, SettingsWidget *m_currSettings) :
    QMainWindow(parent),
    m_ui(new Ui::terminalWindow),
    m_console(new Console),
    m_status(new QLabel),
    m_serial(new QSerialPort(this)),
    m_settingsWidget(new SettingsWidget)
{
    m_settingsWidget = m_currSettings;

    m_ui->setupUi(this);
    m_console->setEnabled(false);
    setCentralWidget(m_console);

    m_ui->actionConnect->setEnabled(true);
    m_ui->actionDisconnect->setEnabled(false);
    m_ui->actionQuit->setEnabled(true);
    m_ui->statusBar->addWidget(m_status);

    initActionsConnections();

    connect(m_serial, &QSerialPort::errorOccurred, this, &terminalWindow::handleError);
    connect(m_serial, &QSerialPort::readyRead, this, &terminalWindow::readData);
    connect(m_console, &Console::getData, this, &terminalWindow::writeData);
}

terminalWindow::~terminalWindow()
{
    delete m_ui;
}

void terminalWindow::openSerialPort()
{
    const SettingsWidget::Settings p = m_settingsWidget->settings();
    //qDebug() << "Serial Open Baud: " << p.baudRate;
    qDebug() << "Port Name from m_SettingsWidget: " << m_settingsWidget->settings().name;
    m_serial->setPortName(p.name);
    //m_serial->setPortName("COM3");
    m_serial->setBaudRate(p.baudRate);
    m_serial->setDataBits(p.dataBits);
    m_serial->setParity(p.parity);
    m_serial->setStopBits(p.stopBits);
    m_serial->setFlowControl(p.flowControl);
    if (m_serial->open(QIODevice::ReadWrite)) {
        m_console->setEnabled(true);
        m_ui->actionConnect->setEnabled(false);
        m_ui->actionDisconnect->setEnabled(true);
        showStatusMessage(tr("Connected to %1 : %2, %3, %4, %5, %6")
                          .arg(p.name, p.stringBaudRate, p.stringDataBits,
                               p.stringParity, p.stringStopBits, p.stringFlowControl));
    } else {
        QMessageBox::critical(this, tr("Error"), m_serial->errorString());

        showStatusMessage(tr("Open error"));
    }
}

void terminalWindow::closeSerialPort()
{
    if (m_serial->isOpen())
        m_serial->close();
    m_console->setEnabled(false);
    m_ui->actionConnect->setEnabled(true);
    m_ui->actionDisconnect->setEnabled(false);
    showStatusMessage(tr("Disconnected"));
}

void terminalWindow::writeData(const QByteArray &data)
{
    m_serial->write(data);
}

void terminalWindow::readData()
{
    const QByteArray data = m_serial->readAll();
    m_console->putData(data);
}

void terminalWindow::handleError(QSerialPort::SerialPortError error)
{
    if (error == QSerialPort::ResourceError) {
        QMessageBox::critical(this, tr("Critical Error"), m_serial->errorString());
        closeSerialPort();
    }
}

void terminalWindow::initActionsConnections()
{
    connect(m_ui->actionConnect, &QAction::triggered, this, &terminalWindow::openSerialPort);
    connect(m_ui->actionDisconnect, &QAction::triggered, this, &terminalWindow::closeSerialPort);
    connect(m_ui->actionQuit, &QAction::triggered, this, &terminalWindow::close);
    connect(m_ui->actionClear, &QAction::triggered, m_console, &Console::clear);
}

void terminalWindow::showStatusMessage(const QString &message)
{
    m_status->setText(message);
}
