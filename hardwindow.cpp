#include "hardwindow.h"
#include<QPainter>
#include<QPixmap>
#include<QPaintEvent>
#include<QPushButton>
#include"mybutton.h"
HardWindow::HardWindow(QWidget *parent) : QMainWindow(parent)
{
    this->setFixedSize(1024,682);
    //返回按钮，也许用不上
    //MyButton * back_btn = new MyButton(":/GameScene/RES/GameScene/BackB.png");
    //back_btn->setParent(this);
    //back_btn->move(600,1100);
    //connect(back_btn,&MyButton::clicked,this,[=](){emit chooseBack();
    //});
}
void HardWindow::paintEvent(QPaintEvent*){
    QPainter painter(this);
    QPixmap pixmap(":/GameScene/RES/GameScene/SH.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pixmap);
}
