#include "mainwindow.h"
#include"gamewindow.h"
#include "ui_mainwindow.h"
#include<QPainter>
#include<QPixmap>
#include<QPaintEvent>
#include<QPushButton>
#include<QMediaPlayer>
#include"mybutton.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    this->setFixedSize(1024,682);
    ui->setupUi(this);
    MyButton *buttone=new MyButton(":/SS/RES/StartScene/B2(1).png");
    buttone->setParent(this);
    buttone->move(350,250);
    MyButton *buttonh=new MyButton(":/SS/RES/StartScene/B2(2).png");
    buttonh->setParent(this);
    buttonh->move(350,400);
    EasyWindow * easyscene = new EasyWindow;
    connect(buttone,&QPushButton::clicked,this,[=](){
        this->hide();
        easyscene->show();

        bgm1=new QMediaPlayer;
        bgm1->setMedia(QUrl("C:/Users/12580/Desktop/Code/MyTowerDefense/music/bgm1.mp3"));
        bgm1->setVolume(80);
        bgm1->play();
    });
    HardWindow * hardscene = new HardWindow;
    connect(buttonh,&QPushButton::clicked,this,[=](){
        this->hide();
        hardscene->show();

        bgm2=new QMediaPlayer;
        bgm2->setMedia(QUrl("C:/Users/12580/Desktop/Code/MyTowerDefense/music/bgm2.mp3"));
        bgm2->setVolume(80);
        bgm2->play();
    });
    //返回，先不要
    connect(easyscene,&EasyWindow::chooseBack,this,[=](){
        easyscene->hide();
        this->show();
        bgm1->stop();
    });

    connect(hardscene,&HardWindow::chooseBack,this,[=](){
        hardscene->hide();
        this->show();
        bgm2->stop();
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::paintEvent(QPaintEvent*){
    QPainter painter(this);
    QPixmap pixmap(":/SS/RES/StartScene/S2.jpg");

    painter.drawPixmap(0,0,this->width(),this->height(),pixmap);
}

