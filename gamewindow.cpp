#include "gamewindow.h"
#include "mybutton.h"
#include"towerposition.h"
#include<QPainter>
#include<QPixmap>
#include<QPaintEvent>
#include<QPushButton>
#include<QMediaPlayer>
class Tower;
GameWindow::GameWindow(QWidget *parent) :
    QMainWindow(parent),
    m_waves(0)
{
    this->setFixedSize(1024,682);
    this->loadTowerPositions();
}
GameWindow::~GameWindow(){

}
void GameWindow::paintEvent(QPaintEvent*){
    QPainter painter(this);
    QPixmap pixmap(":/GameScene/RES/GameScene/SE.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pixmap);

    foreach (const TowerPosition &towerPos,m_TowerPositionsList)
        towerPos.draw(&painter);

    foreach (Tower *tower, m_TowersList)
        tower->draw(&painter);

}
void GameWindow::loadTowerPositions()
{
    QPoint pos[] =
    {
        QPoint(923,403)
    };
    int len	= sizeof(pos) / sizeof(pos[0]);

    for (int i = 0; i < len; ++i)
        m_TowerPositionsList.push_back(TowerPosition(pos[i]));
}


void GameWindow::addWayPoints()
{
    WayPoint *wayPoint1 = new WayPoint(QPoint(945,140));
    m_WayPointsList.push_back(wayPoint1);

    WayPoint *wayPoint2 = new WayPoint(QPoint(945,330));
    m_WayPointsList.push_back(wayPoint2);
    wayPoint2->setNextWayPoint(wayPoint1);

    WayPoint *wayPoint3 = new WayPoint(QPoint(410,330));
    m_WayPointsList.push_back(wayPoint3);
    wayPoint3->setNextWayPoint(wayPoint2);

    WayPoint *wayPoint4 = new WayPoint(QPoint(410,570));
    m_WayPointsList.push_back(wayPoint4);
    wayPoint4->setNextWayPoint(wayPoint3);

    WayPoint *wayPoint5 = new WayPoint(QPoint(750,570));
    m_WayPointsList.push_back(wayPoint5);
    wayPoint5->setNextWayPoint(wayPoint4);
}
void GameWindow::getHpDamage(int damage)
{
    m_life-=damage;
}
void GameWindow::removedEnemy(Enemy *enemy)
{
    Q_ASSERT(enemy);
    m_enemyList.removeOne(enemy);
    delete enemy;
    if (m_enemyList.empty())
    {
        ++m_waves; // 当前波数加1
        // 继续读取下一波
        if (!loadWave())
        {
            // 当没有下一波时，这里表示游戏胜利
            // 设置游戏胜利标志为true
            m_gameWin = true;
            // 游戏胜利转到游戏胜利场景
            // 这里暂时以打印处理
        }
    }
}
bool GameWindow::loadWave()
{
    if (m_waves >= 6)
        return false;
    WayPoint *startWayPoint = m_WayPointsList.back(); // 这里是个逆序的，尾部才是其实节点
    int enemyStartInterval[] = { 100, 500, 600, 1000, 3000, 6000 };
    for (int i = 0; i < 6; ++i)
    {
        Enemy *enemy = new Enemy(startWayPoint, this);
        m_enemyList.push_back(enemy);
        QTimer::singleShot(enemyStartInterval[i], enemy, SLOT(doActivate()));
    }
    return true;
}
QList<Enemy *> GameWindow::enemyList() const{
    return m_enemyList;
}

void GameWindow::removedBullet(Bullet *bullet)
{
    Q_ASSERT(bullet);

    m_BulletList.removeOne(bullet);
    delete bullet;
}

void GameWindow::addBullet(Bullet *bullet)
{
    Q_ASSERT(bullet);

    m_BulletList.push_back(bullet);
}
/****************************************************************************************/
EasyWindow::EasyWindow(QWidget *parent) :
    GameWindow(parent),
    m_money(5000),
    m_life(15),
    m_waves(0)
{
    this->setFixedSize(1024,682);
    this->loadTowerPositions();
    this->addWayPoints();


    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateMap()));
    timer->start(30);
    QTimer::singleShot(30, this, SLOT(gameStart()));

    MyButton * back_btn = new MyButton(":/GameScene/RES/GameScene/BackB.png");
    back_btn->setParent(this);
    back_btn->move(10,450);
    connect(back_btn,&MyButton::clicked,this,[=](){emit chooseBack();
    });

    TButton* setTower[m_TowerPositionsList.size()];
        for(int i = 0; i < m_TowerPositionsList.size(); i++)
        {
            setTower[i] = new TButton(m_TowerPositionsList[i].m_pos);
            setTower[i] -> setIcon(QPixmap());
            setTower[i] -> setParent(this);
            setTower[i] ->move(m_TowerPositionsList.at(i).m_pos);
            setTower[i]->setWindowOpacity(0.2);

            connect(setTower[i], &TButton::setNormalTower, this, [=]()
            {
                if(!m_TowerPositionsList[i].hasTower())
                    emit set_Tower(i,'N');
            });
            connect(setTower[i], &TButton::setFireTower, this, [=]()
            {
                if(!m_TowerPositionsList[i].hasTower())
                    emit set_Tower(i,'F');
            });
            connect(setTower[i], &TButton::setIceTower, this, [=]()
            {
                if(!m_TowerPositionsList[i].hasTower())
                    emit set_Tower(i,'I');
            });
            connect(setTower[i], &TButton::Levelup, this, [=]()
            {
                if(m_money>=50)
                    emit up_Tower(i);
            });
            connect(setTower[i], &TButton::sellTower, this, [=]()
            {
                    emit sell_Tower(i);
            });
        }

}
EasyWindow::~EasyWindow(){

}
void EasyWindow::loadTowerPositions()
{
    QPoint pos[] =
    {
        QPoint(290,410),
        QPoint(370,603),
        QPoint(445,220),
        QPoint(445,375),
        QPoint(520,455),
        QPoint(520,600),
        QPoint(597,220),
        QPoint(597,370),
        QPoint(752,220),
        QPoint(755,370),
        QPoint(825,175)

    };
    int len	= sizeof(pos) / sizeof(pos[0]);

    for (int i = 0; i < len; ++i)
    {
        m_TowerPositionsList.push_back(TowerPosition(pos[i]));
    }
}
void EasyWindow::addWayPoints()
{
    WayPoint *wayPoint1 = new WayPoint(QPoint(945,140));
    m_WayPointsList.push_back(wayPoint1);

    WayPoint *wayPoint2 = new WayPoint(QPoint(945,330));
    m_WayPointsList.push_back(wayPoint2);
    wayPoint2->setNextWayPoint(wayPoint1);

    WayPoint *wayPoint3 = new WayPoint(QPoint(410,330));
    m_WayPointsList.push_back(wayPoint3);
    wayPoint3->setNextWayPoint(wayPoint2);

    WayPoint *wayPoint4 = new WayPoint(QPoint(410,570));
    m_WayPointsList.push_back(wayPoint4);
    wayPoint4->setNextWayPoint(wayPoint3);

    WayPoint *wayPoint5 = new WayPoint(QPoint(750,570));
    m_WayPointsList.push_back(wayPoint5);
    wayPoint5->setNextWayPoint(wayPoint4);
}
void EasyWindow::paintEvent(QPaintEvent*){
    QPainter painter(this);
    QPixmap cachePix(":/GameScene/RES/GameScene/SE.png");
    QPainter cachePainter(&cachePix);
    drawMoney(&cachePainter);
    drawLife(&cachePainter);
    drawWave(&cachePainter);

    foreach (const TowerPosition &towerPos, m_TowerPositionsList)
        towerPos.draw(&cachePainter);
    foreach (Tower *tower, m_TowersList)
        {tower->draw(&cachePainter);
        }
    foreach (Enemy *enemy, m_enemyList)
        enemy->draw(&cachePainter);
    foreach (const Bullet *bullet, m_BulletList)
        bullet->draw(&cachePainter);
    painter.drawPixmap(0, 0, cachePix);
    if (m_gameEnded || m_gameWin)
    {
        QString text = m_gameEnded ? "YOU LOST!!!" : "YOU WIN!!!";
        QPainter painter(this);
        painter.setPen(QPen(Qt::red));
        painter.drawText(rect(), Qt::AlignCenter, text);
        return;
    }
    update();
}

