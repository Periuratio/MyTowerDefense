#ifndef BULLET_H
#define BULLET_H

#include <QPoint>
#include <QSize>
#include <QPixmap>
#include <QObject>
#include"gamewindow.h"

class QPainter;
class Enemy;
class GameWindow;

class Bullet : public QObject
{
    Q_OBJECT
    //Qt动画效果
    Q_PROPERTY(QPoint m_currentPos READ currentPos WRITE setCurrentPos)
public:
    Bullet(QPoint startPos, QPoint targetPoint, int damage, Enemy *target, GameWindow *game, int fire = 0, qreal slow = 1,int kind = 0,  const QPixmap &sprite = QPixmap(":/Tower/RES/Tower/NB.png"));
    void draw(QPainter *painter) const;
    void move();
    void setCurrentPos(QPoint pos);
    QPoint currentPos() const;
    friend class Enemy;

protected slots:
    void hitTarget();

protected:
    const QPoint	m_startPos;
    const QPoint	m_targetPos;
    const QPixmap	m_sprite;
    QPoint			m_currentPos;
    Enemy *			m_target;
    GameWindow *    m_game;
    int				m_damage;
    int             bulletKind;
    int             fire_attack;
    qreal           ice;

    static const QSize ms_fixedSize;
};
class NormalBullet:public Bullet{
public:
    NormalBullet(QPoint startPos, QPoint targetPoint, int damage, Enemy *target, GameWindow *game);
};

class FireBullet: public Bullet{
public:
    FireBullet(QPoint startPos, QPoint targetPoint, int damage, Enemy *target, GameWindow *game,int fireattack ,qreal slow=1,int kind = 1, const QPixmap &sprite = QPixmap(":/Tower/RES/Tower/FB.png"));
};


class IceBullet: public Bullet{
public:
    IceBullet(QPoint startPos, QPoint targetPoint, int damage, Enemy *target, GameWindow *game,int fireattack=0, qreal slow=0.9, int kind = 2, const QPixmap &sprite = QPixmap(":/Tower/RES/Tower/IB.png"));
};

#endif // BULLET_H
