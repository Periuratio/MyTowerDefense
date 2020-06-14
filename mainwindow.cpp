#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QPainter>
#include<QPixmap>
#include<QPaintEvent>
#include<QPushButton>
#include"mybutton.h"
#include"easywindow.h"
#include"hardwindow.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    this->setFixedSize(1024,682);
    ui->setupUi(this);
    MyButton *buttone=new MyButton(":/SS/RES/StartScene/B2(1).png");
    buttone->setStyleSheet("background-color:transparent");
    buttone->setParent(this);
    buttone->move(350,250);
    MyButton *buttonh=new MyButton(":/SS/RES/StartScene/B2(2).png");
    buttonh->setStyleSheet("background-color:transparent");
    buttonh->setParent(this);
    buttonh->move(350,400);
    EasyWindow * easyscene = new EasyWindow;
    connect(buttone,&QPushButton::clicked,this,[=](){
        this->hide();
        easyscene->show();
    });
    HardWindow * hardscene = new HardWindow;
    connect(buttonh,&QPushButton::clicked,this,[=](){
        this->hide();
        hardscene->show();
    });
    //返回，先不要
    //connect(easyscene,&EasyWindow::chooseBack,this,[=](){
    //    easyscene->hide();
    //    this->show();
    //});
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

