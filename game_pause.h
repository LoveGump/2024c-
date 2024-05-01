#ifndef GAME_PAUSE_H
#define GAME_PAUSE_H

#include <QDialog>
#include <QWidget>
#include"mypushbutton.h"

class Game_Pause : public QDialog
{
public:
    Game_Pause();

    MyPushButton *btn_continue;//继续游戏
    MyPushButton *initGame;//重新开始
    MyPushButton *btn_exit;//退出游戏

    // 处理键盘按下事件的函数
    void keyPressEvent(QKeyEvent *event);

    // 处理绘制事件的函数
    void paintEvent(QPaintEvent *);
};

#endif // GAME_PAUSE_H
