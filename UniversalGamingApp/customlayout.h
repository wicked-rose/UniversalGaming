#ifndef CUSTOMLAYOUT_H
#define CUSTOMLAYOUT_H

#include <QWidget>
#include <QSerialPort>
#include <QString>
#include <QSerialPortInfo>
#include <QComboBox>
#include <QVector>
#include <QList>

#include <iostream>
#include <string>
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
       // QSerialPort *this_serial = nullptr;
        //auto myParent = qobject_cast<parentWidget()

        MyComboBox(QWidget *parent = nullptr, int index = 0): QComboBox(parent){
            addItems({"Button 1","Button 2","Button 3","Button 4","Button 5",
                      "Button 6","Button 7","Button 8","Button 9","Button 10",
                      "Button 11","Button 12","Button 13","Button 14","Button 15","Button 16"});
            setCurrentIndex(thisIndex);
            thisIndex = index;
            connect(this, &QComboBox::activated, this, &MyComboBox::onComboBoxActivated);
        }

        void onComboBoxActivated(int newIndex){
            qDebug() << "activated";
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
                string data = "on"; //"remap " + to_string(thisIndex) + " " + to_string(newIndex);
                const char *c_str = data.c_str();
                const QByteArray writeData(c_str);// = data.toUtf8();


                const QByteArray write1("o");
                this_serial.write(write1);
                const QByteArray write2("n");
                this_serial.write(write2);
                const QByteArray write3("\r");
                this_serial.write(write3);

                qDebug() << write1 << write2 << write3;

                //writeData.QByteArray::fromHex(c_str);
                if (this_serial.isOpen()) {
                    qDebug() << "serial still connected";
                }
                this_serial.clear();
//                qint64 bytesWritten = this_serial.write(writeData);
//                qDebug() << bytesWritten << " bytes written to serial port";

//                QObject::connect(&this_serial, &QSerialPort::bytesWritten, [](qint64 bytes){
//                    qDebug() << bytes << " bytes written to serial port 2";
//                });

//                if(this_serial.waitForBytesWritten()){
//                    qDebug() << "bytes have been written";
//                }
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
    MyComboBox *thisBox16 = nullptr;

};

#endif // CUSTOMLAYOUT_H
