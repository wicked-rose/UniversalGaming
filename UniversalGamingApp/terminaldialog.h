#ifndef TERMINALDIALOG_H
#define TERMINALDIALOG_H

#include <QDialog>

namespace Ui {
class terminalDialog;
}

class terminalDialog : public QDialog
{
    Q_OBJECT

public:
    explicit terminalDialog(QWidget *parent = nullptr);
    ~terminalDialog();

private:
    Ui::terminalDialog *ui;
};

#endif // TERMINALDIALOG_H