void EasyWindow::drawMoney(QPainter *painter)
{
    QFont font("Arial",16,QFont::Bold,false);
    painter->setPen(QPen(Qt::white));
    painter->setFont(font);
    painter->drawText(QRect(20,50,200,200), QString("MONEY\n%1").arg(m_money));
}

void EasyWindow::drawLife(QPainter *painter)
{
    QFont font("Arial",16,QFont::Bold,false);
    painter->setPen(QPen(Qt::white));
    painter->setFont(font);
    painter->drawText(QRect(20,200,200,200), QString("LIFE\n%1").arg(m_life));
}

void EasyWindow::drawWave(QPainter *painter)
{
    QFont font("Arial",16,QFont::Bold,false);
    painter->setPen(QPen(Qt::white));
    painter->setFont(font);
    painter->drawText(QRect(20,350,200,200), QString("Wave\n%1").arg(6-m_waves));
}

void EasyWindow::set_Tower(int num,char type)
{
    switch (type)
    {
    case 'N':
    {
        NormalTower * a_new_tower = new
        NormalTower(m_TowerPositionsList.at(num).centerPos(), this);
        if(m_money<a_new_tower->m_cost)
        {
            delete [] a_new_tower;
            break;
        }
        m_TowerPositionsList[num].setHasTower(true);
        m_TowerPositionsList[num].m_tower=a_new_tower;
        m_TowersList.push_back(a_new_tower);
        m_money -= a_new_tower -> m_cost;
        update();
        break;
    }
    case 'F':
    {
        FireTower * a_new_tower = new FireTower(m_TowerPositionsList.at(num).centerPos(), this);
        if(m_money<a_new_tower->m_cost)
        {
            delete [] a_new_tower;
            break;
        }
        m_TowerPositionsList[num].setHasTower(true);
        m_TowerPositionsList[num].m_tower=a_new_tower;
        m_TowersList.push_back(a_new_tower);
        m_money -= a_new_tower -> m_cost;
        update();
        break;
    }
    case 'I':
    {
        IceTower * a_new_tower = new IceTower(m_TowerPositionsList.at(num).centerPos(), this);
        if(m_money<a_new_tower->m_cost)
        {
            delete [] a_new_tower;
            break;
        }
        m_TowerPositionsList[num].setHasTower(true);
        m_TowerPositionsList[num].m_tower=a_new_tower;
        m_TowersList.push_back(a_new_tower);
        m_money -= a_new_tower -> m_cost;
        update();
        break;
    }
    default:
        break;
    }
}
void EasyWindow::up_Tower(int num){
    if(m_TowerPositionsList[num].m_tower)
    {
        m_TowerPositionsList[num].m_tower->levelup();
        m_money-=50;
    }
}
void EasyWindow::sell_Tower(int num){
    if(m_TowerPositionsList[num].m_tower)
    {
        m_money+=80;
        Tower * removedtower=m_TowerPositionsList[num].m_tower;
        Q_ASSERT(removedtower);
        m_TowersList.removeOne(removedtower);
        delete removedtower;
        m_TowerPositionsList[num].m_tower=NULL;
        m_TowerPositionsList[num].setNoTower();
    }
}

