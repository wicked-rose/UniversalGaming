#ifndef CONTROLLERLAYOUT_H
#define CONTROLLERLAYOUT_H

#include <QWidget>
#include <QSerialPort>
#include <QLabel>
#include <QStatusBar>
#include <QMessageBox>
#include <QString>

namespace Ui {
class ControllerLayout;
}

class ControllerLayout : public QWidget
{
    Q_OBJECT

public:
    explicit ControllerLayout(QWidget *parent = nullptr);
    ~ControllerLayout();
    void fillLayoutOptions();
    void setControllerLayout(int index);
    void select();
    void openSerialPort(QString name);
    void closeSerialPort();
signals:
    void sendStatus(QString message);

private:
    Ui::ControllerLayout *ui;     
    int currLayout;
    QSerialPort *m_serial = nullptr;
};

#endif // CONTROLLERLAYOUT_H
