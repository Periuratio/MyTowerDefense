#include "easywindow.h"
#include "mybutton.h"
#include"towerposition.h"
#include<QPainter>
#include<QPixmap>
#include<QPaintEvent>
#include<QPushButton>
void EasyWindow::loadTowerPositions()
{
    QPoint pos[] =
    {
        QPoint(488,623),
        QPoint(463,245),
        QPoint(463,393),
        QPoint(543,483),
        QPoint(547,623),
        QPoint(623,243),
        QPoint(618,393),
        QPoint(772,243),
        QPoint(772,393),
        QPoint(853,163),
        QPoint(923,403)
    };
    int len	= sizeof(pos) / sizeof(pos[0]);

    for (int i = 0; i < len; ++i)
        m_TowerPositionsList.push_back(TowerPosition(pos[i]));
}
EasyWindow::EasyWindow(QWidget *parent) : QMainWindow(parent)
{
    this->setFixedSize(1024,682);
    this->loadTowerPositions();
    //返回按钮，也许用不上
    //MyButton * back_btn = new MyButton(":/GameScene/RES/GameScene/BackB.png");
    //back_btn->setParent(this);
    //back_btn->move(600,1100);
    //connect(back_btn,&MyButton::clicked,this,[=](){emit chooseBack();
    //});
}
void EasyWindow::paintEvent(QPaintEvent*){
    QPainter painter(this);
    QPixmap pixmap(":/GameScene/RES/GameScene/SE.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pixmap);
}