void EasyWindow::doGameOver()
{
    if (!m_gameEnded)
    {
       if (m_life <= 0)
        m_gameEnded = true;
        // 此处应该切换场景到结束场景
        // 暂时以打印替代,见paintEvent处理
    }
}

bool EasyWindow::loadWave()
{
    if (m_waves >= 6)
        return false;
    WayPoint *startWayPoint = m_WayPointsList.back(); // 这里是个逆序的，尾部才是其实节点
    int enemyStartInterval[]={ 100*(7-m_waves), 300*(7-m_waves), 500*(7-m_waves), 700*(7-m_waves), 900*(7-m_waves), 1100*(7-m_waves),1300*(7-m_waves),1500*(7-m_waves),1700*(7-m_waves),1900*(7-m_waves),2100*(7-m_waves) };
    for (int i = 0; i < 6; ++i)
    {
        Enemy *enemy;
        int j=i%3;
        switch(j){
        case 0:
            enemy = new NormalEnemy(startWayPoint, this);
            break;
        case 1:
            enemy=new DefendEnemy(startWayPoint, this);
            break;
        case 2:
            enemy=new BloodEnemy(startWayPoint, this);
            break;
        }
        m_enemyList.push_back(enemy);
        QTimer::singleShot(enemyStartInterval[i], enemy, SLOT(doActivate()));
    }
    return true;
}

