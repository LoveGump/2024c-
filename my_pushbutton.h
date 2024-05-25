#ifndef MY_PUSHBUTTON_H
#define MY_PUSHBUTTON_H

#include <QPushButton>
#include<QObject>
#include<QString>
#include<QPropertyAnimation>
#include <QSoundEffect>
#include <QUrl>


class My_PushButton : public QPushButton {
    Q_OBJECT
public:
    QSoundEffect *mouse_Press_Music;

    // 构造函数，接受一个参数表示普通状态下的图片路径
    My_PushButton(QString normalImg);
    // 成员变量，存储普通状态下的图片路径
    QString normalImgPath;

    //重写鼠标按下函数
    void mousePressEvent(QMouseEvent *event);

    // 点击效果动画1
    void zoom1();
    // 点击效果动画2
    void zoom2();

signals:

};
#endif // MY_PUSHBUTTON_H
