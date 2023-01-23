#include "controllerlayout.h"
#include "ui_controllerlayout.h"

ControllerLayout::ControllerLayout(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ControllerLayout)
{
    ui->setupUi(this);

    connect(ui->selectLayoutBox, &QComboBox::currentIndexChanged,
            this, &ControllerLayout::setControllerLayout);
    connect(ui->selectButton, &QPushButton::clicked,
            this, &ControllerLayout::select);
}

ControllerLayout::~ControllerLayout()
{
    delete ui;
}

void ControllerLayout::fillLayoutOptions()
{
    ui->selectLayoutBox->addItem(QStringLiteral("1. Gamepad"));
    ui->selectLayoutBox->addItem(QStringLiteral("2. Keyboard"), 2);
    ui->selectLayoutBox->addItem(QStringLiteral("3. XBox"), 3);
}

void ControllerLayout::setControllerLayout(int index)
{
    if (index == -1)
        return;

   // const QString blankString = tr(::blankString);

   // const QStringList list = m_ui->selectLayoutBox->itemData(index).toStringList();
    ui->selectionLabel->setText(tr("Layout Selected: %1").arg(ui->selectLayoutBox->itemData(index).toString()));
}

void ControllerLayout::select()
{

}
