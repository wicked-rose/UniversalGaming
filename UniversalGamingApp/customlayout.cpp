#include "customlayout.h"
#include "ui_customlayout.h"
#include <QSettings>

CustomLayout::CustomLayout(QWidget *parent) :
    QWidget(parent),
    m_ui(new Ui::CustomLayout),
    m_serial(new QSerialPort),
    button(new QPushButton),
    settings(new QSettings("myconfig.ini", QSettings::IniFormat))
{
    m_ui->setupUi(this);
    select();

    for(int i = 0; i <= 15; i++){
        MyComboBox *newCombo = new MyComboBox(this,i);

        MyGroupBox *newBox = new MyGroupBox(this, i, newCombo);

        boxes.push_back(newBox);
    }

    addOptions();
}

CustomLayout::~CustomLayout()
{
    delete m_ui;
}

void CustomLayout::addOptions(){
    for(int i = 0; i <= 7; i++){
        m_ui->leftLayout->addWidget(boxes.at(i));
    }
    for(int i = 8; i <= 15; i++){
        m_ui->rightLayout->addWidget(boxes.at(i));
    }

    button->setText("Save Layout");
    connect(button, &QPushButton::clicked, this, &CustomLayout::saveConfig);
    m_ui->topText->addWidget(button);
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
void CustomLayout::saveConfig(){
    qDebug() << "layout saved";

    for(int i = 0; i <= 15; i++){
        QString s = "Button " + QString::number(i);
        MyComboBox *c = boxes.at(i)->myBox;
        settings->setValue(s, c->newIndex);
    }
//    settings->setValue("Button 0", thisBox0->newIndex);
//    settings->setValue("Button 1", thisBox1->newIndex);
//    settings->setValue("Button 2", thisBox2->newIndex);
//    settings->setValue("Button 3", thisBox3->newIndex);
//    settings->setValue("Button 4", thisBox4->newIndex);
//    settings->setValue("Button 5", thisBox5->newIndex);
//    settings->setValue("Button 6", thisBox6->newIndex);
//    settings->setValue("Button 7", thisBox7->newIndex);
//    settings->setValue("Button 8", thisBox8->newIndex);
//    settings->setValue("Button 9", thisBox9->newIndex);
//    settings->setValue("Button 10", thisBox10->newIndex);
//    settings->setValue("Button 11", thisBox11->newIndex);
//    settings->setValue("Button 12", thisBox12->newIndex);
//    settings->setValue("Button 13", thisBox13->newIndex);
//    settings->setValue("Button 14", thisBox14->newIndex);
//    settings->setValue("Button 15", thisBox15->newIndex);
}
