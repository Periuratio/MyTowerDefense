#ifndef TOWER_H
#define TOWER_H
#include <QPoint>
#include <QSize>
#include <QPixmap>
#include <QObject>
#include <QPushButton>
#include <QAction>
#include"gamewindow.h"
#include"bullet.h"
class QPainter;
class Enemy;
class GameWindow;
class QTimer;

class Tower:public QObject{
        Q_OBJECT
public:
    Tower(QPoint pos,GameWindow *game, const QPixmap &sprite = QPixmap(":/Tower/RES/Tower/NT.png"), int attackRange = 120, int damage = 10, int fireRate = 300,int level=1);
    ~Tower();
    virtual void draw(QPainter *) const;
    virtual void levelup()=0;
    void attackEnemy();
    void chooseEnemyForAttack(Enemy *enemy);
    void targetKilled();
    void lostSightOfEnemy();
    void checkEnemyInRange();
    void damageEnemy();
    int             m_level;
public slots:
    virtual void shootWeapon()=0;

protected:
    QTimer *		m_fireRateTimer;
    int				m_attackRange;
    int				m_damage;
    int				m_fireRate;
    GameWindow *    m_game;
    const QPoint	m_pos;
    const QPixmap	m_sprite;
    static const QSize ms_fixedSize;
    Enemy *         m_chooseEnemy;
};

class NormalTower:public Tower{
    Q_OBJECT
public:
    NormalTower(QPoint pos,GameWindow *game, const QPixmap &sprite = QPixmap(":/Tower/RES/Tower/NT.png"));
    ~NormalTower();
    const int m_cost;
    virtual void levelup();
public slots:
    void shootWeapon();

protected:
    const QPixmap	m_sprite;
};

class FireTower:public Tower{
    Q_OBJECT
public:
    FireTower(QPoint pos,GameWindow *game, const QPixmap &sprite = QPixmap(":/Tower/RES/Tower/FT.png"));
    ~FireTower();
    const int m_cost;
    virtual void levelup();
public slots:
    void shootWeapon();

protected:
    int fireattack;
    const QPixmap	m_sprite;
};

class IceTower:public Tower{
    Q_OBJECT
public:
    IceTower(QPoint pos,GameWindow *game, const QPixmap &sprite = QPixmap(":/Tower/RES/Tower/IT.png"));
    ~IceTower();
    const int m_cost;
    virtual void levelup();
public slots:
    void shootWeapon();

protected:
    double slowspeed;
    const QPixmap	m_sprite;
};

#endif // TOWER_H
