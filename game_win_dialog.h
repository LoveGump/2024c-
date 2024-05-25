#ifndef GAME_WIN_DIALOG_H
#define GAME_WIN_DIALOG_H

#include <QDialog>
#include"my_pushbutton.h"
#include<QWidget>
#define LENGTH_OF_GAMEWIN 600
#define WIDTH_OF_GAMEWIN 400
#define LENGTH_OF_PUSHBUTTON 120
#define WIDTH_OF_PUSHBUTTON 75
#define X_IN_WINDOW 100
#define Y_IN_WINDOW 100
#define Y_OF_PUSHBUTTON 300

class Game_Win_dialog : public QDialog
{
public:
    Game_Win_dialog();

    My_PushButton *btn_Back;//回到主页
    My_PushButton *btn_InitGame;//重新开始
    My_PushButton *btn_Exit;//退出游戏

    // 绘画背景
    void paintEvent(QPaintEvent *);
};

#endif // GAME_WIN_DIALOG_H
