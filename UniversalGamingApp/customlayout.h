#ifndef CUSTOMLAYOUT_H
#define CUSTOMLAYOUT_H

#include <QWidget>
#include <QSerialPort>
#include <QString>
#include <QSerialPortInfo>

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
    void select();
    void openSerialPort(QString name);
    void closeSerialPort();

private:
    Ui::CustomLayout *m_ui = nullptr;
    QString currLayout;
        QSerialPort *m_serial = nullptr;
};

#endif // CUSTOMLAYOUT_H
