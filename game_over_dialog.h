#ifndef GAME_OVER_DIALOG_H
#define GAME_OVER_DIALOG_H

#include <QWidget>
#include"my_pushbutton.h"

class Game_Over : public QWidget
{
    Q_OBJECT
public:
    explicit Game_Over(QWidget *parent = nullptr);
    My_PushButton *btn_Back;//回到主页
    My_PushButton *btn_InitGame;//重新开始
    My_PushButton *btn_Exit;//退出游戏
    void paintEvent(QPaintEvent *event) override;
signals:
};

#endif // GAME_OVER_DIALOG_H
