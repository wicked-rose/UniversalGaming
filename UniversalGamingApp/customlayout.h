#ifndef CUSTOMLAYOUT_H
#define CUSTOMLAYOUT_H

#include <QWidget>
#include <QSerialPort>
#include <QString>
#include <QSerialPortInfo>
#include <QComboBox>
#include <QVector>
#include <QList>
#include <QLabel>
#include <QGroupBox>
#include <QSettings>
#include <QLayout>

#include <iostream>
#include <string>
#include <tts.h>
using namespace std;

namespace Ui {
class CustomLayout;
}

class CustomLayout : public QWidget
{
    Q_OBJECT

public:
    explicit CustomLayout(QWidget *parent = nullptr);
    ~CustomLayout();
    void addOptions();
    void updateLayout(int thisIndex, int newIndex);
    void select();
    void openSerialPort(QString name);
    void closeSerialPort();
    void saveConfig();
    class MyComboBox : public QComboBox
    {
    public:
        int thisIndex = 0;
        int newIndex = 0;
        tts* cbTts;
        MyComboBox(QWidget *parent = nullptr, int index = 0): QComboBox(parent){
            addItems({"Button 0","Button 1","Button 2","Button 3","Button 4",
                      "Button 5","Button 6","Button 7","Button 8","Button 9",
                      "Button 10","Button 11","Button 12","Button 13","Button 14","Button 15"});

            thisIndex = index;
            newIndex = index;
            setCurrentIndex(thisIndex);

            connect(this, &QComboBox::activated, this, &MyComboBox::onComboBoxActivated);
            QString toSay = "Button " + QString::number(index);
            cbTts = new tts(this, nullptr, toSay);
        }


        void onComboBoxActivated(int newIndex){
           // updateLayout(thisIndex, newIndex);
            this->newIndex = newIndex;
            // detect serial port
            const auto infos = QSerialPortInfo::availablePorts();
            QString portName = "COM5";
            QString goalId = "463638";

            for (const QSerialPortInfo &info : infos) {
                const auto serialNum = info.serialNumber();
                QString str = serialNum.left(6);
                if(str == goalId){
                    portName = info.portName();
                }
            }
            if(thisIndex != newIndex){
                QString toSay = "Button " + QString::number(thisIndex) + "remapped to Button " + QString::number(newIndex);
                this->cbTts->setToSay(toSay);
            }
            else{
                QString toSay = "Button " + QString::number(thisIndex) + "default function";
                this->cbTts->setToSay(toSay);
            }
            // open serial port
            QSerialPort this_serial;
            qDebug() << portName;
            this_serial.setPortName(portName);
            this_serial.setBaudRate(QSerialPort::Baud9600);
            this_serial.setDataBits(QSerialPort::Data8);
            this_serial.setParity(QSerialPort::NoParity);
            this_serial.setStopBits(QSerialPort::OneStop);
            this_serial.setFlowControl( QSerialPort::NoFlowControl);
           // this_serial.open(QIODevice::ReadWrite);

            if (this_serial.open(QIODevice::ReadWrite)  ) {
                qDebug() << "serial connected";
                // send data
                string data = "remap " + to_string(thisIndex) + " " + to_string(newIndex) + "\x0D";
                const char *c_str = data.c_str();
                const QByteArray writeData(c_str);
                qDebug() << c_str;

                this_serial.clear();
                this_serial.write(writeData);
                this_serial.waitForBytesWritten();
            }

            // close serial port
            if (this_serial.isOpen())
                this_serial.close();
        }
    };
    //QGroupBox* myGroupBox(int index, MyComboBox *myBox);
    class MyGroupBox : public QGroupBox{
    public:
        MyComboBox *myBox;
        MyGroupBox(QWidget *parent = nullptr, int index = 0, MyComboBox *thisBox = nullptr): QGroupBox(parent){
            myBox = thisBox;
            setTitle("Button " + QString::number(index));
            this->setStyleSheet("QGroupBox::title {color: red}");

            QVBoxLayout *layout = new QVBoxLayout;
            layout->addWidget(myBox);
            layout->addStretch(1);
            this->setLayout(layout);
        }
    };

signals:
    void sendStatus(QString message);

private:
    Ui::CustomLayout *m_ui = nullptr;
    QString currLayout;
    QString portName = "COM3";
    QSerialPort *m_serial = nullptr;

    QPushButton *button = nullptr;
    QSettings *settings = nullptr;

    QList<MyGroupBox*> boxes;

};

#endif // CUSTOMLAYOUT_H
