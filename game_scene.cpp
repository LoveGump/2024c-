#include "game_scene.h"
#include "mario.h"
#include "my_pushbutton.h"
#include "qtimer.h"
#include "game_pause.h"

Game_Scene::Game_Scene(QWidget *parent)
    : QWidget{parent}
{
    //设置标题
    setWindowTitle("超级马里奥");
    setFixedSize(800, 545);

    Game_Init();
    Pause_Init();

    //显示1.5秒界面之后，开始游戏
    QTimer::singleShot(1500, this, [=]() {
        timer1 = startTimer(15);
        timer3 = startTimer(40);
        game_start = true;
    });
}

//初始化游戏
void Game_Scene::Game_Init()// 初始化游戏
{
    mario = new Mario;
    brick = new Brick;
    pipe = new Pipe;
    unknown = new Unknown_Surprise;
    mushroom = new MushRoom;
    master = new Master;
    castle = new Castle;

    //fire = new Fire;
    //fire->Fire_Move(mary, pipe, brick, master);

    key = "null";
    is_press_x = false;
    is_win = false;
    score = 0;
    time = 300.0;

    is_kill_timer2 = true;
    game_start = false;

    master->Master_State(mario, pipe, brick);
}

// 初始化暂停状态
void Game_Scene::Pause_Init()
{
    Pause = new Game_Pause();//初始化暂停窗口

    //链接继续游戏
    connect(Pause->btn_continue, &QPushButton::clicked, this, [=]() {

        QTimer::singleShot(500, this, [=]() {
            timer1 = startTimer(15);
            timer3 = startTimer(40);
            mario->walk_state = 0;//初始化mario的行走状态
            key = "null";
            Pause->close();
        });
    });
    //链接重新游戏
    connect(Pause->initGame, &QPushButton::clicked, this, [=]() {

        QTimer::singleShot(500, this, [=]() {
            Pause_Game_Init();//游戏初始化
            Pause->close();
            QTimer::singleShot(1500, this, [=]() {
                timer1 = startTimer(15);//开启定时器
                timer3 = startTimer(40);
                game_start = true;
            });
        });
    });

    //链接退出游戏
    connect(Pause->btn_exit, &QPushButton::clicked, this, [=]() {

        QTimer::singleShot(500, this, [=]() {
            this->close();
        });
    });

}

