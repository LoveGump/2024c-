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
    //进入游戏过程中的音乐
    QSoundEffect *stage_clear_Music;

    ~MainWindow();

private:
    //设置背景的函数
    void paintEvent(QPaintEvent *);

    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
