#include "terminaldialog.h"
#include "ui_terminaldialog.h"

terminalDialog::terminalDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::terminalDialog)
{
    ui->setupUi(this);
}

terminalDialog::~terminalDialog()
{
    delete ui;
}
