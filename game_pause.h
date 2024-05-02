#ifndef GAME_PAUSE_H
#define GAME_PAUSE_H

#include <QDialog>
#include <QWidget>
#include"my_pushbutton.h"

class Game_Pause : public QDialog
{
public:
    Game_Pause();

    My_PushButton *btn_continue;//继续游戏
    My_PushButton *initGame;//重新开始
    My_PushButton *btn_exit;//退出游戏

    // 处理键盘按下事件的函数
    void keyPressEvent(QKeyEvent *event);

    // 绘画背景
    void paintEvent(QPaintEvent *);
};

#endif // GAME_PAUSE_H
