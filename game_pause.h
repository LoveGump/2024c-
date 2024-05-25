#ifndef GAME_PAUSE_H
#define GAME_PAUSE_H

#include <QDialog>
#include <QWidget>
#include"my_pushbutton.h"
#define LENGTH_OF_GAMEPAUSE 200
#define WIDTH_OF_GAMEPAUSE 240
#define LENGTH_OF_PUSHBUTTON 150
#define WIDTH_OF_PUSHBUTTON 75
#define X_OF_PUSHBUTTON 20


class Game_Pause : public QDialog
{
public:
    Game_Pause();

    My_PushButton *btn_continue;//继续游戏
    My_PushButton *initGame;//重新开始
    My_PushButton *btn_back;//返回主页


    // 处理键盘按下事件的函数
    void keyPressEvent(QKeyEvent *event);

    // 绘画背景
    void paintEvent(QPaintEvent *);
};

#endif // GAME_PAUSE_H
