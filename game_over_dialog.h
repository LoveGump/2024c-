#ifndef GAME_OVER_DIALOG_H
#define GAME_OVER_DIALOG_H

#include <QWidget>
#include"my_pushbutton.h"
#include<QDialog>
#define LENGTH_OF_GAMEOVER 600
#define WIDTH_OF_GAMEOVER 400
#define LENGTH_OF_PUSHBUTTON 120
#define WIDTH_OF_PUSHBUTTON 75
#define X_IN_WINDOW 100
#define Y_IN_WINDOW 100
#define Y_OF_PUSHBUTTON 300



class Game_Over_Dialog: public QDialog
{

public:
    Game_Over_Dialog();

    My_PushButton *btn_Back;//回到主页
    My_PushButton *btn_InitGame;//重新开始
    My_PushButton *btn_Exit;//退出游戏


    void paintEvent(QPaintEvent *event);
signals:
};

#endif // GAME_OVER_DIALOG_H
