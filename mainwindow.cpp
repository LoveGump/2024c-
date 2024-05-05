#include "mainwindow.h"


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
    QApplication::setWindowIcon(QIcon(":/photo/mario.png"));
    //设置开始游戏按钮
    start_Btn = new My_PushButton(":/photo/start3.png");
    //设置父类
    start_Btn->setParent(this);
    //设置开始按钮坐标
    start_Btn->move(100,this->height()*0.25);


    // 创建声音效果对象
    background_Music = new QSoundEffect;
    // 设置音频文件的路径
    background_Music->setSource(QUrl::fromLocalFile(":/music/start.wav"));
    // QUrl::fromLocalFile(":/music/start.wav")
    background_Music->setLoopCount(QSoundEffect::Infinite);  //设置无限循环
    background_Music->setVolume(0.5f);  //设置音量，在0到1之间
    background_Music->play(); // 播放声音

    stage_clear_Music = new QSoundEffect;
    stage_clear_Music->setSource(QUrl::fromLocalFile(":/music/stage_clear.wav"));
    stage_clear_Music->setVolume(0.5f);


    //设置按下按钮之后的事件
    connect(start_Btn, &QPushButton::clicked, [=](){
        //先触发动画
        start_Btn->zoom1();
        start_Btn->zoom2();

        background_Music->stop(); //结束播放

        QTimer::singleShot(500,this,[=](){
            this->hide();
            stage_clear_Music->play();

            gamescene = new Cinema;

            gamescene->show();
            QTimer::singleShot(1500, this, [=]() {
                stage_clear_Music->stop();

            });
            connect(gamescene,&Cinema::back,this,[=](){
                this->show();
                background_Music->play();
            });

        });
    });



    //设置帮助按钮
    help_Btn = new My_PushButton(":/photo/help3.png");
    help_Btn->setParent(this);
    help_Btn->move(100,this->height()*0.40);
    connect(help_Btn,&QPushButton::clicked,[=](){
        help_Btn->zoom1();
        help_Btn->zoom2();
        QTimer::singleShot(400,this,[=](){

            this->hide();
            gamehelp = new game_help();
            gamehelp->show();
         connect(gamehelp,&game_help::back,this,[=](){
                this->show();
           });
        });
    });

    //设置结束按钮
   end_Btn = new My_PushButton(":/photo/end3.png");
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
