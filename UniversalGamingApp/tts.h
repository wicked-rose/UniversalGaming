#pragma once

#include <QApplication>
#include <QPushButton>
#include <QTextToSpeech>
#include <QComboBox>



class tts : public QObject
{
    Q_OBJECT

public:
    explicit tts(QPushButton *button, QObject *parent = nullptr)
        : QObject(parent)
        , m_button(button)
    {
        // Install an event filter on the button to track hover events
        m_button->installEventFilter(this);

        // Create the text-to-speech object
        m_tts = new QTextToSpeech();
    }

    bool eventFilter(QObject *obj, QEvent *event) override
    {
        if (obj == m_button) {
            if (event->type() == QEvent::HoverEnter or event->type() == QEvent::FocusIn) {
                // Get the text of the button and speak it
                QString text = m_button->text();
                m_tts->say(text);
            } else if (event->type() == QEvent::HoverLeave  or event->type() == QEvent::FocusOut) {
                // Stop any speech in progress
                m_tts->stop();
            }
        }
        else if (obj == m_box) {
            if (event->type() == QEvent::HoverEnter or event->type() == QEvent::FocusIn) {
                // Get the text of the button and speak it
                QString text = m_box->currentText();
                m_tts->say(text);
            } else if (event->type() == QEvent::HoverLeave  or event->type() == QEvent::FocusOut) {
                // Stop any speech in progress
                m_tts->stop();
            }
        }

        // Pass the event to the parent event filter
        return QObject::eventFilter(obj, event);
    }

    explicit tts(QComboBox *box, QObject *parent = nullptr)
        : QObject(parent)
        , m_box(box)
    {
        // Install an event filter on the button to track hover events
        m_box->installEventFilter(this);

        // Create the text-to-speech object
        m_tts = new QTextToSpeech();
    }

private:
    QPushButton *m_button;
    QComboBox *m_box;
    QTextToSpeech *m_tts;
};
//class tts
//{
//public:
//    tts();
//};

