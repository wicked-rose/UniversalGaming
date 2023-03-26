#include "customlayout.h"
#include "ui_customlayout.h"

CustomLayout::CustomLayout(QWidget *parent) :
    QWidget(parent),
    m_ui(new Ui::CustomLayout),
    m_serial(new QSerialPort),
    thisBox1(new MyComboBox(this,1)),
    thisBox2(new MyComboBox(this,2)),
    thisBox3(new MyComboBox(this,3)),
    thisBox4(new MyComboBox(this,4)),
    thisBox5(new MyComboBox(this,5)),
    thisBox6(new MyComboBox(this,6)),
    thisBox7(new MyComboBox(this,7)),
    thisBox8(new MyComboBox(this,8)),
    thisBox9(new MyComboBox(this,9)),
    thisBox10(new MyComboBox(this,10)),
    thisBox11(new MyComboBox(this,11)),
    thisBox12(new MyComboBox(this,12)),
    thisBox13(new MyComboBox(this,13)),
    thisBox14(new MyComboBox(this,14)),
    thisBox15(new MyComboBox(this,15)),
    thisBox16(new MyComboBox(this,16))
{
    m_ui->setupUi(this);
    addOptions();
   // updateLayout();
}

CustomLayout::~CustomLayout()
{
    delete m_ui;
}

void CustomLayout::addOptions(){
    //QHBoxLayout *layout = new QHBoxLayout(this);
    //thisBox1->thisBox.setParent(this);
    m_ui->leftLayout->addWidget(thisBox1);

   // m_ui->box1->addItems({"Button 1","Button 2","Button 3","Button 4","Button 5",
   //                     "Button 6","Button 7","Button 8","Button 9","Button 10",
   //                     "Button 11","Button 12","Button 13","Button 14","Button 15","Button 16"});
}

void CustomLayout::updateLayout(int thisIndex, int newIndex){
    // send serial instruction
    // " remap " + this index + chosen index
    openSerialPort(portName);

     QString data = "remap " + QString::number(thisIndex) + " " + QString::number(newIndex);
    qDebug() << data;
    QByteArray writeData = data.toLatin1();
   // writeData.QByteArray::fromHex(data.toUTF8());
    m_serial->write(writeData);

    closeSerialPort();
}

void CustomLayout::select(){
    // change later to continuously send remap over serial on ComboBox click
    const auto infos = QSerialPortInfo::availablePorts();
    portName = "COM3";
    QString goalId = "463638";

    for (const QSerialPortInfo &info : infos) {
        const auto serialNum = info.serialNumber();
        QString str = serialNum.left(6);
        if(str == goalId){
            portName = info.portName();
        }
    }
    openSerialPort(portName);

    //updateLayout();

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
