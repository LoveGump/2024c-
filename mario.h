#ifndef MARIO_H
#define MARIO_H

//主角马里奥类
#include<QString>

class Mario
{
public:
    Mario(); // 构造函数

    int x; // 角色的理论x坐标
    int map_x; // 角色在地图中的x坐标
    int y; // 角色y坐标
    int colour; // 角色颜色
    int life; // 角色生命
    int walk_state; // 行走动画状态
    int ground_state; // 地面动画状态
    int height; // 角色高度
    int distance; // 跳跃距离
    int die_state; // 死亡状态
    int die_pix_state; // 死亡像素状态

    int invincible_state; // 无敌状态
    bool can_move; // 是否可以移动
    bool is_invincible; // 是否无敌
    bool is_die; // 判断角色是否死亡
    bool is_jump; // 判断角色是否跳跃
    bool is_jump_end; // 判断角色单次跳跃是否结束
    bool is_space_release; // 空格键是否释放
    QString direction; // 角色移动的方向

    void Mario_Init(); // 角色初始化函数
    void Move_state(); // 移动状态更新函数

    void Mario_Move(const QString &direction); // 角色移动函数
    void Jump_And_Down(); // 跳跃和下落函数
    void Mario_die(); // 角色死亡函数
};

#endif // MARIO_H
