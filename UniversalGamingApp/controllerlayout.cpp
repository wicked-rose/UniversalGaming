#include "controllerlayout.h"
#include "ui_controllerlayout.h"

ControllerLayout::ControllerLayout(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ControllerLayout),
    statusBar(new QStatusBar(this)),
    m_serial(new QSerialPort),
    m_status(new QLabel)
{
    ui->setupUi(this);

    connect(ui->selectLayoutBox, &QComboBox::currentIndexChanged,
            this, &ControllerLayout::setControllerLayout);
    connect(ui->selectButton, &QPushButton::clicked,
            this, &ControllerLayout::select);

    this->statusBar->show();
    this->statusBar->addWidget(m_status);
    //ui->statusBar->addWidget(m_status);

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
    ui->selectLayoutBox->addItem(QStringLiteral("3. Anotha One"), 3);
}

void ControllerLayout::setControllerLayout(int index)
{
    if (index == -1)
        return;
    ui->selectionLabel->setText(tr("Layout Selected: %1").arg(ui->selectLayoutBox->itemData(index).toString()));

    currLayout = ui->selectLayoutBox->currentData().toInt();
    qDebug() << currLayout;
}

void ControllerLayout::select()
{
    // how to determine/auto detect which com port the comtroller will use,
    // or, other way to identify controller as device we want to connect to
    openSerialPort();

    QByteArray writeData;
    writeData.setNum(currLayout);
    m_serial->write(writeData);

    closeSerialPort();
}

void ControllerLayout::openSerialPort()
{
    // connect to serial port
    m_serial->setPortName("COM3");
    m_serial->setBaudRate(QSerialPort::Baud9600);
    m_serial->setDataBits(QSerialPort::Data8);
    m_serial->setParity(QSerialPort::OddParity);
    m_serial->setStopBits(QSerialPort::OneStop);
    m_serial->setFlowControl( QSerialPort::NoFlowControl);
    if (m_serial->open(QIODevice::ReadWrite)) {
        //showStatusMessage(tr("Connected"));
    } else {
        QMessageBox::critical(this, tr("Error"), m_serial->errorString());
        //showStatusMessage(tr("Open error"));
    }

}

void ControllerLayout::closeSerialPort()
{
    if (m_serial->isOpen())
        m_serial->close();
    //showStatusMessage(tr("Disconnected"));
}

void ControllerLayout::showStatusMessage(const QString &message)
{
    m_status->setText(message);
}

