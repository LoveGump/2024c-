#include "cinema.h"
#include "my_pushbutton.h"
#include "qtimer.h"
#include<QDebug>
#include <QFontDatabase>

#include"mainwindow.h"
#include"game_win.h"

Cinema::Cinema(QWidget *parent)
    : QWidget{parent}
{
    //设置标题
    setWindowTitle("超级马里奥");
    setFixedSize(800, 545);

    Music_Init();
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
void Cinema::Game_Init()// 初始化游戏
{
    is_background_painted=false;
    is_win_dialog_show = false;
    mario = new Mario;
    brick = new Brick;
    pipe = new Pipe;
    unknown = new Unknown_Surprise;
    mushroom = new MushRoom;
    master = new Master;
    castle = new Castle;

    QTimer::singleShot(1500, this, [=]() {
        main_theme_Music->play();
    });


    //fire = new Fire;
    //fire->Fire_Move(mary, pipe, brick, master);

    key = "null";
    is_press_x = false;
    is_win = false;
    score = 0;
    time = 200.0;

    is_kill_timer2 = true;
    game_start = false;
    master->Master_State(mario, pipe, brick);
}

// 初始化暂停状态
void Cinema::Pause_Init()
{
    Pause = new Game_Pause();//初始化暂停窗口

    //链接继续游戏
    connect(Pause->btn_continue, &QPushButton::clicked, this, [=](){

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


            this->hide();
        });
    });

}

//初始化音乐
void Cinema::Music_Init()
{
    //普通背景音乐
    main_theme_Music = new QSoundEffect;
    main_theme_Music->setSource (QUrl::fromLocalFile(":/music/main_theme.wav"));
    main_theme_Music->setLoopCount(QSoundEffect::Infinite);//无限循环
    main_theme_Music->setVolume(0.5f);

    //死亡音乐
    death_Music = new QSoundEffect;
    death_Music->setSource(QUrl::fromLocalFile(":/music/death.wav"));
    death_Music->setVolume(0.5f);
    //游戏结束 生命用光的音乐
    Out_of_Time_Music = new QSoundEffect;
    Out_of_Time_Music->setSource(QUrl::fromLocalFile(":/music/game_over.wav"));
    Out_of_Time_Music->setVolume(0.5f);
    //变颜色之后的音乐
    invincible_Music = new QSoundEffect;
    invincible_Music->setSource(QUrl::fromLocalFile(":/music/invincible.mp3"));
    invincible_Music->setLoopCount(QSoundEffect::Infinite);//无限循环
    invincible_Music->setVolume(0.5f);
    //加速之后的音乐
    main_theme_sped_up_Music = new QSoundEffect;
    main_theme_sped_up_Music->setSource(QUrl::fromLocalFile(":/music/main_theme_sped_up.wav"));
    main_theme_sped_up_Music->setLoopCount(QSoundEffect::Infinite);//无限循环
    main_theme_sped_up_Music->setVolume(0.5f);
    //超时的音乐
    Out_of_Time_Music = new QSoundEffect;
    Out_of_Time_Music->setSource(QUrl::fromLocalFile(":/music/out_of_time.wav"));
    Out_of_Time_Music->setVolume(0.5f);


    //砖块破碎
    brick_Break_Music = new QSoundEffect;
    brick_Break_Music->setSource(QUrl::fromLocalFile(":/music/break.wav"));
    brick_Break_Music->setVolume(0.5f);
    //游戏胜利
    Game_Win_Music = new QSoundEffect;
    Game_Win_Music->setSource(QUrl::fromLocalFile(":/music/win.wav"));
    Game_Win_Music->setVolume(0.5f);

    //获得金币
    Coin_Music = new QSoundEffect;
    Coin_Music->setSource(QUrl::fromLocalFile(":/music/coin.wav"));
    Coin_Music->setVolume(0.5f);
    //出现蘑菇
    Mushroom_Music = new QSoundEffect;
    Mushroom_Music->setSource(QUrl::fromLocalFile(":/music/mushroom.wav"));
    Mushroom_Music->setVolume(0.5f);




}

