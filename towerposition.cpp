#include "towerposition.h"
#include <QPushButton>

const QSize TowerPosition::ms_fixedSize(80,10);

TowerPosition::TowerPosition(QPoint pos, const QPixmap &pic/* = QPixmap(":/GameScene/RES/GameScene/towerpoint.png")*/)
    :m_pos(pos)
    ,m_hasTower(false)
    ,m_pic(pic)
    ,m_tower(NULL)
{
}
TowerPosition::TowerPosition(const TowerPosition &t)
    :m_pos(t.m_pos)
    ,m_hasTower(false)
    ,m_pic(t.m_pic)
    ,m_tower(NULL)
{
}
const QPoint TowerPosition::centerPos() const
{
    QPoint offsetPoint(ms_fixedSize.width() / 2, ms_fixedSize.height() / 2);
    return m_pos + offsetPoint;
}

bool TowerPosition::containPoint(const QPoint &pos) const
{
    bool isXInHere = m_pos.x() < pos.x() && pos.x() < (m_pos.x() + ms_fixedSize.width());
    bool isYInHere = m_pos.y() < pos.y() && pos.y() < (m_pos.y() + 5*ms_fixedSize.height());
    return isXInHere && isYInHere;
}

bool TowerPosition::hasTower() const
{
    return m_hasTower;
}

void TowerPosition::setHasTower(bool hasTower/* = true*/)
{
    m_hasTower = hasTower;
}
void TowerPosition::setNoTower(bool hasTower/*=false*/){
    m_hasTower = hasTower;
}

void TowerPosition::draw(QPainter *painter) const
{
    painter->drawPixmap(m_pos.x(), m_pos.y(), m_pic);
}
