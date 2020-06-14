#ifndef TOWERPOSITION_H
#define TOWERPOSITION_H

#include <QObject>
#include<QPoint>
#include<QPainter>

class TowerPosition
{
public:
    TowerPosition(QPoint pos, const QPixmap &sprite = QPixmap(":/GameScene/RES/GameScene/towerpoint.png"));


    const QPoint centerPos() const;
    void draw(QPainter *painter) const;
    void setHasTower(int hasTower=1);
    bool hasTower() const;
    bool containPoint(const QPoint &pos) const;

private:
    QPoint		m_pos;
    bool m_hasTower;
    QPixmap		m_pic;

    static const QSize ms_fixedSize;
};

#endif // TOWERPOSITION_H
