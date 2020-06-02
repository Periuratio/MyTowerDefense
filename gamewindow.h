#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>
#include<QPainter>
#include<QPixmap>
#include<QPaintEvent>

class GameWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit GameWindow(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent*);
signals:

    //void chooseBack();
};

#endif // GAMEWINDOW_H
