#ifndef GAME_HELP_H
#define GAME_HELP_H

#include <QMainWindow>
#include <QWidget>
#include<QPainter>

class game_help : public QWidget
{
    Q_OBJECT
public:
    explicit game_help(QWidget *parent = nullptr);
    //绘制背景
    void paintEvent(QPaintEvent *);


signals:
    //回到上一页
    void back();
};

#endif // GAME_HELP_H
