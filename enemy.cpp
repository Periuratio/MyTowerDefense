#include "enemy.h"
#include<QMediaPlayer>
class WayPoint;

const QSize Enemy::ms_fixedSize(80,80);
Enemy::Enemy(WayPoint *startWayPoint, GameWindow *game, const QPixmap &sprite)
    : QObject(0)
    , kind(0)
    , m_active(false)
    , m_maxHp(100)
    , m_currentHp(100)
    , m_walkingSpeed(1)
    , m_rotationSprite(0.0)
    , m_pos(startWayPoint->pos())
    , m_destinationWayPoint(startWayPoint->nextWayPoint())
    , m_game(game)
    , m_sprite(sprite)
{
    FireTimer = new QTimer(this);
    connect(FireTimer, SIGNAL(timeout()), this, SLOT(firehurt()));

}
Enemy::~Enemy(){

}

void Enemy::draw(QPainter *painter) const
{
    if (!m_active)
        return;

    //
    // 血条的长度
    // 其实就是2个方框,红色方框表示总生命,固定大小不变
    // 绿色方框表示当前生命,受m_currentHp / m_maxHp的变化影响
    static const int Health_Bar_Width = 30;
    painter->save();
    QPoint healthBarPoint = m_pos + QPoint(-Health_Bar_Width / 2 , -ms_fixedSize.height()*1.3);
    // 绘制血条
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::red);
    QRect healthBarBackRect(healthBarPoint, QSize(Health_Bar_Width, 2));
    painter->drawRect(healthBarBackRect);
    painter->setBrush(Qt::green);
    QRect healthBarRect(healthBarPoint, QSize((double)m_currentHp / m_maxHp * Health_Bar_Width, 2));
    painter->drawRect(healthBarRect);
    // 绘制偏转坐标,由中心+偏移=左上
    static const QPoint offsetPoint(-ms_fixedSize.width() / 2, -ms_fixedSize.height()*1.2);
    painter->translate(m_pos);
    painter->rotate(m_rotationSprite);
    painter->drawPixmap(offsetPoint, m_sprite);
    painter->restore();
}

void Enemy::move()
{
    if (!m_active)
        return;
    if (collisionWithCircle(m_pos, 1, m_destinationWayPoint->pos(), 1))
    {
        // 敌人抵达了一个航点
        if (m_destinationWayPoint->nextWayPoint())
        {
            // 还有下一个航点
            m_pos = m_destinationWayPoint->pos();
            m_destinationWayPoint = m_destinationWayPoint->nextWayPoint();
        }
        else
        {
            // 表示进入基地
            m_game->getHpDamage();
            m_game->removedEnemy(this);
            return;
        }
    }
    // 还在前往航点的路上
    // 目标航点的坐标
    QPoint targetPoint = m_destinationWayPoint->pos();
    // 未来修改这个可以添加移动状态,加快,减慢,m_walkingSpeed是基准值
    // 向量标准化
    double movementSpeed = m_walkingSpeed*this->ice;
    QVector2D normalized(targetPoint - m_pos);
    normalized.normalize();
    m_pos = m_pos + normalized.toPoint() * movementSpeed;
    // 确定敌人选择方向
    // 默认图片向左,需要修正180度转右
    m_rotationSprite = qRadiansToDegrees(qAtan2(normalized.y(), normalized.x())) + 180;
}

void Enemy::doActivate()
{
    m_active = true;
}
void Enemy::firehurt(){
    m_currentHp-=fire;
}

void Enemy::getRemoved()
{
    if (m_attackedTowersList.empty())
        return;

    foreach (Tower *attacker, m_attackedTowersList)
        attacker->targetKilled();
    // 通知game,此敌人已经阵亡
    m_game->removedEnemy(this);
}

void Enemy::canRemove()
{
        //m_game->audioPlayer()->playSound(EnemyDestorySound);
        m_game->m_money+=100;
        getRemoved();
}

void Enemy::getDamage(Bullet *bullet){
    m_currentHp -=bullet->m_damage;
    if(this->kind==1)
    m_currentHp += 10;//DefendEnemy拥有额外10点防御力
    switch(bullet->bulletKind)
    {
        case 1:
        {
            fire=bullet->fire_attack;
            this->FireTimer->start(1000);
        }
        case 2:
        {
            this->ice=bullet->ice;
        }
        default:
            break;
    }
    if(m_currentHp<=0)
    canRemove();
}

QPoint Enemy::pos() const
{
    return m_pos;
}

void Enemy::getAttacked(Tower *attacker)
{
    m_attackedTowersList.push_back(attacker);
}

// 表明敌人已经逃离了攻击范围
void Enemy::gotLostSight(Tower *attacker)
{
    m_attackedTowersList.removeOne(attacker);
}

//********************************************************************************************
NormalEnemy::NormalEnemy(WayPoint *startWayPoint, GameWindow *game, const QPixmap &sprite)
    :Enemy(startWayPoint,game,sprite)
{

}
NormalEnemy::~NormalEnemy(){

}

DefendEnemy::DefendEnemy(WayPoint *startWayPoint, GameWindow *game, const QPixmap &sprite)
    :Enemy(startWayPoint,game,sprite)
{
    this->kind=1;
}
DefendEnemy::~DefendEnemy(){
}

BloodEnemy::BloodEnemy(WayPoint *startWayPoint, GameWindow *game, const QPixmap &sprite)
    :Enemy(startWayPoint,game,sprite)
{
    m_maxHp=150;
    m_currentHp=150;
}
BloodEnemy::~BloodEnemy(){
}
