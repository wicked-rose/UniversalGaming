#ifndef CUSTOMLAYOUT_H
#define CUSTOMLAYOUT_H

#include <QWidget>

namespace Ui {
class CustomLayout;
}

class CustomLayout : public QWidget
{
    Q_OBJECT

public:
    explicit CustomLayout(QWidget *parent = nullptr);
    ~CustomLayout();
    void addOptions();

private:
    Ui::CustomLayout *ui = nullptr;
};

#endif // CUSTOMLAYOUT_H
