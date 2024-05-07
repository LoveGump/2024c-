#include "game_win_dialog.h"
#include<QKeyEvent>
#include<QTimer>
#include<QPainter>

Game_Win_dialog::Game_Win_dialog() {
    //设置标题游戏胜利
    this->setWindowTitle("游戏胜利");
    this->setFixedSize(600,400);
    this->move(100,100);
    // 设置为模态对话框
    this->setWindowModality(Qt::ApplicationModal);
    //添加下一关按钮
    btn_Back = new My_PushButton(":/photo/back1.png");
    btn_Back->setParent(this);
    btn_Back->setFixedSize(120, 75);
    btn_Back->setIconSize(QSize(120, 75));//设置图片大小
    btn_Back->move(75, 300);

    //添加重新开始按钮
    btn_InitGame = new My_PushButton(":/photo/initGame1.png");
    btn_InitGame->setParent(this);
    btn_InitGame->setFixedSize(120, 75);
    btn_InitGame->setIconSize(QSize(120, 75));
    btn_InitGame->move(225, 300);

    //添加退出游戏按钮
    btn_Exit = new My_PushButton(":/photo/Exit.png");//添加离开按钮
    btn_Exit->setParent(this);
    btn_Exit->setFixedSize(120, 75);
    btn_Exit->setIconSize(QSize(120, 75));
    btn_Exit->move(375, 300);

    connect(btn_Back,&QPushButton::clicked, this, [=]() {
        btn_Back->zoom1();
        btn_Back->zoom2();
    });
    connect(btn_InitGame,&QPushButton::clicked, this, [=]() {
        btn_InitGame->zoom1();
        btn_InitGame->zoom2();
    });
    connect(btn_Exit,&QPushButton::clicked, this, [=]() {
        btn_Exit->zoom1();
        btn_Exit->zoom2();
    });

    // 设置焦点策略为StrongFocus，确保窗口接收键盘事件
    setFocusPolicy(Qt::StrongFocus);

}

// 绘制背景
void Game_Win_dialog::paintEvent(QPaintEvent *) {
    QPainter painter(this);

    painter.drawPixmap(0, 0, this->width(), this->height(), QPixmap(":/photo/Game_Win.png"));
}

