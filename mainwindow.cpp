#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QPainter>
#include<QPixmap>
#include<QPaintEvent>
#include<QPushButton>
#include"mybutton.h"
#include"gamewindow.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    this->setFixedSize(1200,800);
    ui->setupUi(this);
    MyButton *button=new MyButton(":/SS/RES/StartScene/B1.png");
    button->setParent(this);
    button->move(437,300);
    GameWindow * gamescene = new GameWindow;
    connect(button,&QPushButton::clicked,this,[=](){
        this->hide();
        gamescene->show();
    });
    //connect(gamescene,&GameWindow::chooseBack,this,[=](){
    //    gamescene->hide();
    //    this->show();
    //});
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::paintEvent(QPaintEvent*){
    QPainter painter(this);
    QPixmap pixmap(":/SS/RES/StartScene/S1.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pixmap);
}

