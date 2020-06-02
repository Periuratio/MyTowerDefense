#ifndef MYBUTTON_H
#define MYBUTTON_H

#include <QWidget>
#include <QPushButton>

class MyButton : public QPushButton
{
    Q_OBJECT
public:
    MyButton(QString);
    void buttonup();
    void buttondown();
signals:

};

#endif // MYBUTTON_H
