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
      m_layout(new ControllerLayout)
{
    m_ui->setupUi(this);
    m_ui->menuTabWidget->tabBar()->setStyle(new CustomTabStyle);
    connect(m_ui->applyButton, &QPushButton::clicked,
            this, &MainWindow::apply);
};

MainWindow::~MainWindow()
{
    delete m_ui;
}

void MainWindow::apply()
{
    //qDebug() << "apply clicked";
    m_settings->updateSettings();
    //qDebug() << "Updated Baud: " << m_settings->settings().baudRate;
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

