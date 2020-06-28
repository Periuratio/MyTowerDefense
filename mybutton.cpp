#include "mybutton.h"
#include <QPixmap>
#include <QPropertyAnimation>
#include <QPushButton>
#include <QPainter>
class QPainter;
MyButton::MyButton(QString pix):QPushButton(0),m_pic(QPixmap(pix)){
    QPixmap pixmap(pix);
    this->setFixedSize(pixmap.width(),pixmap.height());
    this->setStyleSheet("QPushbotton{border:Opx}");
    this->setIcon(pixmap);
    this->setIconSize(QSize(pixmap.width(),pixmap.height()));
    this->setStyleSheet("background-color:transparent");
}
TButton::TButton(QPoint pos,const QPixmap & pic):QPushButton(0),m_pos(pos),m_pic(QPixmap(pic)){
    QPixmap pixmap(pic);
    this->setFixedSize(pixmap.width(),pixmap.height());
    this->setStyleSheet("QPushbotton{border:Opx}");
    this->setIcon(pixmap);
    this->setIconSize(QSize(0,0));
    this->setStyleSheet("background-color:transparent");

    this ->setContextMenuPolicy(Qt::ActionsContextMenu);

    QAction* normaltower = new QAction(this);
    normaltower->setText("NormalTower:100");
    m_ActionsList.push_back(normaltower);
    QAction* firetower = new QAction(this);
    firetower->setText("FireTower:150");
    m_ActionsList.push_back(firetower);
    QAction* icetower = new QAction(this);
    icetower->setText("IceTower:150");
    m_ActionsList.push_back(icetower);
    QAction* sell = new QAction(this);
    sell->setText("Sell: get 80");
    m_ActionsList.push_back(sell);
    QAction* levelup = new QAction(this);
    levelup->setText("LevelUp:50");
    m_ActionsList.push_back(levelup);


    this -> addActions(m_ActionsList);

    connect(normaltower, &QAction::triggered, this, [=]()
    {
        emit setNormalTower();
    });
    connect(firetower, &QAction::triggered, this, [=]()
    {
        emit setFireTower();
    });
    connect(icetower, &QAction::triggered, this, [=]()
    {
        emit setIceTower();
    });
    connect(levelup, &QAction::triggered, this, [=]()
    {
        emit Levelup();
    });
    connect(sell, &QAction::triggered, this, [=]()
    {
        emit sellTower();
    });

}

