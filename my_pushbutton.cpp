#include "my_pushbutton.h"
#include<QMouseEvent>
#include<QDebug>

My_PushButton::My_PushButton(QString normalImg) {

    // 将传入的图片路径赋值给成员变量 normalImgPath
    this->normalImgPath = normalImg;

    // 声明 QPixmap 对象 pix ,加载图片
    QPixmap pix;
    pix.load(normalImg);

    // 设置按钮的固定大小为 200x100 像素
    this->setFixedSize(200, 100);

    // 设置按钮样式表，移除边框
    this->setStyleSheet("QPushButton{border:0px;}");

    // 设置按钮的图标为加载的图片
    this->setIcon(pix);

    // 设置按钮图标的大小为 200x100 像素
    this->setIconSize(QSize(200, 100));

    mouse_Press_Music = new QSoundEffect;
    mouse_Press_Music->setSource(QUrl::fromLocalFile(":/music/my_pushbutton_press.wav"));
    mouse_Press_Music->setVolume(0.5f);

}

//点击动画效果1
void My_PushButton::zoom1() {
    // 创建一个属性动画，作用对象是当前按钮对象，属性是 geometry（位置和大小）
    QPropertyAnimation *animation = new QPropertyAnimation(this, "geometry");

    // 设置动画持续时间为200毫秒
    animation->setDuration(200);

    // 设置动画的起始值为当前按钮的位置和大小
    animation->setStartValue(QRect(this->x(), this->y(), this->width(), this->height()));

    // 设置动画的结束值为当前按钮的位置向下移动10个像素，但宽度和高度不变
    animation->setEndValue(QRect(this->x(), this->y() + 10, this->width(), this->height()));

    // 设置动画的缓动曲线为弹跳效果
    animation->setEasingCurve(QEasingCurve::OutBounce);

    // 启动动画
    animation->start();
}
//点击动画效果2
void My_PushButton::zoom2() {
    // 创建一个属性动画，作用对象是当前按钮对象，属性是 geometry（位置和大小）
    QPropertyAnimation *animation = new QPropertyAnimation(this, "geometry");

    // 设置动画持续时间为200毫秒
    animation->setDuration(200);

    // 设置动画的起始值为当前按钮的位置向下移动10个像素，但宽度和高度不变
    animation->setStartValue(QRect(this->x(), this->y() + 10, this->width(), this->height()));

    // 设置动画的结束值为当前按钮的原始位置，但宽度和高度不变
    animation->setEndValue(QRect(this->x(), this->y(), this->width(), this->height()));

    // 设置动画的缓动曲线为弹跳效果
    animation->setEasingCurve(QEasingCurve::OutBounce);

    // 启动动画
    animation->start();
}

//重写鼠标按下函数
void My_PushButton::mousePressEvent(QMouseEvent *event)
{
    // 按钮被按下时播放音效
    if (event->button() == Qt::LeftButton) {
        qDebug()<<1;
        mouse_Press_Music->play();
    }
    // 调用父类的事件处理函数
    QPushButton::mousePressEvent(event);
}
