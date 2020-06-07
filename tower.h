#ifndef TOWER_H
#define TOWER_H

#include <QObject>
#include <QPoint>
#include <QPixmap>

class Tower : public QObject
{
    Q_OBJECT
public:
    Tower(QPoint pos,QString pixfile);
    void draw(QPainter * painter);
private:
    QPoint _pos;
    QPixmap _pix;
signals:

};

#endif // TOWER_H
