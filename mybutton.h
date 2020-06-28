#ifndef MYBUTTON_H
#define MYBUTTON_H

#include <QWidget>
#include <QPushButton>
#include <QPixmap>
#include <QAction>
#include"towerposition.h"
class QPainter;
class MyButton : public QPushButton
{
    Q_OBJECT
public:
    MyButton(QString);
    QPixmap		m_pic;
signals:

};

//这个TButton类在塔座处设置了一个隐形的button，从而通过右击塔座圆圈即可实现塔的安装、升级和拆除
class TButton :public QPushButton
{
    Q_OBJECT
public:
    TButton(QPoint pos,const QPixmap &pic = QPixmap(":/GameScene/RES/GameScene/towerbutton.png"));
    //void draw(QPainter *) const;
    QPoint m_pos;
    QPixmap m_pic;
    QList<QAction*>m_ActionsList;
signals:
    void showLevel();
    void setNormalTower();
    void setFireTower();
    void setIceTower();
    void sellTower();
    void Levelup();

};

#endif // MYBUTTON_H
