#ifndef TOWERE_H
#define TOWERE_H
#include <QPoint>
#include <QSize>
#include <QPixmap>
#include <QObject>
#include <QPushButton>
#include"easywindow.h"
class QPainter;
class Enemy;
class EasyWindow;
class QTimer;

class TowerE : public QPushButton
{
    Q_OBJECT
public:
    TowerE(QPoint pos,EasyWindow *game, const QPixmap &sprite = QPixmap(":/image/normaltower.png"), int attackRange = 120, int damage = 10, int fireRate = 300, int level = 1);
    ~TowerE();

    virtual void draw(QPainter *painter) const;
    void checkEnemyInRange();
    void targetKilled();
    void attackEnemy();
    void chooseEnemyForAttack(Enemy *enemy);
    void damageEnemy();
    void lostSightOfEnemy();

    //炮塔升级
    virtual void levelup() = 0;
    int             m_level;        // 等级

protected slots:
    //不同派生类（不同塔）需要发射不同子弹，需要虚函数
    virtual void shootWeapon() = 0;

protected:
    bool			m_attacking;
    qreal			m_rotationSprite;

    Enemy *			m_chooseEnemy;
    EasyWindow *        m_game;
    QTimer *		m_fireRateTimer;

    int				m_attackRange;	// 代表塔可以攻击到敌人的距离
    int				m_damage;		// 代表攻击敌人时造成的伤害
    int				m_fireRate;		// 代表再次攻击敌人的时间间隔

    const QPoint	m_pos; //塔的圆心
    const QPixmap	m_sprite;

    static const QSize ms_fixedSize;
};

class NormalTowerE: public TowerE
{
    Q_OBJECT
public:
    NormalTowerE(QPoint pos, EasyWindow *game, const QPixmap &sprite = QPixmap(":/image/normaltower.png"));
    ~NormalTowerE();

    void levelup();

protected slots:
    virtual void shootWeapon();
};

class FireTowerE : public TowerE
{
    Q_OBJECT
public:
    FireTowerE(QPoint pos, EasyWindow *game, const QPixmap &sprite = QPixmap(":/image/firetower.png"));
    ~FireTowerE();

    void levelup();

protected slots:
    virtual void shootWeapon();

private:
    int fireattack; //每秒的灼烧伤害
};

class IceTowerE : public TowerE
{
    Q_OBJECT
public:
    IceTowerE(QPoint pos, EasyWindow *game, const QPixmap &sprite = QPixmap(":/image/icetower.png"));
    ~IceTowerE();

    void levelup();

protected slots:
    virtual void shootWeapon();

private:
    double slowspeed; //减慢速度百分比
};
#endif // TOWER_H
