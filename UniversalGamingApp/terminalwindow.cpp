#include "terminalwindow.h"
#include "ui_terminalwindow.h"
#include "settingswidget.h"

#include <QLabel>
#include <QMessageBox>

terminalWindow::terminalWindow(QWidget *parent) :
    QMainWindow(parent),
    m_ui(new Ui::terminalWindow),
    m_console(new Console)
{
    m_ui->setupUi(this);
    m_console->setEnabled(false);
    setCentralWidget(m_console);

    m_ui->actionConnect->setEnabled(true);
    m_ui->actionDisconnect->setEnabled(false);
    m_ui->actionQuit->setEnabled(true);

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
    m_serial->setPortName(p.name);
    m_serial->setBaudRate(p.baudRate);
    m_serial->setDataBits(p.dataBits);
    m_serial->setParity(p.parity);
    m_serial->setStopBits(p.stopBits);
    m_serial->setFlowControl(p.flowControl);
    if (m_serial->open(QIODevice::ReadWrite)) {
        m_console->setEnabled(true);
        //m_console->setLocalEchoEnabled(p.localEchoEnabled);
        m_ui->actionConnect->setEnabled(false);
        m_ui->actionDisconnect->setEnabled(true);
        m_ui->actionConfigure->setEnabled(false);
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

void terminalWindow::about()
{
    QMessageBox::about(this, tr("About Simple Terminal"),
                       tr("The <b>Simple Terminal</b> example demonstrates how to "
                          "use the Qt Serial Port module in modern GUI applications "
                          "using Qt, with a menu bar, toolbars, and a status bar."));
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
    //connect(m_ui->actionConfigure, &QAction::triggered, m_settingsWidget, &SettingsWidget::show);
    connect(m_ui->actionClear, &QAction::triggered, m_console, &Console::clear);
}

void terminalWindow::showStatusMessage(const QString &message)
{
    m_status->setText(message);
}