//绘制地图
void Game_Scene::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    if (!game_start) { // 如果游戏尚未开始
        // 绘制游戏未开始时的界面
        painter.drawPixmap(0, 0, 800, 550, QPixmap(":/photo/blackground2.png")); // 黑背景
        painter.drawPixmap(300, 250, 40, 40, QPixmap(":/photo/life.png")); // 绘制生命图标
        painter.setPen(QColor(255, 255, 255)); // 设置画笔颜色
        QFont font; // 创建字体对象
        font.setPointSize(35); // 设置字体大小
        painter.setFont(font); // 设置字体
        painter.drawText(360, 280, "x"); // 绘制生命图标右侧的"x"
        painter.drawText(80, 40, "times:"); // 绘制计时文本
        painter.drawText(220, 40, QString::number(time, 'f', 1)); // 绘制倒计时
        painter.drawText(600, 40, "coin:"); // 绘制金币文本
        painter.drawText(720, 40, QString::number(unknown->coin)); // 绘制金币数量
        font.setPointSize(45); // 设置字体大小
        painter.setFont(font); // 设置字体
        painter.drawText(400, 287, QString::number(mario->life)); // 绘制生命值
        qDebug()<<mario->life;
        return;
    }

    painter.drawPixmap(0, 0, 800, 550, QPixmap(":/photo/sky1.jpg"));//画背景
    painter.drawPixmap(230, 10, QPixmap(":/photo/coin.png"), 0, 0, 30, 30);
    painter.drawPixmap(380, 10, 40, 40, QPixmap(":/photo/score.png"));
    painter.setFont(QFont("Times", 45, QFont::Bold));
    painter.drawText(280, 50, QString::number(unknown->coin));
    painter.drawText(430, 50, QString::number(score));
    //绘制生命值
    for (int i = 1; i <= mario->life; i++) {
        painter.drawPixmap(800 - i * 45, 10, 40, 40, QPixmap(":/photo/life.png"));
    }
    //绘制倒计时图标
    painter.drawPixmap(10, 10, 40, 40, QPixmap(":/photo/time.png"));
    //绘制倒计时'f'表示浮点数
    painter.drawText(50, 50, QString::number(time, 'f', 1));
    //绘制草坪地板
    painter.drawPixmap(0, 500, QPixmap(":/photo/ground.png"), mario->ground_state, 0, 800, 45);//画地板
    //如果马里奥的横坐标已经超过过7800 就可以画出城堡
    if (mario->x > 7800) {
        QVector < QVector < int >> ::iterator it = castle->m.begin()->begin();
        //城堡相对于马里奥的坐标为它的初始值8700 减去马里奥现在的横坐标 ，纵坐标为其本身的纵坐标
        painter.drawPixmap(*it->begin() - mario->x, *(it->begin() + 1), 200, 200, QPixmap(":/photo/castle.png"));
    }
    //蘑菇
    if (mushroom->mushroom_state != 0) {
        painter.drawPixmap(mushroom->mushroom_x - mario->x, mushroom->mushroom_y, 40, 40,
                           QPixmap(":/photo/mushroom" + QString::number(mario->colour) + ".png"));
    }

    //绘制砖块 宽50 高40
    for (QVector < QVector < int >> ::iterator it = brick->m.begin()->begin(); it != brick->m.begin()->end(); it++)
    {
        //在玛丽后的50像素的和在玛丽前的800像素（绘制超过宽度的像素）的并且没有碎掉的砖块
        if (*it->begin() - mario->x >= -50 && *it->begin() - mario->x <=800 && *(it->begin() + 2) == 1) {
            painter.drawPixmap(*it->begin() - mario->x, *(it->begin() + 1), 50, 40, QPixmap(":/photo/brick1.png"));
        }
    }

    //绘制神秘方块
    for (QVector < QVector < int >> ::iterator it = unknown->m.begin()->begin(); it != unknown->m.begin()->end();it++)
    {
        //没有顶过的
        //
        //
        if (*it->begin() - mario->x >= -50 && *it->begin() - mario->x <= 800 && *(it->begin() + 2) != 0) {
            painter.drawPixmap(*it->begin() - mario->x, *(it->begin() + 1), QPixmap(":/photo/unknown.png"),
                               unknown->unknown_state, 0, 50, 40);
        }

        //被顶过的
        else if (*it->begin() - mario->x >= -50 && *it->begin() - mario->x <= 800 && *(it->begin() + 2) == 0)
        {
            painter.drawPixmap(*it->begin() - mario->x, *(it->begin() + 1), 50, 40,
                               QPixmap(":/photo/unknown_after.png"));
        }
    }
    //
    //
    if (unknown->coin_state > 0) {
        painter.drawPixmap(unknown->coin_x - mario->x, unknown->coin_y, QPixmap(":/photo/coin.png"), unknown->coin_state,
                           0, 30, 33);
    }



}





void Game_Scene::timerEvent(QTimerEvent *event) // 定时器事件

{
    if (event->timerId() == timer1 && mario->is_die) {
        mario->Mario_die();
      //  Die_Init();
        update();
        return;
    }
    if (event->timerId() == timer1) {
        //mario->Mario_Move(key);
        //mario->Jump_And_Down();
        //  Jump_Collision();
        // Move_Collision();
        //  brick->ShatterState();
        //  mushroom->Move_state();
        //   master->Master_Move();
        // Die_Init();
        //Fall_Down(mario->y);
        //fire->Fire_state();


        update();//刷新屏幕
    }

    if (event->timerId() == timer2) {
        mario->Mario_Move(key);
    }

    if (event->timerId() == timer3) {
        time -= 0.04;
        //unknown->Unknown_State();
       // unknown->Crash_state();
    }
}
void Game_Scene::Pause_Game_Init()
{

}
