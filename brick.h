#ifndef BRICK_H
#define BRICK_H

class Brick
{
public:
    QVector<int> v; // 存储整数值的向量
    QVector<QVector<int>> v2; // 存储整数向量的二维向量
    QMap<int, QVector<QVector<int>>> m; // 将整数键映射到二维整数向量的映射

    int left_shatter_x; // 左碎块的 x 坐标
    int left_shatter_y; // 左碎块的 y 坐标
    int right_shatter_x; // 右碎块的 x 坐标
    int right_shatter_y; // 右碎块的 y 坐标
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