void EasyWindow::gameStart()
{
    loadWave();
}

void EasyWindow::updateMap()
{
    doGameOver();
    if(m_gameWin||m_gameEnded)
        return;
    else
    {
        foreach(Enemy *enemy, m_enemyList)
        enemy->move();
        foreach(Tower *tower, m_TowersList)
        tower->checkEnemyInRange();
        update();
    }
}
void EasyWindow::getHpDamage(int damage)

{
    QMediaPlayer * sound=new QMediaPlayer;
    sound->setMedia(QUrl("C:/Users/12580/Desktop/Code/MyTowerDefense/music/hplose.wav"));
    sound->setVolume(50);
    sound->play();
    m_life-=damage;
}
//********************************************************************

HardWindow::HardWindow(QWidget *parent) :
    GameWindow(parent),
    m_money(2000),
    m_life(9),
    m_waves(0)
{
    this->setFixedSize(1024,682);
    this->loadTowerPositions();
    this->addWayPoints();

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateMap()));
    timer->start(15);
    QTimer::singleShot(30, this, SLOT(gameStart()));

    MyButton * back_btn = new MyButton(":/GameScene/RES/GameScene/BackB.png");
    back_btn->setParent(this);
    back_btn->move(10,450);
    connect(back_btn,&MyButton::clicked,this,[=](){emit chooseBack();
    });

    TButton* setTower[m_TowerPositionsList.size()];
        for(int i = 0; i < m_TowerPositionsList.size(); i++)
        {
            setTower[i] = new TButton(m_TowerPositionsList[i].m_pos);
            setTower[i] -> setIcon(QPixmap());
            setTower[i] -> setParent(this);
            setTower[i] ->move(m_TowerPositionsList.at(i).m_pos);
            setTower[i]->setWindowOpacity(0.2);

            connect(setTower[i], &TButton::setNormalTower, this, [=]()
            {
                if(!m_TowerPositionsList[i].hasTower())
                    emit set_Tower(i,'N');
            });
            connect(setTower[i], &TButton::setFireTower, this, [=]()
            {
                if(!m_TowerPositionsList[i].hasTower())
                    emit set_Tower(i,'F');
            });
            connect(setTower[i], &TButton::setIceTower, this, [=]()
            {
                if(!m_TowerPositionsList[i].hasTower())
                    emit set_Tower(i,'I');
            });
            connect(setTower[i], &TButton::Levelup, this, [=]()
            {
                if(m_money>=50)
                    emit up_Tower(i);
            });
            connect(setTower[i], &TButton::sellTower, this, [=]()
            {
                    emit sell_Tower(i);
            });
        }

}
HardWindow::~HardWindow(){

}
void HardWindow::loadTowerPositions()
{
    QPoint pos[] =
    {
        QPoint(220,275),
        QPoint(220,420),
        QPoint(295,575),
        QPoint(360,110),
        QPoint(360,350),
        QPoint(455,260),
        QPoint(455,420),
        QPoint(455,580),
        QPoint(530,120),
        QPoint(600,425),
        QPoint(675,120),
        QPoint(675,270),
        QPoint(675,500),
        QPoint(750,45),
        QPoint(750,415),
        QPoint(830,190)

    };
    int len	= sizeof(pos) / sizeof(pos[0]);

    for (int i = 0; i < len; ++i)
    {
        m_TowerPositionsList.push_back(TowerPosition(pos[i]));
    }
}
void HardWindow::addWayPoints()
{
    WayPoint *wayPoint1 = new WayPoint(QPoint(900,145));
    m_WayPointsList.push_back(wayPoint1);

    WayPoint *wayPoint2 = new WayPoint(QPoint(790,145));
    m_WayPointsList.push_back(wayPoint2);
    wayPoint2->setNextWayPoint(wayPoint1);

    WayPoint *wayPoint3 = new WayPoint(QPoint(790,380));
    m_WayPointsList.push_back(wayPoint3);
    wayPoint3->setNextWayPoint(wayPoint2);

    WayPoint *wayPoint4 = new WayPoint(QPoint(640,380));
    m_WayPointsList.push_back(wayPoint4);
    wayPoint4->setNextWayPoint(wayPoint3);

    WayPoint *wayPoint5 = new WayPoint(QPoint(640,230));
    m_WayPointsList.push_back(wayPoint5);
    wayPoint5->setNextWayPoint(wayPoint4);

    WayPoint *wayPoint6 = new WayPoint(QPoint(330,230));
    m_WayPointsList.push_back(wayPoint6);
    wayPoint6->setNextWayPoint(wayPoint5);

    WayPoint *wayPoint7 = new WayPoint(QPoint(330,540));
    m_WayPointsList.push_back(wayPoint7);
    wayPoint7->setNextWayPoint(wayPoint6);

    WayPoint *wayPoint8 = new WayPoint(QPoint(635,540));
    m_WayPointsList.push_back(wayPoint8);
    wayPoint8->setNextWayPoint(wayPoint7);

    WayPoint *wayPoint9 = new WayPoint(QPoint(635,610));
    m_WayPointsList.push_back(wayPoint9);
    wayPoint9->setNextWayPoint(wayPoint8);

    WayPoint *wayPoint10 = new WayPoint(QPoint(900,610));
    m_WayPointsList.push_back(wayPoint10);
    wayPoint10->setNextWayPoint(wayPoint9);
}
void HardWindow::paintEvent(QPaintEvent*){
    QPainter painter(this);
    QPixmap cachePix(":/GameScene/RES/GameScene/SH.png");
    QPainter cachePainter(&cachePix);
    drawMoney(&cachePainter);
    drawLife(&cachePainter);
    drawWave(&cachePainter);
    foreach (const TowerPosition &towerPos, m_TowerPositionsList)
        towerPos.draw(&cachePainter);
    foreach (Tower *tower, m_TowersList)
        tower->draw(&cachePainter);
    foreach (Enemy *enemy, m_enemyList)
        enemy->draw(&cachePainter);
    foreach (const Bullet *bullet, m_BulletList)
        bullet->draw(&cachePainter);
    painter.drawPixmap(0, 0, cachePix);
    if (m_gameEnded || m_gameWin)
    {
        QString text = m_gameEnded ? "YOU LOST!!!" : "YOU WIN!!!";
        QPainter painter(this);
        painter.setPen(QPen(Qt::red));
        painter.drawText(rect(), Qt::AlignCenter, text);
        return;
    }
    update();
}

