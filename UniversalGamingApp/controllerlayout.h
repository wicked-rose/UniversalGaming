#ifndef CONTROLLERLAYOUT_H
#define CONTROLLERLAYOUT_H

#include <QWidget>

namespace Ui {
class ControllerLayout;
}

class ControllerLayout : public QWidget
{
    Q_OBJECT

public:
    explicit ControllerLayout(QWidget *parent = nullptr);
    ~ControllerLayout();
    void fillLayoutOptions();
    void setControllerLayout(int index);
    void select();

private:
    Ui::ControllerLayout *ui;
    int currLayout;
};

#endif // CONTROLLERLAYOUT_H
