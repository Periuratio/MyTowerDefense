#include "tower.h"
#include <QObject>
#include <QPoint>
#include <QPixmap>
#include <QPainter>
Tower::Tower(QPoint pos,QString pixfile):QObject(0),_pix(pixfile)
{
    _pos=pos;
}
void  Tower::draw(QPainter *painter){
    painter->drawPixmap(_pos,_pix);
}