void HardWindow::drawMoney(QPainter *painter)
{
    QFont font("Arial",16,QFont::Bold,false);
    painter->setPen(QPen(Qt::white));
    painter->setFont(font);
    painter->drawText(QRect(20,50,200,200), QString("MONEY\n%1").arg(m_money));
}

void HardWindow::drawLife(QPainter *painter)
{
    QFont font("Arial",16,QFont::Bold,false);
    painter->setPen(QPen(Qt::white));
    painter->setFont(font);
    painter->drawText(QRect(20,200,200,200), QString("LIFE\n%1").arg(m_life));
}
void HardWindow::drawWave(QPainter *painter)
{
    QFont font("Arial",16,QFont::Bold,false);
    painter->setPen(QPen(Qt::white));
    painter->setFont(font);
    painter->drawText(QRect(20,350,200,200), QString("Wave\n%1").arg(6-m_waves));
}

void HardWindow::set_Tower(int num,char type)
{
    switch (type)
    {
    case 'N':
    {
        NormalTower * a_new_tower = new
        NormalTower(m_TowerPositionsList.at(num).centerPos(), this);
        if(m_money<a_new_tower->m_cost)
        {
            delete [] a_new_tower;
            break;
        }
        m_TowerPositionsList[num].setHasTower(true);
        m_TowerPositionsList[num].m_tower=a_new_tower;//at函数返回常引用，不能调用非常成员函数
        m_TowersList.push_back(a_new_tower);
        m_money -= a_new_tower -> m_cost;
        update();                         //对界面进行刷新，否则需要移开才出现一座新的塔，每次加入都需要刷新
        break;
    }
    case 'F':
    {
        FireTower * a_new_tower = new FireTower(m_TowerPositionsList.at(num).centerPos(), this);
        if(m_money<a_new_tower->m_cost)
        {
            delete [] a_new_tower;
            break;
        }
        m_TowerPositionsList[num].setHasTower(true);
        m_TowerPositionsList[num].m_tower=a_new_tower;//at函数返回常引用，不能调用非常成员函数
        m_TowersList.push_back(a_new_tower);
        m_money -= a_new_tower -> m_cost;
        update();                         //对界面进行刷新，否则需要移开才出现一座新的塔，每次加入都需要刷新
        break;
    }
    case 'I':
    {
        IceTower * a_new_tower = new IceTower(m_TowerPositionsList.at(num).centerPos(), this);
        if(m_money<a_new_tower->m_cost)
        {
            delete [] a_new_tower;
            break;
        }
        m_TowerPositionsList[num].setHasTower(true);
        m_TowerPositionsList[num].m_tower=a_new_tower;//at函数返回常引用，不能调用非常成员函数
        m_TowersList.push_back(a_new_tower);
        m_money -= a_new_tower -> m_cost;
        update();                         //对界面进行刷新，否则需要移开才出现一座新的塔，每次加入都需要刷新
        break;
    }
    default:
        break;
    }                     //对界面进行刷新，否则需要移开才出现一座新的塔，每次加入都需要刷新
}
void HardWindow::up_Tower(int num){
    if(m_TowerPositionsList[num].m_tower)
    {
        m_TowerPositionsList[num].m_tower->levelup();

    }
}
void HardWindow::sell_Tower(int num){
    if(m_TowerPositionsList[num].m_tower)
    {
        m_money+=80;
        Tower * removedtower=m_TowerPositionsList[num].m_tower;
        Q_ASSERT(removedtower);
        m_TowersList.removeOne(removedtower);
        delete removedtower;
        m_TowerPositionsList[num].m_tower=NULL;
        m_TowerPositionsList[num].setNoTower();
    }
}

