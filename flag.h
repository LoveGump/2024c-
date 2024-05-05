#ifndef FLAG_H
#define FLAG_H

#include<QMap>

class Flag
{
public:
    Flag();
    QMap<int, QVector<QVector<int>>> m; // QMap，储存城堡的坐标
    void Flag_Init(); // 初始化城堡的函数声明
    QVector<int> v;
    QVector<QVector<int>> v1; // 二维vector

};

#endif // FLAG_H
