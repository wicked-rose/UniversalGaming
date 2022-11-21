#ifndef TERMINALDIALOG_H
#define TERMINALDIALOG_H

#include <QMainWindow>
#include <QSerialPort>
#include "console.h"
#include "settingswidget.h"

namespace Ui {
class terminalDialog;
}

class terminalDialog : public QMainWindow
{
    Q_OBJECT

public:
    explicit terminalDialog(QWidget *parent = nullptr);
    ~terminalDialog();

private:
    Ui::terminalDialog *ui;
    Console *m_console = nullptr;
    SettingsWidget *m_settings = nullptr;
    QSerialPort *m_serial = nullptr;
};

#endif // TERMINALDIALOG_H
