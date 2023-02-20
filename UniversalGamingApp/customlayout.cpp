#include "customlayout.h"
#include "ui_customlayout.h"

CustomLayout::CustomLayout(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CustomLayout)
{
    ui->setupUi(this);
}

CustomLayout::~CustomLayout()
{
    delete ui;
}

void addOptions(){
    // for each box in boxes
    QString thisBox = "1";
    ui->box1->addItem(QStringLiteral("Button 2"), QStringLiteral("remap "+thisBox+" 2"));
}
