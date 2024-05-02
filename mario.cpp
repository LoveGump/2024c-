#include "mario.h"

Mario::Mario() {
    //初始化马里奥的状态
    Mario_Init();
}
void Mario::Mario_Init() {
    x = 0; // 角色的理论x坐标
    map_x =0 ; // 角色在地图中的x坐标
    y = 455; // 角色y坐标
    colour = 1; // 角色颜色
    life = 5; // 角色生命
    height = 20; // 角色高度

    distance = 0; // 跳跃距离

    walk_state = 0; // 行走动画状态
    ground_state = 0; // 地面动画状态

    die_state = 0; // 死亡状态
    die_pix_state = -50; // 死亡像素状态
    invincible_state = false; // 无敌状态
    can_move = true; // 是否可以移动

    is_invincible = false; // 是否无敌

    is_die = false; // 判断角色是否死亡

    is_jump = false; // 判断角色是否跳跃
    is_jump_end = true; // 判断角色单次跳跃是否结束
    is_space_release = true; // 空格键是否释放

    direction = "right";

}

void Mario::Move_state() // 移动状态更新函数
{
    //如果walk_state==1140，walk_state = 0
    if (walk_state == 1197) {
        walk_state = 0;
    }
    //如果ground_state==805，ground_state = 5
    if (ground_state == 805) {
        ground_state = 5;
    }
    //如果ground_state==-5，ground_state = 795
    else if (ground_state == -5) {
        ground_state = 795;
    }
    // 如果不在跳跃中，则行走动画状态归零
    if (!is_jump_end) {
        walk_state = 0;
    }
}
void Mario::Mario_Move(const QString &direction)// 角色移动函数
{
    //如果方向向右 并且x坐标小于300 并且处于可以移动的状态下
    if (direction == "right" && x < 300 && can_move) {
        x += 5;
        map_x += 5;
        walk_state += 57;
    }
    //如果方向向左 并且0 <= x <= 300 并且处于可以移动的状态下
    else if (direction == "left" && x <= 300 && x >= 0 && can_move) {
        x -= 5;
        map_x -= 5;
        walk_state += 57;
    }
    //如果方向向右 并且 x >= 300 并且处于可以移动的状态下
    else if (direction == "right" && x >= 300 && can_move) {
        x += 5;
        walk_state += 57;
        ground_state += 5;
    }
    //如果方向向左 并且 x >= 300 并且处于可以移动的状态下
    else if (direction == "left" && x >= 300 && can_move) {
        x -= 5;
        walk_state += 57;
        ground_state -= 5;
    }
    else if ((direction == "left" && x < 0) || (!can_move && direction != "null")) {
        walk_state += 57;
    }
    Move_state();
}
void Mario::Jump_And_Down()// 跳跃和下落函数
{
    //如果正在跳跃，跳跃结束 并且按下space 按键
    if (is_jump && is_jump_end && is_space_release) {
        is_space_release = false;//每按一次空格键只能触发一次跳跃

        is_jump_end = false;//跳跃状态开始
        distance = 1;
    }
    //按下按钮之后，开始更新跳跃的状态
    if (distance > 0) {
        y -= height - distance;
        distance++;
    }

}

void Mario::Mario_die() {
    // 如果马里奥 死了 并且 死亡向上动画尚未完成
    if (is_die && die_state < 30) {
        // 将马里奥向上移动并增加死亡动画状态
        y -= 5;
        die_state++;
        // 更新与像素相关的状态以完成死亡动画
        die_pix_state += 50;
    }
    //如果马里奥 死了 并且 死亡向上动画 完成  开始向下的动画
    else if (is_die && die_state >= 30) {
        // 一旦死亡 向上的动画完成，将马里奥向下移动
        y += 5;
        die_state++;
    }

}



