#ifndef GAME_PAUSE_H
#define GAME_PAUSE_H

#include <QDialog>
#include <QWidget>

class Game_Pause : public QDialog
{
public:
    Game_Pause();

    // 处理键盘按下事件的函数
    void keyPressEvent(QKeyEvent *event);

    // 处理绘制事件的函数
    void paintEvent(QPaintEvent *);
};

#endif // GAME_PAUSE_H
