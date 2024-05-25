#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QPainter>
#include<QTimer>
#include "ui_mainwindow.h"
#include <QSoundEffect>
#include"my_pushbutton.h"
#include"cinema.h"
#include"game_help.h"

#define WINDOWLENGTH 800
#define WINDOWWIDTH 545
#define WIN_OF_MARIO_x 8700
#define GAMEOVER_LENGTH 600
#define GAMEOVER_WIDTH 400


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    //添加开始游戏按钮
    My_PushButton *start_Btn;
    //添加帮助按钮
    My_PushButton *help_Btn;
    //添加结束按钮
    My_PushButton *end_Btn;
    //开始游戏的界面
    Cinema *gamescene;
    //帮助文档的界面
    game_help *gamehelp;

    QSoundEffect *background_Music;


    ~MainWindow();

private:
    //设置背景的函数
    void paintEvent(QPaintEvent *);

    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
