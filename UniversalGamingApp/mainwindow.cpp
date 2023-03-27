#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "customtabstyle.h"
#include "qlayout.h"
#include "controllerlayout.h"
#include "customlayout.h"
#include "tts.h"
#include "global.h"

#include <QSerialPort>
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      m_ui(new Ui::MainWindow),
      m_console(new Console),
      m_settings(new SettingsWidget),
      m_layout(new ControllerLayout),
      m_custom(new CustomLayout)
{
    m_ui->setupUi(this);
    m_ui->menuTabWidget->tabBar()->setStyle(new CustomTabStyle);
    connect(m_ui->applyButton, &QPushButton::clicked,
            this, &MainWindow::apply);

    connect(m_layout, SIGNAL(sendStatus(QString)), this, SLOT(displayStatusMessage(QString)));
    //connect(m_custom, SIGNAL(sendStatus(QString)), this, SLOT(displayStatusMessage(QString)));

    m_ui->statusBar->show();
    //displayStatusMessage("Ready...");
};

MainWindow::~MainWindow()
{
    delete m_ui;
}

void MainWindow::apply()
{
    m_settings->updateSettings();
    terminalWindow *win = new terminalWindow(this, m_settings);
    if(win != nullptr){
        win->show();
    }
}

void MainWindow::on_pushButton_clicked()
{
    Global::isEnabled = !Global::isEnabled;
    if(Global::isEnabled){
        // Create the text-to-speech object
        QTextToSpeech *text_to_speech = new QTextToSpeech();
        text_to_speech->say("Text to Speech enabled");
        tts *TTS_button = new tts(m_ui->pushButton);
        tts *CB_button = new tts(m_ui->ColorBlindMode);
    }
    else {
        QTextToSpeech *text_to_speech = new QTextToSpeech();
        text_to_speech->say("Text to Speech disabled");
    }
}

void MainWindow::displayStatusMessage(QString message){
    m_ui->statusBar->showMessage(message);
}

