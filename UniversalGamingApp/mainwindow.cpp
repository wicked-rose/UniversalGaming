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


tts *TTS_button;
tts *CB_button ;

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
    connect(this, &MainWindow::showFullScreen, this, &MainWindow::onShowFullScreen);
    connect(this, &MainWindow::showNormal, this, &MainWindow::onShowNormal);

//    connect(this, &QMainWindow::changeEvent, this, [this](QEvent* event){
//        if(event->type() == QEvent::WindowStateChange){
//            QWindowStateChangeEvent *stateEvent = static_cast<QWindowStateChangeEvent*>(event);
//            if(stateEvent->oldState() != stateEvent->newState() && stateEvent->newState() & Qt::WindowFullScreen){
//                qDebug() << "Fullscreen";
//                //                QFont font = QApplication::font();
//                //                font.setPointSize(font.pointSize() * 2);
//                //                QApplication::setFont(font);
//            }

//            else {
//                // The window is not in fullscreen mode
//                // Set the font size back to its default
//               // QApplication::setFont(QApplication::font());
//                qDebug() << "No Fullsrceen";
//            }
//    });
        if(this->windowState() & Qt::WindowFullScreen){
            qDebug() << "Fullscreen";
        }
    m_ui->statusBar->show();
    //displayStatusMessage("Ready...");

//    for (int i = 0; i < m_ui->menuTabWidget->tabBar()->count(); i++) {
//        QWidget* button = m_ui->menuTabWidget->tabBar()->tabButton(i, QTabBar::LeftSide);
//        tts* tab_buttons = new tts(button, nullptr, "Test");
//    }

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
        TTS_button = new tts(m_ui->pushButton);
        CB_button = new tts(m_ui->ColorBlindMode);
        m_ui->pushButton->setText("Text to Speech (ON)");
    }
    else {
        QTextToSpeech *text_to_speech = new QTextToSpeech();
        text_to_speech->say("Text to Speech disabled");
        m_ui->pushButton->setText("Text to Speech (OFF)");
        delete TTS_button;
        delete CB_button;
    }
}

void MainWindow::displayStatusMessage(QString message){
    m_ui->statusBar->showMessage(message);
}

void MainWindow::onShowFullScreen()
{
    qDebug() << "Main window is now in full screen";
}

void MainWindow::onShowNormal()
{
    qDebug() << "Main window is no longer in full screen";
}

