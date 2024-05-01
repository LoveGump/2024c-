#ifndef CASTLE_H
#define CASTLE_H

#include<QVector>
#include<QMap>

class Castle
{
public:
    QMap<int, QVector<QVector<int>>> m; // QMap，键为整数，值为二维整数向量的映射
    void Castle_Init(); // 初始化城堡的函数声明
    QVector<int> v; // 整数向量 v
    QVector<QVector<int>> v1; // 二维vector v1
    Castle();
};

#endif // CASTLE_H
