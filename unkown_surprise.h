#ifndef UNKNOWN_SURPRISE_H
#define UNKNOWN_SURPRISE_H

#include<QVector>
#include<QMap>


class Unknown_Surprise
{
public:

    int coin;//金币
    int coin_x;//金币的横坐标
    int coin_y;//金币的纵坐标
    int unknown_state;//未知惊喜的状态
    int coin_state;//金币的状态
    QVector<int> v;
    QVector <QVector<int>> v2;
    QMap<int, QVector<QVector < int>>> m;

    Unknown_Surprise();

    //初始化
    void Unknown_Init(); // 初始化未知方块状态

    void Unknown_State(); // 更新未知方块状态

    void Crash_state(); // 更新碰撞状态

    void Unknown_crash(QVector<QVector<int>>::iterator it); // 处理顶到未知方块
};



#endif // UNKOWN_SURPRISE_H
