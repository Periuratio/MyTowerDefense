#include "bullet.h"
#include "enemy.h"
#include "gamewindow.h"
#include <QPainter>
#include <QPropertyAnimation>

const QSize Bullet::ms_fixedSize(26, 26);

Bullet::Bullet(QPoint startPos, QPoint targetPoint, int damage, Enemy *target, GameWindow *game, int fire , qreal slow ,int kind,  const QPixmap &sprite)
    : QObject(0)
    , m_startPos(startPos)
    , m_targetPos(targetPoint)
    , m_sprite(sprite)
    , m_currentPos(startPos)
    , m_target(target)
    , m_game(game)
    , m_damage(damage)
    , bulletKind(kind)
    , fire_attack(fire)
    , ice(slow)
{

}


void Bullet::move()
{
    // 300毫秒内击中敌人
    static const int duration = 300;
    QPropertyAnimation *animation = new QPropertyAnimation(this, "m_currentPos");
    animation->setDuration(duration);
    animation->setStartValue(m_startPos);
    animation->setEndValue(m_targetPos);
    connect(animation, SIGNAL(finished()), this, SLOT(hitTarget()));

    animation->start();
}


void Bullet::hitTarget()
{
    if (m_game->enemyList().indexOf(m_target) != -1)
        m_target->getDamage(this);
    m_game->removedBullet(this);
}

void Bullet::setCurrentPos(QPoint pos)
{
    m_currentPos = pos;
}

QPoint Bullet::currentPos() const
{
    return m_currentPos;
}

void Bullet::draw(QPainter *painter) const
{
    painter->drawPixmap(m_currentPos, m_sprite);
}
//*********************************************************************
NormalBullet::NormalBullet(QPoint startPos, QPoint targetPoint, int damage, Enemy *target, GameWindow *game)
    :Bullet(startPos, targetPoint, damage, target, game)
{
    bulletKind=0;
}

FireBullet::FireBullet(QPoint startPos, QPoint targetPoint, int damage, Enemy *target, GameWindow *game,int fireattack,qreal slow,int kind, const QPixmap &sprite)
    :Bullet(startPos, targetPoint, damage, target, game, fireattack, 1,kind, sprite)
{
    bulletKind=1;
    ice=slow;
    ice=1;
    m_damage+=5;
}

IceBullet::IceBullet(QPoint startPos, QPoint targetPoint, int damage, Enemy *target, GameWindow *game,int fireattack, qreal slow,int kind, const QPixmap &sprite)
    :Bullet(startPos, targetPoint, damage, target, game,  0, slow,kind, sprite)
{
    bulletKind=2;
    fire_attack=fireattack;
    fire_attack=0;
}
