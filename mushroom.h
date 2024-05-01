#ifndef MUSHROOM_H
#define MUSHROOM_H

#include<QVector>
#include<QMap>
#include"brick.h"
#include"unkown_surprise.h"
#include"mario.h"
#include"castle.h"


class MushRoom
{
public:
    //储存mushroom的坐标
    QMap<int,QVector<QVector<int>>>m;
    //mushroom的形态
    int mushroom_kind;
    //mushroom的坐标
    int mushroom_x;
    int mushroom_y;
    //mushroom的状态
    int mushroom_state;
    int mushroom_fall_down_distance;
    //砖块
    Brick *brick;
    Unknown_Surprise *unknown;
    Mario *mario;

    MushRoom();

    //初始化mushroom
    void MushRoom_Init();

    //更新mushroom的状态
    void Move_state();

    //mushroom的移动
    void MushRoom_Move(QVector<QVector<int>>::iterator it,Unknown_Surprise *u,Brick *r, Mario *m);


};

#endif // MUSHROOM_H
