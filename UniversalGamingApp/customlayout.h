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
    class MyComboBox : public QComboBox
    {
    public:
        int thisIndex = 0;

        MyComboBox(QWidget *parent = nullptr, int index = 0): QComboBox(parent){
            addItems({"Button 0","Button 1","Button 2","Button 3","Button 4",
                      "Button 5","Button 6","Button 7","Button 8","Button 9",
                      "Button 10","Button 11","Button 12","Button 13","Button 14","Button 15"});

            thisIndex = index;
            setCurrentIndex(thisIndex);

            connect(this, &QComboBox::activated, this, &MyComboBox::onComboBoxActivated);
            QString toSay = "Button " + QString::number(index);
            tts* cbTts = new tts(this, nullptr, toSay);
        }

        void onComboBoxActivated(int newIndex){
           // updateLayout(thisIndex, newIndex);

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

signals:
    void sendStatus(QString message);

private:
    Ui::CustomLayout *m_ui = nullptr;
    QString currLayout;
    QString portName = "COM3";
    QSerialPort *m_serial = nullptr;
    //QList<QComboBox*> boxes;
    MyComboBox *thisBox0 = nullptr;
    MyComboBox *thisBox1 = nullptr;
    MyComboBox *thisBox2 = nullptr;
    MyComboBox *thisBox3 = nullptr;
    MyComboBox *thisBox4 = nullptr;
    MyComboBox *thisBox5 = nullptr;
    MyComboBox *thisBox6 = nullptr;
    MyComboBox *thisBox7 = nullptr;
    MyComboBox *thisBox8 = nullptr;
    MyComboBox *thisBox9 = nullptr;
    MyComboBox *thisBox10 = nullptr;
    MyComboBox *thisBox11 = nullptr;
    MyComboBox *thisBox12 = nullptr;
    MyComboBox *thisBox13 = nullptr;
    MyComboBox *thisBox14 = nullptr;
    MyComboBox *thisBox15 = nullptr;

    QLabel *label0 = nullptr;
    QLabel *label1 = nullptr;
    QLabel *label2 = nullptr;
    QLabel *label3 = nullptr;
    QLabel *label4 = nullptr;
    QLabel *label5 = nullptr;
    QLabel *label6 = nullptr;
    QLabel *label7 = nullptr;
    QLabel *label8 = nullptr;
    QLabel *label9 = nullptr;
    QLabel *label10 = nullptr;
    QLabel *label11 = nullptr;
    QLabel *label12 = nullptr;
    QLabel *label13 = nullptr;
    QLabel *label14 = nullptr;
    QLabel *label15 = nullptr;

   // QGroupBox *groupBox0 = nullptr;

};

#endif // CUSTOMLAYOUT_H
