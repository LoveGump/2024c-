#include "game_pause.h"
#include<QKeyEvent>
#include<QTimer>
#include<QPainter>

Game_Pause::Game_Pause() {

    this->setFixedSize(LENGTH_OF_GAMEPAUSE, WIDTH_OF_GAMEPAUSE);
    this->move(300,130);
    // 设置为模态对话框
    this->setWindowModality(Qt::ApplicationModal);

    //添加继续游戏按钮
    btn_continue = new My_PushButton(":/photo/continueGame1.png");
    btn_continue->setParent(this);
    btn_continue->setFixedSize(LENGTH_OF_PUSHBUTTON, WIDTH_OF_PUSHBUTTON);
    btn_continue->setIconSize(QSize(LENGTH_OF_PUSHBUTTON, WIDTH_OF_PUSHBUTTON));//设置图片大小
    btn_continue->move(X_OF_PUSHBUTTON, 10);

    //添加重新开始按钮
    initGame = new My_PushButton(":/photo/initGame1.png");
    initGame->setParent(this);
    initGame->setFixedSize(LENGTH_OF_PUSHBUTTON, WIDTH_OF_PUSHBUTTON);
    initGame->setIconSize(QSize(LENGTH_OF_PUSHBUTTON, WIDTH_OF_PUSHBUTTON));
    initGame->move(X_OF_PUSHBUTTON, 90);

    //添加返回主页按钮
    btn_back = new My_PushButton(":/photo/back1.png");
    btn_back->setParent(this);
    btn_back->setFixedSize(LENGTH_OF_PUSHBUTTON, WIDTH_OF_PUSHBUTTON);
    btn_back->setIconSize(QSize(LENGTH_OF_PUSHBUTTON, WIDTH_OF_PUSHBUTTON));
    btn_back->move(X_OF_PUSHBUTTON, 170);

    connect(btn_continue,&QPushButton::clicked, this, [=]() {
        btn_continue->zoom1();
        btn_continue->zoom2();
    });
    connect(initGame,&QPushButton::clicked, this, [=]() {
        initGame->zoom1();
        initGame->zoom2();
    });
    connect(btn_back,&QPushButton::clicked, this, [=]() {
        this->close();
        btn_back->zoom1();
        btn_back->zoom2();
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
        btn_back->click();
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
