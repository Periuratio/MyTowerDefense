#ifndef HARDWINDOW_H
#define HARDWINDOW_H

#include <QMainWindow>
#include<QPainter>
#include<QPixmap>
#include<QPaintEvent>
#include <QList>
class HardWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit HardWindow(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent*);
private:
signals:

    //void chooseBack();
};

#endif // GAMEWINDOW_H
