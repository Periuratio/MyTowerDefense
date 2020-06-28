#ifndef TOWERPOSITION_H
#define TOWERPOSITION_H
#include <QObject>
#include<QPoint>
#include<QPainter>
#include <QPushButton>
#include"tower.h"
#include"mybutton.h"
class Tower;
class TowerPosition{
public:
    TowerPosition(QPoint pos, const QPixmap &sprite = QPixmap(":/GameScene/RES/GameScene/towerpoint.png"));
    TowerPosition(const TowerPosition &);
    const QPoint centerPos() const;
    void draw(QPainter *painter) const;
    void setHasTower(bool hasTower=true);
    void setNoTower(bool hasTower=false);
    bool hasTower() const;
    bool containPoint(const QPoint &pos) const;

    QPoint		m_pos;
    bool m_hasTower;
    QPixmap		m_pic;
    static const QSize ms_fixedSize;
    Tower* m_tower;
};

#endif // TOWERPOSITION_H
