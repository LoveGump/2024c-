#include "game_pause.h"
#include<QKeyEvent>
#include<QTimer>
#include<QPainter>

Game_Pause::Game_Pause() {
    // 设置标题
    this->setWindowTitle("游戏暂停");
    this->setFixedSize(200, 240);
    this->move(300,130);
    // 设置为模态对话框
    this->setWindowModality(Qt::ApplicationModal);

    //添加继续游戏按钮
    btn_continue = new My_PushButton(":/photo/continueGame.png");
    btn_continue->setParent(this);
    btn_continue->setFixedSize(150, 75);
    btn_continue->setIconSize(QSize(150, 75));//设置图片大小
    btn_continue->move(20, 10);

    //添加重新开始按钮
    initGame = new My_PushButton(":/photo/initGame.png");
    initGame->setParent(this);
    initGame->setFixedSize(150, 75);
    initGame->setIconSize(QSize(150, 75));
    initGame->move(20, 90);

    //添加退出游戏按钮
    btn_exit = new My_PushButton(":/photo/end.png");//添加离开按钮
    btn_exit->setParent(this);
    btn_exit->setFixedSize(150, 75);
    btn_exit->setIconSize(QSize(150, 75));
    btn_exit->move(20, 170);

    connect(btn_continue,&QPushButton::clicked, this, [=]() {
        btn_continue->zoom1();
        btn_continue->zoom2();
    });
    connect(initGame,&QPushButton::clicked, this, [=]() {
        initGame->zoom1();
        initGame->zoom2();
    });
    connect(btn_exit,&QPushButton::clicked, this, [=]() {
        btn_exit->zoom1();
        btn_exit->zoom2();
    });

    // 设置焦点策略为StrongFocus，确保窗口接收键盘事件
    setFocusPolicy(Qt::StrongFocus);

}

// 处理键盘按下事件的函数
//ESC继续游戏 R重新开始 Q退出游戏
void Game_Pause::keyPressEvent(QKeyEvent *event) {
    switch (event->key())
    {
    case Qt::Key_Escape:
        btn_continue->click();
        break;
    case Qt::Key_R:
        initGame->click();
        break;
    case Qt::Key_Q:
        btn_exit->click();
        break;
    default:
        break;
    }
}

// 绘制背景
void Game_Pause::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    //
    //
    painter.drawPixmap(0, 0, this->width(), this->height(), QPixmap(":/photo/dlg.png"));
}
