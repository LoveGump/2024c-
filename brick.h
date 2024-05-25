#ifndef BRICK_H
#define BRICK_H

#include<QVector>
#include<QMap>

class Brick
{


public:
    QVector<int> v;
    QVector<QVector<int>> v2; // 储存坐标的二维容器
    QMap<int, QVector<QVector<int>>> m;

    int left_shatter_x; // 左碎块的 x 坐标
    int left_shatter_y; // 左碎块的 y 坐标
    int right_shatter_x; // 右碎块的 x 坐标
    int right_shatter_y; // 右碎块的 y 坐标

    //
    //1
    int shatter_state; // 砖块的状态

    Brick(); // 构造函数声明

    // 初始化砖块
    void BrickInit();

    // 获取碎块状态的函数声明
    void ShatterState();

    // 碎裂砖块的函数声明，接受一个二维整数向量的迭代器作为参数
    void BrickShatter(QVector<QVector<int>>::iterator it);
};

#endif // BRICK_H
