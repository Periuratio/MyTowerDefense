#ifndef EASYWINDOW_H
#define EASYWINDOW_H
#include <QMainWindow>
#include<QPainter>
#include<QPixmap>
#include<QPaintEvent>
#include <QList>
#include"towerposition.h"
class EasyWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit EasyWindow(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent*);
    void loadTowerPositions();
private:
    QList<TowerPosition> m_TowerPositionsList;
signals:

    //void chooseBack();
};

#endif // GAMEWINDOW_H
