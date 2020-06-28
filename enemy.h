#ifndef ENEMY_H
#define ENEMY_H
#include <QObject>
#include <QPainter>
#include <QPoint>
#include <QSize>
#include <QPixmap>
#include"waypoint.h"
#include"gamewindow.h"
#include"circle.h"
#include"bullet.h"
class Tower;
class GameWindow;
class Bullet;

class Enemy : public QObject
{
    Q_OBJECT
public:
    Enemy(WayPoint *startWayPoint, GameWindow *game, const QPixmap &sprite = QPixmap(":/Enemy/RES/Enemy/normal-enemy.png"));
    ~Enemy();

    void draw(QPainter *painter) const;
    void move();
    void getDamage(Bullet *bullet);
    void getRemoved();
    void getAttacked(Tower *attacker);
    void gotLostSight(Tower *attacker);
    void canRemove();
    QPoint pos() const;

public slots:
    void doActivate();
    void firehurt();

protected:
    int             kind;
    bool			m_active;
    int				m_maxHp;
    int				m_currentHp;
    double          ice=1.0;
    int             fire=0;
    qreal			m_walkingSpeed;
    qreal           m_maxSpeed;
    qreal			m_rotationSprite;
    QTimer *        FireTimer;
    QPoint			m_pos;
    WayPoint *		m_destinationWayPoint;
    GameWindow *	m_game;
    QList<Tower *>	m_attackedTowersList;

    const QPixmap	m_sprite;
    static const QSize ms_fixedSize;
};

class NormalEnemy : public Enemy{
public:
    NormalEnemy(WayPoint *startWayPoint, GameWindow *game, const QPixmap &sprite = QPixmap(":/Enemy/RES/Enemy/normal-enemy.png"));
    ~NormalEnemy();
};

class DefendEnemy : public Enemy{
public:
    DefendEnemy(WayPoint *startWayPoint, GameWindow *game, const QPixmap &sprite = QPixmap(":/Enemy/RES/Enemy/defend-enemy.png"));
    ~DefendEnemy();
};

class BloodEnemy : public Enemy{
public:
    BloodEnemy(WayPoint *startWayPoint, GameWindow *game, const QPixmap &sprite = QPixmap(":/Enemy/RES/Enemy/quick-enemy.png"));
    ~BloodEnemy();
};

#endif // ENEMY_H
