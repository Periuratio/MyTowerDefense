#include "tower.h"
#include "gamewindow.h"
#include "circle.h"
#include <QPainter>
#include <QColor>
#include <QTimer>
#include <QVector2D>
#include <QtMath>
#include <QPushButton>
#include<QMediaPlayer>
const QSize Tower::ms_fixedSize(80,80);

Tower::Tower(QPoint pos,GameWindow *game, const QPixmap &sprite, int attackRange, int damage, int fireRate,int level)
    : m_level(level),
      m_attackRange(attackRange),
      m_damage(damage),
      m_fireRate(fireRate),
      m_game(game),
      m_pos(pos),
      m_sprite(sprite),
      m_chooseEnemy(NULL)
{

    m_fireRateTimer = new QTimer(this);
    connect(m_fireRateTimer, SIGNAL(timeout()), this, SLOT(shootWeapon()));

    QMediaPlayer *bgm=new QMediaPlayer;
    bgm->setMedia(QUrl("C:/Users/12580/Desktop/Code/MyTowerDefense/music/tower_place.wav"));
    bgm->setVolume(80);
    bgm->play();

}
Tower::~Tower()
{
}

void Tower::draw(QPainter *painter) const{
    painter->save();
    static const QPoint offsetPoint(-ms_fixedSize.width() / 2, -ms_fixedSize.height()*1.5);
    painter->translate(m_pos);
    painter->drawPixmap(offsetPoint, m_sprite);
    painter->restore();
}
void Tower::checkEnemyInRange()
{

    if (m_chooseEnemy)
    {
        if (!collisionWithCircle(m_pos, m_attackRange, m_chooseEnemy->pos(), 1))
        {   lostSightOfEnemy();
            }
    }
    else
    {
        // 遍历敌人,看是否有敌人在攻击范围内
        foreach (Enemy *enemy, m_game->m_enemyList)
        {
            if (collisionWithCircle(m_pos, m_attackRange, enemy->pos(), 1))
            {
                chooseEnemyForAttack(enemy);

                break;
            }
        }
    }
}

void Tower::attackEnemy()
{
    m_fireRateTimer->start(m_fireRate);
}
void Tower::chooseEnemyForAttack(Enemy *enemy)
{
    // 选择敌人,同时设置对敌人开火
    m_chooseEnemy = enemy;
    // 这里启动timer,开始打炮
    attackEnemy();
    // 敌人自己要关联一个攻击者,这个用QList管理攻击者,因为可能有多个
    m_chooseEnemy->getAttacked(this);
}
void Tower::shootWeapon()
{

    Bullet *bullet = new Bullet(m_pos, m_chooseEnemy->pos(), m_damage, m_chooseEnemy, m_game);
    bullet->move();
    m_game->addBullet(bullet);
}
void Tower::targetKilled()
{
    if (m_chooseEnemy)
        m_chooseEnemy = NULL;
    m_fireRateTimer->stop();
}
void Tower::lostSightOfEnemy()
{
    m_chooseEnemy->gotLostSight(this);
    if (m_chooseEnemy)
        m_chooseEnemy = NULL;
    m_fireRateTimer->stop();
}

//******************************************************************************************
NormalTower::NormalTower(QPoint pos,GameWindow *game, const QPixmap &sprite)
    : Tower(pos, game,sprite),
      m_cost(100)
{
}

NormalTower::~NormalTower()
{
}

void NormalTower::shootWeapon()
{
    Bullet *bullet = new NormalBullet(m_pos, m_chooseEnemy->pos(), m_damage, m_chooseEnemy, m_game);
    bullet->move();
    m_game->addBullet(bullet);
}

void NormalTower::levelup()
{
    if (m_level < 5)
    {m_level++;
    m_damage += 5;
    m_game->m_money-=50;}
}

FireTower::FireTower(QPoint pos,GameWindow *game, const QPixmap &sprite)
    : Tower(pos, game,sprite),
      m_cost(150),
      fireattack(5)
{
    m_damage=15;
}
FireTower::~FireTower()
{

}

void FireTower::levelup()
{
    if (m_level < 5)
    {m_level++;
    m_damage += 5;
    fireattack += 1;
    m_game->m_money-=50;
    }
}

void FireTower::shootWeapon()
{

    Bullet *bullet = new FireBullet(m_pos, m_chooseEnemy->pos(), m_damage, m_chooseEnemy, m_game,fireattack);
    bullet->move();
    m_game->addBullet(bullet);
}
IceTower::IceTower(QPoint pos,GameWindow *game, const QPixmap &sprite)
    : Tower(pos, game,sprite),
      m_cost(150),
      slowspeed(0.8)
{
    m_damage=15;
}

IceTower::~IceTower()
{

}

void IceTower::levelup()
{
    if (m_level <5)
    {m_level++;
    m_damage += 5;
    this->slowspeed -= 0.1;
    m_game->m_money-=50;}
}

void IceTower::shootWeapon()
{
    Bullet *bullet = new IceBullet(m_pos, m_chooseEnemy->pos(), m_damage, m_chooseEnemy, m_game,0,slowspeed);
    bullet->move();
    m_game->addBullet(bullet);
}