//按键函数 按下按键 执行相应的函数
void Cinema::keyPressEvent(QKeyEvent *event)
{
    if (!mario->is_die && (9100 - mario->x) >=300)
    {
        switch (event->key())
        {
        case Qt::Key_Right:
        case Qt::Key_D:
            mario->direction = "right";
            key = "right";
            break;
        case Qt::Key_Left:
        case Qt::Key_A:
            mario->direction ="left";
            key = "left";
            break;
            //开始计时器2 用来加速
        case Qt::Key_Z:
            main_theme_Music->stop();
            main_theme_sped_up_Music->play();
            timer2 = startTimer(25);
            is_kill_timer2 = false;
            break;
        case Qt::Key_Space:
        case Qt::Key_W:
        case Qt::Key_Up:
            mario->is_jump = true;
            break;
        case Qt::Key_X:
            if (!is_press_x && !mario->is_jump && mario->is_jump_end && mario->colour == 3)
            {
                is_press_x = true;
                //  fire->Fire_xy();
            }
            break;
        }
    }

}

//按键函数 释放按键 执行相应的函数
void Cinema::keyReleaseEvent(QKeyEvent *event)
{
    if (!mario->is_die||(9100 - mario->x) >=300)
    {
        switch (event->key())
        {
        case Qt::Key_Right:
        case Qt::Key_D:
            mario->walk_state = 0;
            key = "null";
            break;

        case Qt::Key_Left:
        case Qt::Key_A:
            mario->walk_state = 0;
            key = "null";
            break;
            //关闭计时器2
        case Qt::Key_Z:
            main_theme_sped_up_Music->stop();
            main_theme_Music->play();
            is_kill_timer2 = true;
            killTimer(timer2);
            break;


        case Qt::Key_Space:
        case Qt::Key_W:
        case Qt::Key_Up:

            mario->is_jump = false;
            mario->is_space_release = true;
            break;

        case Qt::Key_X:
            is_press_x = false;
            break;
        case Qt::Key_Escape:
            if (game_start)
            {

                //关闭计时器1
                killTimer(timer1);
                if (is_kill_timer2)
                {
                    //关闭计时器2
                    killTimer(timer2);
                }
                main_theme_Music->stop();
                //关闭计时器3
                killTimer(timer3);
                // Game_Pause *Pause = new Game_Pause();
                Pause->setParent(this);
                Pause->exec();
                delete Pause;
                main_theme_Music->play();
                Pause_Init();
            }
            break;
        case Qt::Key_C:
            if (mario->life < 8)
            {
                mario->life++;
            }
            break;

        }
    }
}


