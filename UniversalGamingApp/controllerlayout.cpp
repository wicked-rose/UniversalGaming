#include "controllerlayout.h"
#include "ui_controllerlayout.h"
#include <QSerialPort>
#include <QSettings>
#include <QSerialPortInfo>
#include <tts.h>
ControllerLayout::ControllerLayout(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ControllerLayout),
    m_serial(new QSerialPort)
{
    ui->setupUi(this);

    connect(ui->selectLayoutBox, &QComboBox::currentIndexChanged,
            this, &ControllerLayout::setControllerLayout);
    connect(ui->selectButton, &QPushButton::clicked,
            this, &ControllerLayout::select);

    tts* layoutBox = new tts(ui->selectLayoutBox, nullptr, "Layout Choice");
    tts* selectButton = new tts(ui->selectButton);
    fillLayoutOptions();
}

ControllerLayout::~ControllerLayout()
{
    delete ui;
}

void ControllerLayout::fillLayoutOptions()
{
    ui->selectLayoutBox->addItem(QStringLiteral("1. Gamepad"), 1);
    ui->selectLayoutBox->addItem(QStringLiteral("2. Keyboard"), 2);
    ui->selectLayoutBox->addItem(QStringLiteral("3. FPS"), 3);
    ui->selectLayoutBox->addItem(QStringLiteral("4. Mouse"), 4);
    ui->selectLayoutBox->addItem(QStringLiteral("5. Multimedia"), 5);
    ui->selectLayoutBox->addItem(QStringLiteral("6. Custom Layout"), 6);
    emit sendStatus("Preset Layouts");
}

void ControllerLayout::setControllerLayout(int index)
{
    if (index == -1)
        return;
    ui->selectionLabel->setText(tr("Layout Selected: %1").arg(ui->selectLayoutBox->itemData(index).toString()));

    currLayout = ui->selectLayoutBox->currentData().toInt();
}

void ControllerLayout::select()
{
    if(currLayout == 6){
        QSettings settings("myconfig.ini", QSettings::IniFormat);
        const auto infos = QSerialPortInfo::availablePorts();
        QString portName = "COM3";
        QString goalId = "463638";

        for (const QSerialPortInfo &info : infos) {
            const auto serialNum = info.serialNumber();
            QString str = serialNum.left(6);
            if(str == goalId){
                portName = info.portName();
            }
        }
        qDebug() << portName;
        openSerialPort(portName);

        // send data
        for(int i = 0; i < 16; i++){
            if(settings.contains("Button " + to_string(i))) {
                QString remap = "remap " + QString::number(i) + " " + settings.value("Button " + to_string(i)).toString() + "\x0D";
                const QByteArray writeData = remap.toUtf8();

                m_serial->clear();
                m_serial->write(writeData);
                m_serial->waitForBytesWritten();

                qDebug() << "sent "+writeData+" over serial";
            }
        }
        closeSerialPort();
        return;
    }
    const auto infos = QSerialPortInfo::availablePorts();
    QString portName = "COM3";
    QString goalId = "463638";

    for (const QSerialPortInfo &info : infos) {
        const auto serialNum = info.serialNumber();
        QString str = serialNum.left(6);
        if(str == goalId){
            portName = info.portName();
        }
    }
    qDebug() << portName;
    openSerialPort(portName);

    // send data
    string data = to_string(currLayout) + "\x0D";
    const char *c_str = data.c_str();
    const QByteArray writeData(c_str);

    m_serial->clear();
    m_serial->write(writeData);
    m_serial->waitForBytesWritten();

    qDebug() << "sent "+writeData+" over serial";
    closeSerialPort();
}

void ControllerLayout::openSerialPort(QString name)
{
    qDebug() << "opening serial port";
    emit sendStatus("Opening serial connection...");
    m_serial->setPortName(name);
    m_serial->setBaudRate(QSerialPort::Baud9600);
    m_serial->setDataBits(QSerialPort::Data8);
    m_serial->setParity(QSerialPort::NoParity);
    m_serial->setStopBits(QSerialPort::OneStop);
    m_serial->setFlowControl( QSerialPort::NoFlowControl);

    if (m_serial->open(QIODevice::ReadWrite)) {
        qDebug() << "serial connected";
        emit sendStatus("Connected");
    } else {
        QMessageBox::critical(this, tr("Error"), m_serial->errorString());
        emit sendStatus("Open error");
    }

}

void ControllerLayout::closeSerialPort()
{
    if (m_serial->isOpen()){
        qDebug() << "closing serial port";
        m_serial->close();
        emit sendStatus("Disconnected");
    }
}


