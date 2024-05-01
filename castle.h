#ifndef CASTLE_H
#define CASTLE_H

#include<QVector>
#include<QMap>

class Castle
{
public:
    QMap<int, QVector<QVector<int>>> m; // QMap，储存城堡的坐标
    void Castle_Init(); // 初始化城堡的函数声明
    QVector<int> v;
    QVector<QVector<int>> v1; // 二维vector
    Castle();
};

#endif // CASTLE_H
