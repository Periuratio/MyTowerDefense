#include "mybutton.h"
#include <QPixmap>
#include <QPropertyAnimation>
#include <QPushButton>
MyButton::MyButton(QString pix):QPushButton(0){
    this->setFixedSize(400,200);
    QPixmap pixmap(pix);
    this->setFixedSize(pixmap.width(),pixmap.height());
    this->setStyleSheet("QPushbotton{border:Opx}");
    this->setIcon(pixmap);
    this->setIconSize(QSize(pixmap.width(),pixmap.height()));
}
