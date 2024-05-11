#ifndef CINEMA_H
#define CINEMA_H


#include <QWidget>
#include<QPainter>
#include<QDebug>
#include<QString>
#include<QTimer>
#include<QKeyEvent>
#include<QDialog>
#include<QMap>
#include "game_pause.h"
#include"mario.h"
#include"brick.h"
#include"pipe.h"
#include"master.h"
#include"unkown_surprise.h"
#include"mushroom.h"
#include"castle.h"
#include <QSoundEffect>
#include "game_win_dialog.h"
#include"flag.h"
#include"game_over_dialog.h"
//#include"mainwindow.h"


class Cinema : public QWidget
{
    Q_OBJECT
public:

    explicit Cinema(QWidget *parent = nullptr);



    int timer1; // 计时器1

    int timer2; // 计时器2

    int timer3; // 计时器3

    bool is_kill_timer2; // 计时器2是否关闭
    bool game_start = false; // 游戏是否开始


    float time; // 游戏时间
    int score; // 得分
    bool is_press_x; // 是否按下X键
    bool is_win; // 是否胜利
    bool is_win_dialog_show ;

    QString key; // 按键状态
    Game_Pause *Pause; // 游戏暂停对象
    Game_Win_dialog *win;
    Game_Over_Dialog *game_over;
   // QMainWindow *mainWindow;


    Mario *mario;    //创建角色对象
    Brick *brick; // 砖块对象
    Pipe *pipe;
    Unknown_Surprise *unknown;
    MushRoom *mushroom;
    Master *master;
    Castle *castle;
    Flag *f;
    // Fire *fire;
    //普通背景音乐
    QSoundEffect *main_theme_Music;
    //死亡音乐
    QSoundEffect *death_Music;
    //游戏结束 生命用 光的音乐
    QSoundEffect *Out_of_Life_Music;
    //变颜色之后的音乐
    QSoundEffect *invincible_Music;
    //加速之后的音乐
    QSoundEffect *main_theme_sped_up_Music;
    //超时的音乐
    QSoundEffect *Out_of_Time_Music;

    //砖块破碎
    QSoundEffect *brick_Break_Music;
    //游戏胜利
    QSoundEffect *Game_Win_Music;
    //获得金币
    QSoundEffect *Coin_Music;
    //出现蘑菇
    QSoundEffect *Mushroom_Music;
    //跳跃
    QSoundEffect *Jump_Music;






    void paintEvent(QPaintEvent *); // 绘图事件
    void keyPressEvent(QKeyEvent *event); // 键盘按下事件
    void keyReleaseEvent(QKeyEvent *event); // 键盘抬起事件
    void timerEvent(QTimerEvent *event); // 定时器事件
    void Game_Init(); // 初始化游戏
      void Die_Init(); // 初始化死亡状态
    void Pause_Init(); // 初始化暂停状态
    void Pause_Game_Init(); // 初始化游戏暂停状态


     void Fall_Down(int &y); // 角色掉落处理
     void Jump_Collision(); // 跳跃碰撞检测
     void Move_Collision(); // 移动碰撞检测
    void Game_Win(); // 游戏胜利处理
    void Game_Over();//游戏失败处理
    void Music_Init();
signals:
    void back();
};

#endif // CINEMA_H
