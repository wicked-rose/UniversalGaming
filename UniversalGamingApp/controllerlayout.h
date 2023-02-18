#ifndef CONTROLLERLAYOUT_H
#define CONTROLLERLAYOUT_H

#include <QWidget>
#include <QSerialPort>
#include <QLabel>
#include <QStatusBar>
#include <QMessageBox>

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
    void showStatusMessage(const QString &message);

private:
    Ui::ControllerLayout *ui;     
    int currLayout;
    QSerialPort *m_serial = nullptr;
    QStatusBar *statusBar = nullptr;
    QLabel *m_status = nullptr;
};

#endif // CONTROLLERLAYOUT_H
