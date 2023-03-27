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
    select();
    addOptions();
   // updateLayout();
}

CustomLayout::~CustomLayout()
{
    delete m_ui;
}

void CustomLayout::addOptions(){
    m_ui->leftLayout->addWidget(thisBox1);
    m_ui->leftLayout->addWidget(thisBox2);
    m_ui->leftLayout->addWidget(thisBox3);
    m_ui->leftLayout->addWidget(thisBox4);
    m_ui->leftLayout->addWidget(thisBox5);
    m_ui->leftLayout->addWidget(thisBox6);
    m_ui->leftLayout->addWidget(thisBox7);
    m_ui->leftLayout->addWidget(thisBox8);

    m_ui->rightLayout->addWidget(thisBox9);
    m_ui->rightLayout->addWidget(thisBox10);
    m_ui->rightLayout->addWidget(thisBox11);
    m_ui->rightLayout->addWidget(thisBox12);
    m_ui->rightLayout->addWidget(thisBox13);
    m_ui->rightLayout->addWidget(thisBox14);
    m_ui->rightLayout->addWidget(thisBox15);
    m_ui->rightLayout->addWidget(thisBox16);
}


void CustomLayout::updateLayout(int thisIndex, int newIndex){
    // send serial instruction
    openSerialPort(portName);

    if (m_serial->open(QIODevice::ReadWrite)  ) {
        qDebug() << "serial connected";
        // send data
        string data = "remap " + to_string(thisIndex) + " " + to_string(newIndex);
        const char *c_str = data.c_str();
        const QByteArray writeData(c_str);

        m_serial->clear();
        m_serial->write(writeData);
        m_serial->waitForBytesWritten();
    }

    closeSerialPort();
}

void CustomLayout::select(){
    const auto infos = QSerialPortInfo::availablePorts();
    portName = "COM5";
    QString goalId = "463638";

    for (const QSerialPortInfo &info : infos) {
        const auto serialNum = info.serialNumber();
        QString str = serialNum.left(6);
        if(str == goalId){
            portName = info.portName();
        }
    }
}
void CustomLayout::openSerialPort(QString name){
    m_serial->setPortName(name);
    m_serial->setBaudRate(QSerialPort::Baud9600);
    m_serial->setDataBits(QSerialPort::Data8);
    m_serial->setParity(QSerialPort::OddParity);
    m_serial->setStopBits(QSerialPort::OneStop);
    m_serial->setFlowControl( QSerialPort::NoFlowControl);
    m_serial->open(QIODevice::ReadWrite);
    if (m_serial->isOpen()) {
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
