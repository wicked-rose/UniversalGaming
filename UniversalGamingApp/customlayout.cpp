#include "customlayout.h"
#include "ui_customlayout.h"

CustomLayout::CustomLayout(QWidget *parent) :
    QWidget(parent),
    m_ui(new Ui::CustomLayout),
        m_serial(new QSerialPort)
{
    m_ui->setupUi(this);
}

CustomLayout::~CustomLayout()
{
    delete m_ui;
}

void CustomLayout::addOptions(){
    // for each box in boxes
    QString thisBox = "1";
    m_ui->box1->addItem("Button 2", ("remap 1 2"));
}

void CustomLayout::select(){
    // how to determine/auto detect which com port the comtroller will use,
    // or, other way to identify controller as device we want to connect to
    // const QString blankString = tr(::blankString);
    const auto infos = QSerialPortInfo::availablePorts();
    QString portName = "COM4";
    const auto goalId = '239a';

    for (const QSerialPortInfo &info : infos) {
        QStringList list;
        const auto vendorId = info.vendorIdentifier();
        //const auto productId = info.productIdentifier();
        if(vendorId == goalId){
            portName = info.portName();
        }
    }
    openSerialPort(portName);


    QString str = "remap 1 5";
    QByteArray writeData;
   // writeData.QByteArray::fromHex(str.toUTF8());
    qDebug() << writeData;
    m_serial->write(writeData);

    closeSerialPort();

}
void CustomLayout::openSerialPort(QString name){
    // read heartbeat signal, if matches pico ID, connect
    // connect to serial port
    m_serial->setPortName(name);
    m_serial->setBaudRate(QSerialPort::Baud9600);
    m_serial->setDataBits(QSerialPort::Data8);
    m_serial->setParity(QSerialPort::OddParity);
    m_serial->setStopBits(QSerialPort::OneStop);
    m_serial->setFlowControl( QSerialPort::NoFlowControl);
    if (m_serial->open(QIODevice::ReadWrite)) {
        //showStatusMessage(tr("Connected"));
    } else {
        //QMessageBox::critical(this, tr("Error"), m_serial->errorString());
        //showStatusMessage(tr("Open error"));
    }
}
void CustomLayout::closeSerialPort(){
    if (m_serial->isOpen())
        m_serial->close();
    //showStatusMessage(tr("Disconnected"));
}
