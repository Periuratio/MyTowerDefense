#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H
#include<QObject>
#include<QDebug>
#include <QMainWindow>
#include <QWidget>
#include <QPainter>
#include <QPixmap>
#include <QPaintEvent>
#include <QList>
#include <QPushButton>
#include <QTimer>
#include <QtGlobal>
#include <QMessageBox>
#include <QXmlStreamReader>
#include"towerposition.h"
#include"tower.h"
#include"waypoint.h"
#include"enemy.h"
#include "mybutton.h"
#include"bullet.h"
class TowerPosition;
class TButton;
class Tower;
class WayPoint;
class Bullet;
class AudioPlayer;

class GameWindow : public QMainWindow
{
    Q_OBJECT
public:
    GameWindow(QWidget *parent = nullptr);
    ~GameWindow();
    virtual void paintEvent(QPaintEvent*);
    virtual void loadTowerPositions();
    virtual void addWayPoints();
    virtual void set_Tower(int num,char type)=0;

    virtual void removedEnemy(Enemy *enemy);
    virtual bool loadWave();
    virtual void getHpDamage(int damage=1);
    void removedBullet(Bullet *bullet);
    void addBullet(Bullet *bullet);
    QList<Enemy *> enemyList() const;
    QList<Tower*> m_TowersList;
    QList<Enemy *>m_enemyList;
    int m_money;
    int m_life;
    int m_waves;
public slots:
    virtual void updateMap()=0;
    virtual void gameStart()=0;

protected:
    bool m_gameWin=false;
    bool m_gameEnded=false;
    QList<TowerPosition> m_TowerPositionsList;
    QList<WayPoint *> m_WayPointsList;
    QList<Bullet *>m_BulletList;
signals:

};
class EasyWindow : public GameWindow
{
    Q_OBJECT
public:
    EasyWindow(QWidget *parent = nullptr);
    ~EasyWindow();
    virtual void paintEvent(QPaintEvent*);
    virtual void loadTowerPositions();
    void addWayPoints();
    void set_Tower(int num,char type);
    void up_Tower(int num);
    void sell_Tower(int num);
    virtual bool loadWave();
    virtual void getHpDamage(int damage=1);
    void doGameOver();
    void drawMoney(QPainter *painter);
    void drawLife(QPainter *painter);
    void drawWave(QPainter *painter);
    int m_money;
    int m_life;
    int m_waves;
public slots:
    void updateMap();
    void gameStart();

protected:

signals:

    void chooseBack();
};
class HardWindow : public GameWindow
{
    Q_OBJECT

public:
    HardWindow(QWidget *parent = nullptr);
    ~HardWindow();
    virtual void paintEvent(QPaintEvent*);
    virtual void loadTowerPositions();
    void addWayPoints();
    void set_Tower(int num,char type);
    void up_Tower(int num);
    void sell_Tower(int num);
    virtual bool loadWave();
    virtual void getHpDamage(int damage=1);
    void doGameOver();
    void drawMoney(QPainter *painter);
    void drawLife(QPainter *painter);
    void drawWave(QPainter *painter);
    int m_money;
    int m_life;
    int m_waves;
public slots:
    void updateMap();
    void gameStart();

protected:


signals:

    void chooseBack();
};

#endif // GAMEWINDOW_H
