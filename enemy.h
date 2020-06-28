#ifndef ENEMY_H
#define ENEMY_H

#include <QObject>

class Enemy : public QObject
{
    Q_OBJECT
public:
    explicit Enemy(QObject *parent = nullptr);

signals:

};

#endif // ENEMY_H
