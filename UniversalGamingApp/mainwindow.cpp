#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "customtabstyle.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->menuTabWidget->tabBar()->setStyle(new CustomTabStyle);
}

MainWindow::~MainWindow()
{
    delete ui;
}

