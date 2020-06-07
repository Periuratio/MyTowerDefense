#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>
#include<QPainter>
#include<QPixmap>
#include<QPaintEvent>
#include"tower.h"
#include <QList>
class GameWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit GameWindow(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent*);
    void set_tower();
private:
    QList<Tower*> tower_list;
signals:

    //void chooseBack();
};

#endif // GAMEWINDOW_H