//绘制地图
void Cinema::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    if (!game_start)  // 如果游戏尚未开始
    {
        // 加载自定义字体文件
        int  fontId = QFontDatabase::addApplicationFont(":/fonts/Fixedsys500c.ttf");

        // 获取字体名称
        QString fontName = QFontDatabase::applicationFontFamilies(fontId).at(0);
        // 绘制游戏未开始时的界面
        painter.drawPixmap(0, 0, 800, 550, QPixmap(":/photo/blackground2.png")); // 背景
        painter.drawPixmap(340, 90, 40, 40, QPixmap(":/photo/life.png")); // 绘制生命图标
        painter.setPen(QColor(0, 0, 0)); // 设置画笔颜色
        QFont font(fontName); // 创建字体对象

        font.setPointSize(35); // 设置字体大小
        painter.setFont(font); // 设置字体
        painter.drawText(400, 120, "x"); // 绘制生命图标右侧的"x"
        painter.drawText(80, 40, "times:"); // 绘制计时文本
        painter.drawText(240, 40, QString::number(time, 'f', 1)); // 绘制倒计时
        painter.drawText(600, 40, "coin:"); // 绘制金币文本

        painter.drawText(720, 40, QString::number(unknown->coin)); // 绘制金币数量

        font.setPointSize(45); // 设置字体大小
        painter.setFont(font); // 设置字体
        painter.drawText(440, 125, QString::number(mario->life)); // 绘制生命值


        return;

    }
    // 加载自定义字体文件
    int  fontId = QFontDatabase::addApplicationFont(":/fonts/Fixedsys500c.ttf");

    // 获取字体名称
    QString fontName = QFontDatabase::applicationFontFamilies(fontId).at(0);
    QFont font(fontName); // 创建字体对象
    font.setPointSize(40); // 设置字体大小

    painter.drawPixmap(0, 0, 800, 550, QPixmap(":/photo/sky1.png"));//画背景


    //画得分
    QPixmap pixmap(":/photo/score.png");
    QPixmap scaledPixmap = pixmap.scaled(40, 40); // 缩放为30x30大小
    painter.drawPixmap(QPointF(230, 10), scaledPixmap);

    // painter.drawPixmap(280, 80, QPixmap(":/photo/score.png"), 0, 0, 100, 100);//金币图标
    painter.drawPixmap(380, 10, 40, 40, QPixmap(":/photo/gold_cion.png"));
    painter.setFont(font);

    painter.drawText(280, 50, QString::number(score));
    painter.drawText(430, 50, QString::number(unknown->coin));
    //绘制生命值
    for (int i = 1; i <= mario->life; i++)
    {
        painter.drawPixmap(800 - i * 45, 10, 40, 40, QPixmap(":/photo/life.png"));
    }
    //绘制倒计时图标
    painter.drawPixmap(10, 10, 40, 40, QPixmap(":/photo/time.png"));
    //绘制倒计时'f'表示浮点数
    painter.drawText(50, 50, QString::number(time, 'f', 1));
    //绘制草坪地板
    painter.drawPixmap(0, 500, QPixmap(":/photo/ground.png"), mario->ground_state, 0, 800, 45);//画地板
    //如果马里奥的横坐标已经超过过7800 就可以画出城堡
    if (mario->x > 7800)
    {
        QVector < QVector < int >> ::iterator it = castle->m.begin()->begin();

        QPixmap pixmap(":/photo/castle1.png");
        QPixmap scaledPixmap = pixmap.scaled(260, 260);
        painter.drawPixmap(QPointF(*it->begin() - mario->x, *(it->begin() + 1)), scaledPixmap);


        // //城堡相对于马里奥的坐标为它的初始值8700 减去马里奥现在的横坐标 ，纵坐标为其本身的纵坐标
        // painter.drawPixmap(*it->begin() - mario->x, *(it->begin() + 1), 200, 200, QPixmap(":/photo/castle1.png"));
    }
    //蘑菇
    if (mushroom->mushroom_state != 0)
    {
        painter.drawPixmap(mushroom->mushroom_x - mario->x, mushroom->mushroom_y, 40, 40,
                           QPixmap(":/photo/mushroom" + QString::number(mario->colour) + ".png"));
    }

    //绘制砖块 宽50 高40
    for (QVector < QVector < int >> ::iterator it = brick->m.begin()->begin(); it != brick->m.begin()->end(); it++)
    {
        //在玛丽后的50像素的和在玛丽前的800像素（绘制超过宽度的像素）的并且没有碎掉的砖块
        if (*it->begin() - mario->x >= -50 && *it->begin() - mario->x <=800 && *(it->begin() + 2) == 1)
        {
            painter.drawPixmap(*it->begin() - mario->x, *(it->begin() + 1), 50, 40, QPixmap(":/photo/brick1.png"));
        }
    }

    //绘制神秘方块
    for (QVector < QVector < int >> ::iterator it = unknown->m.begin()->begin(); it != unknown->m.begin()->end();it++)
    {
        //没有顶过的
        //
        //
        if (*it->begin() - mario->x >= -50 && *it->begin() - mario->x <= 800 && *(it->begin() + 2) != 0)
        {
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
    if (unknown->coin_state > 0)
    {
        painter.drawPixmap(unknown->coin_x - mario->x, unknown->coin_y, QPixmap(":/photo/coin.png"), unknown->coin_state,
                           0, 30, 33);
    }
    //绘制管道  长管道 宽80 高100
    for (QVector < QVector < int >> ::iterator it = pipe->long_m.begin()->begin(); it != pipe->long_m.begin()->end();it++)
    {
        if (*it->begin() - mario->x >= -80 && *it->begin() - mario->x < 800)
        {
            painter.drawPixmap(*it->begin() - mario->x, *(it->begin() + 1), 80, 100, QPixmap(":/photo/pipe_long.png"));
        }
    }
    //短管道 80*50
    for (QVector < QVector < int >> ::iterator it = pipe->short_m.begin()->begin(); it != pipe->short_m.begin()->end();it++)
    {
        if (*it->begin() - mario->x > -80 && *it->begin() - mario->x < 800)
        {
            painter.drawPixmap(*it->begin() - mario->x, *(it->begin() + 1), 80, 50, QPixmap(":/photo/pipe_short.png"));
        }
    }

    //绘制砖块碎掉的动画
    if (brick->shatter_state > 0)
    {
        painter.drawPixmap(brick->left_shatter_x - mario->x, brick->left_shatter_y - 20, 30, 30,
                           QPixmap(":/photo/brick2.png"));
        painter.drawPixmap(brick->left_shatter_x - mario->x, brick->left_shatter_y + 50, 30, 30,
                           QPixmap(":/photo/brick2.png"));
        painter.drawPixmap(brick->right_shatter_x - mario->x, brick->right_shatter_y - 20, 30, 30,
                           QPixmap(":/photo/brick3.png"));
        painter.drawPixmap(brick->right_shatter_x - mario->x, brick->right_shatter_y + 50, 30, 30,
                           QPixmap(":/photo/brick3.png"));
    }

    //绘制master master的第三个坐标代表状态 0代表死亡 第四个代表方向 0代表左侧
    for (QVector < QVector < int >> ::iterator it = master->m.begin()->begin(); it != master->m.begin()->end();it++)
    {
        if (*it->begin() - mario->x > -80 && *it->begin() - mario->x < 800 && *(it->begin() + 2) != 0)
        {
            painter.drawPixmap(*it->begin() - mario->x, *(it->begin() + 1), 40, 40,
                               QPixmap(":/photo/master_" + QString::number(*(it->begin() + 3)) + ".png"));
        }
        //
        //如果master被踩死  并且没有消失
        else if (*it->begin() - mario->x > -80 && *(it->begin()) - mario->x < 800 && *(it->begin() + 2) == 0 &&*(it->begin() + 4) == 1)
        {
            painter.drawPixmap(*it->begin() - mario->x, *(it->begin() + 1) + 20, 40, 20,
                               QPixmap(":/photo/master_" + QString::number(*(it->begin() + 3)) + ".png"));
        }

        //如果马里奥死亡
        if (mario->is_die)
        {
            painter.drawPixmap(mario->map_x, mario->y, QPixmap(":/photo/mary_die.png"), mario->die_pix_state, 0, 50, 50);//画角色
        }
        //如果没死亡
        else if (!mario->is_die && mario->invincible_state % 2 == 0 && !is_win)
        {
            painter.drawPixmap(mario->map_x, mario->y,
                               QPixmap(":/photo/walk_" + mario->direction + QString::number(mario->colour) + ".png"),
                               mario->walk_state, 0, 45, 45);//画角色
        }

        // if (fire->is_have) {
        //     painter.drawPixmap(fire->x - mary->x, fire->y, 20, 20, QPixmap(":/photo/fire.png"));
        // }
        // if (fire->is_have1) {
        //     painter.drawPixmap(fire->x1 - mary->x, fire->y1, 20, 20, QPixmap(":/photo/fire.png"));
        // }
        // if (fire->is_have2) {
        //     painter.drawPixmap(fire->x2 - mary->x, fire->y2, 20, 20, QPixmap(":/photo/fire.png"));
        // }
        //绘制旗帜


        QPixmap pixmap(":/photo/flag.png");
        QPixmap scaledPixmap = pixmap.scaled(50, 550);
        painter.drawPixmap(QPointF(9100 - mario->x, 0), scaledPixmap);


        QPixmap pixmap1(":/photo/flag2.png");
        QPixmap scaledPixmap1 = pixmap1.scaled(50, 50);
        if(mario->x < 8800){
            painter.drawPixmap(QPointF(9100 - mario-> x+30, 40), scaledPixmap1);
        }
        else{
            painter.drawPixmap(QPointF(9100 - mario-> x+30, mario->y), scaledPixmap1);
        }

    }

}

// 定时器事件
void Cinema::timerEvent(QTimerEvent *event)
{
    if (event->timerId() == timer1 && mario->is_die)
    {
        mario->Mario_die();
        Die_Init();
        update();
        return;
    }
    if (event->timerId() == timer1)
    {

        mario->Mario_Move(key);

        mario->Jump_And_Down();

        Jump_Collision();

        Move_Collision();

        brick->ShatterState();

        mushroom->Move_state();

        master->Master_Move();

        Die_Init();

        Fall_Down(mario->y);
        //fire->Fire_state();

        update();//刷新屏幕
    }

    if (event->timerId() == timer2)
    {
        mario->Mario_Move(key);
    }
    //数据更新频率
    if (event->timerId() == timer3)
    {
        time -= 0.04;

        if(time<=0)
        {
            //超时



            killTimer(timer1);
            if (is_kill_timer2)
            {
                //关闭计时器2
                killTimer(timer2);
            }
            //关闭计时器3
            killTimer(timer3);
            main_theme_Music->stop();
            Out_of_Time_Music->play();
            QTimer::singleShot(3000, this, [=](){
                Out_of_Time_Music->stop();

            } );
            Game_Over();

        }
        unknown->Unknown_State();
        unknown->Crash_state();
    }


}

//检测mario 是否落在什么东西的上面
void Cinema::Fall_Down(int &y)
{
    if (mario->height - mario->distance < 0)
    {
        //Mario落在地面
        if (y > 455)
        {
            y = 455;
            mario->is_jump_end = true;
            mario->distance = 0;
            mario->height = 20;
            return;
        }
        //Mario落在砖块上面
        for (QVector < QVector < int >> ::iterator it = brick->m.begin()->begin(); it != brick->m.begin()->end(); it++)
        {

            if (*it->begin() - mario->x - 300 >= -30 && *it->begin() - mario->x - 300 <= 30 &&
                *(it->begin() + 1) <= y + 50 && *(it->begin() + 1) >= y + 25 && *(it->begin() + 2) == 1)
            {
                y = *(it->begin() + 1) - 45;
                mario->is_jump_end = true;
                mario->height = mario->distance = 20;
                return;
            }
        }
        for (QVector < QVector < int >> ::iterator it = unknown->m.begin()->begin(); it != unknown->m.begin()->end();it++)
        {
            //Mario落在神秘方块上面
            if (*it->begin() - mario->x - 300 >= -30 && *it->begin() - mario->x - 300 <= 30 &&
                *(it->begin() + 1) <= y + 50 && *(it->begin() + 1) >= y + 25)
            {
                y = *(it->begin() + 1) - 45;
                mario->is_jump_end = true;
                mario->height = mario->distance = 20;
                return;
            }
        }
        //Mario落在管道上面
        for (QVector < QVector < int >> ::iterator it = pipe->long_m.begin()->begin(); it !=pipe->long_m.begin()->end();it++)
        {
            if (*it->begin() - mario->x - 300 >= -50 && *it->begin() - mario->x - 300 <= 30 &&
                *(it->begin() + 1) <= y + 50 && *(it->begin() + 1) >= y + 25)
            {
                y = *(it->begin() + 1) - 45;
                mario->is_jump_end = true;
                mario->height = mario->distance = 20;
                return;
            }
        }
        for (QVector < QVector < int >> ::iterator it = pipe->short_m.begin()->begin(); it != pipe->short_m.begin()->end();it++)
        {
            if (*it->begin() - mario->x - 300 >= -50 && *it->begin() - mario->x - 300 <= 30 &&
                *(it->begin() + 1) <= y + 50 && *(it->begin() + 1) >= y + 25)
            {
                y = *(it->begin() + 1) - 45;
                mario->is_jump_end = true;
                mario->height = mario->distance = 20;
                return;
            }
        }
    }
}


//检测mario 平移过程中 是否 碰到 障碍物
void Cinema::Move_Collision() {

    // 检测 mario 是否与砖块发生了碰撞
    for (QVector < QVector <int> >::iterator it = brick->m.begin()->begin(); it != brick->m.begin()->end(); it++)
    {
        // 如果 mario 向右移动并且与砖块相交
        if (*it->begin() - mario->x - 300 >= 35 && *it->begin() - mario->x - 300 <= 40 &&
            *(it->begin() + 1) > mario->y  -35 && *(it->begin() + 1) - mario->y < 35 &&
            mario->direction == "right" && *(it->begin() + 2) == 1)
        {
            mario->can_move = false; // 禁止移动
            return;
        }
        else if (*it->begin() - mario->x - 300 >= -40 && *it->begin() - mario->x - 300 <= -35 &&
                 *(it->begin() + 1) - mario->y > - 35 && *(it->begin() + 1) - mario->y < 35 &&
                 mario->direction == "left" && *(it->begin() + 2) == 1)
        {
            mario->can_move = false; // 禁止移动
            return;
        }
    }

    // 检测mario是否与神秘方块发生了碰撞
    for (QVector<QVector<int>>::iterator it = unknown->m.begin()->begin(); it != unknown->m.begin()->end(); it++)
    {
        // 如果mario向右移动并且与神秘方块碰撞
        if (*it->begin() - mario->x - 300 >= 35 && *it->begin() - mario->x - 300 <= 40 &&
            *(it->begin() + 1) - mario->y >= -35 && *(it->begin() + 1) - mario->y <= 35 && mario->direction == "right")
        {
            mario->can_move = false; // 禁止移动
            return;
        }
        else if (*it->begin() - mario->x - 300 >= -40 && *it->begin() - mario->x - 300 <= -35 &&
                 *(it->begin() + 1) - mario->y > - 35 && *(it->begin() + 1) - mario->y < 35 &&
                 mario->direction == "left" && *(it->begin() + 2) == 1)
        {
            mario->can_move = false; // 禁止移动
            return;
        }
    }

    // 检测mario 是否与水管发生了碰撞
    for (QVector<QVector<int>>::iterator it = pipe->long_m.begin()->begin(); it != pipe->long_m.begin()->end(); it++)
    {

        if (*it->begin() - mario->x - 300 >= 30 && *it->begin() - mario->x - 300 <= 35 &&
            *(it->begin() + 1) - mario->y <= 45 && mario->direction == "right")
        {
            mario->can_move = false; // 禁止移动
            return;
        }
        else if (*it->begin() - mario->x - 300 >= -55 && *it->begin() - mario->x - 300 <= -50 &&
                 *(it->begin() + 1) - mario->y <= 45 && mario->direction == "left")
        {
            mario->can_move = false; // 禁止移动
            return;
        }
    }

    for (QVector<QVector<int>>::iterator it = pipe->short_m.begin()->begin(); it != pipe->short_m.begin()->end(); it++)
    {
        if (*it->begin() - mario->x - 300 >= 30 && *it->begin() - mario->x - 300 <= 35 &&
            *(it->begin() + 1) < mario->y + 45 && mario->direction == "right")
        {
            mario->can_move = false; // 禁止移动
            return;
        }
        else if (*it->begin() - mario->x - 300 >= -55 && *it->begin() - mario->x - 300 <= -50 &&
                 *(it->begin() + 1) < mario->y + 45 && mario->direction == "left")
        {
            mario->can_move = false; // 禁止移动
            return;
        }
    }
    //检测与城堡的接触
    QVector < QVector < int >> ::iterator it = castle->m.begin()->begin();
    if (*it->begin() - mario->x - 300 >= -220 && *it->begin() - mario->x - 300 <= -40 &&
        *(it->begin() + 1) < mario->y - 100 && *(it->begin() + 1) > mario->y - 270) {

        is_win = true;
        main_theme_Music->stop();
        Game_Win_Music->play();


        if(is_win_dialog_show == false){
            qDebug()<<"auasgfcub";
            Game_Win();
            is_win_dialog_show = true;

        }


    }
    qDebug()<<mario->x;
    mario->can_move = true;

    if((9100 - mario->x) <=300 && mario->y < 460)
    {
        mario->x =8800;
        mario->y +=1;
        mario->is_jump = false;
        mario-> is_jump_end = true;
        mario->is_space_release = true;
        mario->distance = 0;
    }
    else if((9100 - mario->x) <= 300&&mario->y >= 460)
    {
        key = "right";
        mario->speed = 2;
        mario->y = 460;

    }

}



//检测mario跳跃过程中 是否 碰到 障碍物
void Cinema::Jump_Collision() {
    // 检查mario的跳跃高度是否为0或负值，如果是则直接返回，表示没有发生跳跃
    if (mario->height - mario->distance <= 0)
    {
        return;
    }

    // 遍历砖块对象中的砖块，检测是否发生了碰撞
    for (QVector<QVector<int>>::iterator it = brick->m.begin()->begin(); it != brick->m.begin()->end(); it++)
    {
        // 如果mario顶到砖块
        if (*it->begin() - mario->x - 300 >= -30 && *it->begin() - mario->x - 300 <= 30 &&
            *(it->begin() + 1) - mario->y + 40 >= -10 && *(it->begin() + 1) - mario->y + 40 <= 20 &&
            *(it->begin() + 2) == 1) {
            // 增加得分
            score += 5;
            // 碎裂砖块
            brick->BrickShatter(it);
            //设置砖块破碎音效
            brick_Break_Music->play();
            // 更新砖块状态
            *(it->begin() + 2) = 0;
            // 更新mario的位置

            //让mario停留在碰撞的位置
            mario->y = *(it->begin() + 1) + 40;
            mario->height = mario->distance;
            return;
        }
    }

    // 遍历神秘方块中的物体，检测是否发生了碰撞
    for (QVector<QVector<int>>::iterator it = unknown->m.begin()->begin(); it != unknown->m.begin()->end(); it++)
    {
        // 如果mario顶到神秘方块
        if (*it->begin() - mario->x - 300 >= -30 && *it->begin() - mario->x - 300 <= 30 &&
            *(it->begin() + 1) + 40 - mario->y  >= -10 && *(it->begin() + 1) + 40 - mario->y  <= 20) {
            // 如果神秘方块类型为金币（假设值为1）
            if (*(it->begin() + 2) == 1) {
                //
                Coin_Music->play();
                // 增加金币数量
                unknown->coin++;
                // 增加得分
                score += 10;
                // 执行神秘方块的碰撞动作（产生金币）
                //
                unknown->Unknown_crash(it);
            }
            // 如果神秘方块 类型为蘑菇（假设值为2）
            else if (*(it->begin() + 2) == 2) {
                // 出现蘑菇 并让蘑菇移动
                Mushroom_Music->play();
                mushroom->MushRoom_Move(it, unknown, brick, mario);
            }
            // 更新Mario的位置
            mario->y = *(it->begin() + 1) + 40;
            // 更新神秘方块的状态（变得不神秘）
            *(it->begin() + 2) = 0;

            // 更新Mario的高度
            mario->height = mario->distance;
            return;
        }
    }
}



// 初始化死亡状态
void Cinema::Die_Init()
{
    if (mario->is_die && key != "null")
    {
        mario->walk_state = 0;
        key = "null";
    }
    if (mario->invincible_state == 100)
    {
        mario->is_invincible = false;
        mario->invincible_state = 0;
    }
    if (mario->is_invincible)
    {
        mario->invincible_state += 1;
    }
    //如果马里奥死了
    if (mario->y > 500 && mario->life > 0)
    {

        mario->y = 455;
        mario->life--;
        main_theme_Music->stop();
        death_Music->play();
        killTimer(timer3);
        killTimer(timer1);
        game_start = false;
        QTimer::singleShot(2000, this, [=]() {
            mario->is_die = false;
            mario->is_invincible = true;
            timer1 = startTimer(15);//开启定时器
            timer3 = startTimer(40);
            game_start = true;
            mario->die_state = 0;
            mario->die_pix_state = -50;
            main_theme_Music->play();
        });
    }


    //如果生命死光了
    if (mario->y > 500 && mario->life <= 0)
    {
        killTimer(timer1);
        if (is_kill_timer2)
        {
            //关闭计时器2
            killTimer(timer2);
        }
        //关闭计时器3
        killTimer(timer3);
        main_theme_Music->stop();
        Out_of_Life_Music->play();
        QTimer::singleShot(3000, this, [=]() {
            Out_of_Life_Music->stop();
        });
        Game_Over();
    }

}

// 游戏胜利处理弹出新窗口，显示游戏胜利（理想情况下可以做一段小视频）
void Cinema::Game_Win()
{

    //
    killTimer(timer1);
    if (is_kill_timer2)
    {
        //关闭计时器2
        killTimer(timer2);
    }
    //关闭计时器3
    killTimer(timer3);
    QTimer::singleShot(1000, this, [=]() {
        game_start = false;

        is_win = true;

        update();

    });
    win = new Game_Win_dialog;
    win->setParent(this);
    win->show();
    qDebug()<<"55456515";
    //链接返回主界面
    connect(win->btn_Back, &QPushButton::clicked, this, [=](){


        QTimer::singleShot(500, this, [=]() {

            this->close();
            emit
                this->back();
        });



    });
    //链接重新游戏
    connect(win->btn_InitGame, &QPushButton::clicked, this, [=]() {


        QTimer::singleShot(500, this, [=]() {

            //
            //
            Game_Init();//游戏初始化
            qDebug()<<"5555";
            win->close();
            QTimer::singleShot(500, this, [=]() {
                timer1 = startTimer(15);//开启定时器
                timer3 = startTimer(40);
                game_start = true;
                is_win = false;
            });
            win->hide();

        });
    });

    //链接退出游戏
    connect(win->btn_Exit, &QPushButton::clicked, this, [=]() {

        QTimer::singleShot(500, this, [=]() {
            this->close();

        });
    });





}



//游戏失败处理
void Cinema::Game_Over()
{

    killTimer(timer1);
    if (is_kill_timer2)
    {
        //关闭计时器2
        killTimer(timer2);
    }
    //关闭计时器3
    killTimer(timer3);
    QTimer::singleShot(1000, this, [=]() {
        game_start = false;

        is_win = true;

        update();

    });
    win = new Game_Win_dialog;//初始化暂停窗口
    win->setParent(this);
    //链接返回主界面
    connect(win->btn_Back, &QPushButton::clicked, this, [=](){


        QTimer::singleShot(500, this, [=]() {

            this->close();
            emit
                this->back();
        });



    });
    //链接重新游戏
    connect(win->btn_InitGame, &QPushButton::clicked, this, [=]() {


        QTimer::singleShot(500, this, [=]() {

            //
            //
            Game_Init();//游戏初始化
            win->close();
            QTimer::singleShot(1500, this, [=]() {
                timer1 = startTimer(15);//开启定时器
                timer3 = startTimer(40);
                game_start = true;
            });
        });
    });

    //链接退出游戏
    connect(win->btn_Exit, &QPushButton::clicked, this, [=]() {

        QTimer::singleShot(500, this, [=]() {
            this->close();

        });
    });

    win->exec();


}

//初始化重新开始游戏的函数
void Cinema::Pause_Game_Init()
{
    key = "null";
    score = 0;
    time = 200.0;
    is_press_x = false;
    is_kill_timer2 = true;
    game_start = false;
    mario->Mario_Init();
    unknown->Unknown_Init();
    brick->BrickInit();
    mushroom->MushRoom_Init();
    master->Master_Init();
    master->Master_State(mario, pipe, brick);
}
