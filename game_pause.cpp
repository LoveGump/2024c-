#include "game_pause.h"
#include<QKeyEvent>
#include<QTimer>
#include<QPainter>

Game_Pause::Game_Pause() {
    // 设置对话框标题为"游戏暂停"
    this->setWindowTitle("游戏暂停");
    // 设置对话框大小为固定大小(200, 240)
    this->setFixedSize(200, 240);
    // 设置对话框模态性为应用程序模态
    this->setWindowModality(Qt::ApplicationModal);
}

// 处理键盘按下事件的函数
void Game_Pause::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Escape: // 如果按下的是Esc键
        return;// 不执行任何操作
    default: // 如果按下的不是Esc键
        QDialog::keyPressEvent(event); // 调用父类的键盘按下事件处理函数
    }
}

// 处理绘制事件的函数
void Game_Pause::paintEvent(QPaintEvent *) {
    QPainter painter(this); // 创建一个用于绘制的painter对象，并将其绑定到当前窗口
    // 在窗口左上角绘制一张名为"dlg.png"的图片，图片大小与窗口大小相同
    painter.drawPixmap(0, 0, this->width(), this->height(), QPixmap(":/photo/dlg.png"));
}
