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
    //back_btn->move(600,1100);
    //connect(back_btn,&MyButton::clicked,this,[=](){emit chooseBack();
    //});
    MyButton * setTower = new MyButton("//按钮图片路径");
    setTower->setParent(this);
    setTower->move(500,500);
    connect(setTower,&MyButton::clicked,this,&GameWindow::set_tower);
}
void GameWindow::paintEvent(QPaintEvent*){
    QPainter painter(this);
    QPixmap pixmap(":/GameScene/RES/GameScene/S1.jpg");
    painter.drawPixmap(0,0,this->width(),this->height(),pixmap);

}
void GameWindow::set_tower(){
    Tower * a_new_tower=new Tower(QPoint(200,200),"//塔路径");
    tower_list.push_back(a_new_tower);
}
