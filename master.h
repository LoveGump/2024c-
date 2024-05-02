#ifndef MASTER_H
#define MASTER_H

#include<QMap>
#include<QVector>

#include"mario.h"
#include"pipe.h"
#include"brick.h"

class Master
{
public:
    int die_state;

    Mario *mario;
    Pipe *pipe;
    Brick *brick;

    QVector<int> v;
    QVector <QVector<int>> v1;
    QMap<int, QVector<QVector < int>>> m;

    Master();
    //怪兽初始化
    void Master_Init();
    //指针
    void Master_State(Mario *m, Pipe *p, Brick *r);
    //怪兽移动处理
    void Master_Move();
};

#endif // MASTER_H
