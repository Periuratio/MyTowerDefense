#include "gamewindow.h"
#include "mybutton.h"
#include<QPainter>
#include<QPixmap>
#include<QPaintEvent>
#include<QPushButton>
#include"mybutton.h"
GameWindow::GameWindow(QWidget *parent) : QMainWindow(parent)
{
    this->setFixedSize(1200,800);
    //返回按钮，也许用不上
    //MyButton * back_btn = new MyButton(":/GameScene/RES/GameScene/BackB.png");
    //back_btn->setParent(this);
    //back_btn->move(40,40);
    //connect(back_btn,&MyButton::clicked,this,[=](){emit chooseBack();
    //});

}
void GameWindow::paintEvent(QPaintEvent*){
    QPainter painter(this);
    QPixmap pixmap(":/GameScene/RES/GameScene/S1.jpg");
    painter.drawPixmap(0,0,this->width(),this->height(),pixmap);
}
