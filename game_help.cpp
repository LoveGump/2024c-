#include "game_help.h"
#include"my_pushbutton.h"
#include<QTimer>

game_help::game_help(QWidget *parent)
    : QWidget{parent}
{
    this->setWindowTitle("游戏帮助");
    this->setFixedSize(800,500);
    //设置帮助按钮
    My_PushButton *back_Btn = new My_PushButton(":/photo/back.png");
    //设置父类
    back_Btn->setParent(this);
    back_Btn->move(500,this->height()*0.8);
    //链接按钮
    connect(back_Btn, &QPushButton::clicked, [=]() {
        back_Btn->zoom1();
        back_Btn->zoom2();
        QTimer::singleShot(400, this, [=]() {
            this->close();
            emit
                this->back();
        });
    });

}
void game_help::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    painter.drawPixmap(0, 0, 800, 550, QPixmap(":/photo/gamehelp.png"));
}