void HardWindow::doGameOver()
{
    if (!m_gameEnded)
    {
       if (m_life <= 0)
        m_gameEnded = true;
        // 此处应该切换场景到结束场景
        // 暂时以打印替代,见paintEvent处理
    }
}

bool HardWindow::loadWave()
{
    if (m_waves >= 9)
        return false;
    WayPoint *startWayPoint = m_WayPointsList.back(); // 这里是个逆序的，尾部才是其实节点
    int enemyStartInterval[] = { 200*(10-m_waves), 400*(10-m_waves), 600*(10-m_waves), 800*(10-m_waves), 1000*(10-m_waves), 1200*(10-m_waves),1400*(10-m_waves),1600*(10-m_waves),1800*(10-m_waves)};
    for (int i = 0; i < 9; ++i)
    {
        Enemy *enemy;
        int j=i%3;
        switch(j){
        case 0:
            enemy = new NormalEnemy(startWayPoint, this);
            break;
        case 1:
            enemy=new DefendEnemy(startWayPoint, this);
            break;
        case 2:
            enemy=new BloodEnemy(startWayPoint, this);
            break;
        }
        m_enemyList.push_back(enemy);
        QTimer::singleShot(enemyStartInterval[i], enemy, SLOT(doActivate()));
    }
    return true;
}

void HardWindow::gameStart()
{
    loadWave();
}

void HardWindow::updateMap()
{
    doGameOver();
    if(m_gameWin||m_gameEnded)
        return;
    else
    {
        foreach(Enemy *enemy, m_enemyList)
        enemy->move();
        foreach(Tower *tower, m_TowersList)
        tower->checkEnemyInRange();
        update();
    }

}
void HardWindow::getHpDamage(int damage)
{
    QMediaPlayer * sound=new QMediaPlayer;
    sound->setMedia(QUrl("C:/Users/12580/Desktop/Code/MyTowerDefense/music/hplose.wav"));
    sound->setVolume(50);
    sound->play();

    m_life-=damage;
}
