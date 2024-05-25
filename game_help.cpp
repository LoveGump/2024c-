#include "game_help.h"
#include"my_pushbutton.h"
#include<QTimer>

game_help::game_help(QWidget *parent)
    : QWidget{parent}
{
    this->setWindowTitle("Game_Help");
    this->setFixedSize(LENGTH_OF_HELP,WIDTH_OF_HELP);
    //设置帮助按钮
    My_PushButton *back_Btn = new My_PushButton(":/photo/back.png");
    back_Btn->setParent(this);//设置父类
    back_Btn->move(500,this->height() * 0.8);
    //链接按钮
    connect(back_Btn, &QPushButton::clicked, [=]() {
        back_Btn->zoom1();
        back_Btn->zoom2();
        QTimer::singleShot(500, this, [=]() {
            this->close();
            //
            //
            emit
                this->back();
        });
    });

}
void game_help::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    //绘制背景
    painter.drawPixmap(0, 0, LENGTH_OF_HELP, WIDTH_OF_HELP, QPixmap(":/photo/help.png"));
}
