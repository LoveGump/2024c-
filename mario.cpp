#include "mario.h"

Mario::Mario() {

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
    // //如果行走了1140，回到出发点
    // if (walk_state == 1140) {
    //     walk_state = 0;
    // }
    // if (ground_state == 805) {
    //     ground_state = 5;
    // } else if (ground_state == -5) {
    //     ground_state = 795;
    // }
    // // 如果不在跳跃中，则行走动画状态归零
    // if (!is_jump_end) {
    //     walk_state = 0;
    // }
}
void Mario::Mario_Move(const QString &direction)// 角色移动函数
{
    // if (direction == "right" && x < 300 && can_move) {
    //     x += 5;
    //     map_x += 5;
    //     walk_state += 57;
    // } else if (direction == "left" && x <= 300 && x >= 0 && can_move) {
    //     x -= 5;
    //     map_x -= 5;
    //     walk_state += 57;
    // } else if (direction == "right" && x >= 300 && can_move) {
    //     x += 5;
    //     walk_state += 57;
    //     ground_state += 5;
    // } else if (direction == "left" && x > 300 && can_move) {
    //     x -= 5;
    //     walk_state += 57;
    //     ground_state -= 5;
    // } else if ((direction == "left" && x < 0) || (!can_move && direction != "null")) {
    //     walk_state += 57;
    // }
    // Move_state();
}
void Mario::Jump_And_Down()// 跳跃和下落函数
{
    // if (is_jump && is_jump_end && is_space_release) {
    //     is_space_release = false;//每按一次空格键只能触发一次跳跃
    //     is_jump_end = false;//跳跃状态开始
    //     distance = 1;
    // }
    // if (distance > 0) {
    //     y -= height - distance;
    //     distance++;
    // }
    // if (distance > 0) {
    //     y -= height - distance;
    //     distance++;
    // }
}

void Mario::Mario_die() {
    // // 检查马里奥是否处于死亡状态并且死亡动画尚未完成
    // if (is_die && die_state < 20) {
    //     // 将马里奥向上移动并增加死亡动画状态
    //     y -= 5;
    //     die_state++;
    //     // 更新与像素相关的状态以完成死亡动画
    //     die_pix_state += 50;
    // } else if (is_die && die_state >= 20) {
    //     // 一旦死亡动画完成，将马里奥向下移动
    //     y += 5;
    //     die_state++;
    // }
    // // 添加注释以解释函数的目的和功能
}



