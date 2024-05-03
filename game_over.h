#ifndef GAME_OVER_H
#define GAME_OVER_H

#include <QWidget>
#include"my_pushbutton.h"

class Game_Over : public QWidget
{
    Q_OBJECT
public:
    explicit Game_Over(QWidget *parent = nullptr);

signals:
};

#endif // GAME_OVER_H
