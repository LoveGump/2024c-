#include "mainwindow.h"
#include "game_help.h"
#include"game_scene.h"
#include "my_pushbutton.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //设置窗口名字
    this->setWindowTitle("Super_Mario_bro");
    //设置窗口大小
    this->setFixedSize(800,545);
    //设置图标
    QApplication::setWindowIcon(QIcon(":/photo/icon.png"));
    //设置开始游戏按钮
    My_PushButton *start_Btn = new My_PushButton(":/photo/start3.png");
    //设置父类
    start_Btn->setParent(this);
    //设置开始按钮坐标
    start_Btn->move(100,this->height()*0.25);
    // 创建声音效果对象
    QSoundEffect *start_Music=new QSoundEffect;
    // 设置音频文件的路径
    start_Music->setSource(QUrl::fromLocalFile(":/music/start.wav"));

    start_Music->setLoopCount(QSoundEffect::Infinite);  //设置无限循环
    start_Music->setVolume(0.5f);  //设置音量，在0到1之间

    //设置按下按钮之后的事件
    connect(start_Btn, &QPushButton::clicked, [=](){
        //先触发动画
        start_Btn->zoom1();
        start_Btn->zoom2();
       // start_Music->play(); // 播放声音
        //  start_Music->play(); //结束播放
        //  之后等动画结束之后进入游戏
        QTimer::singleShot(500,this,[=](){
            this->hide();
            Game_Scene *gamescene=new Game_Scene;
            gamescene->show();

        });
    });


    //设置帮助按钮
    My_PushButton *help_Btn=new My_PushButton(":/photo/help3.png");
    help_Btn->setParent(this);
    help_Btn->move(100,this->height()*0.40);
    connect(help_Btn,&QPushButton::clicked,[=](){
        help_Btn->zoom1();
        help_Btn->zoom2();
        QTimer::singleShot(400,this,[=](){

            this->hide();
            game_help *gamehelp=new game_help();
            gamehelp->show();
         connect(gamehelp,&game_help::back,this,[=](){
                this->show();
           });
        });
    });

    //设置结束按钮
    My_PushButton *end_Btn=new My_PushButton(":/photo/end3.png");
    end_Btn->setParent(this);
    end_Btn->move(100,this->height()*0.55);
    connect(end_Btn,&QPushButton::clicked,[=](){
        end_Btn->zoom1();
        end_Btn->zoom2();
        QTimer::singleShot(500,this,[=](){
            this->close();
        });
    });

}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    painter.drawPixmap(0,0,800,550,QPixmap(":/photo/background.jpg"));//画背景图
}
