#include "brick.h"

Brick::Brick() {

    //初始化砖块
     BrickInit();
}

void Brick::BrickInit() {
    //初始化砖块状态
    shatter_state = 0;

    //绘制砖块的位置（横坐标，纵坐标）
    int arr[51][2] = {{1000, 350},
                      {1100, 350},
                      {1200, 350},
                      {3200, 350},
                      {3250, 350},
                      {3600, 350},
                      {3700, 350},
                      {3750, 200},
                      {3800, 200},
                      {3850, 200},
                      {3900, 200},
                      {3950, 200},
                      {4000, 200},
                      {4050, 200},
                      {4300, 200},
                      {4350, 200},
                      {4400, 200},
                      {4450, 350},
                      {4750, 350},
                      {4800, 350},
                      {5600, 350},
                      {5750, 200},
                      {5800, 200},
                      {5850, 200},
                      {6050, 200},
                      {6100, 350},
                      {6150, 350},
                      {6200, 350},
                      {6400, 460},
                      {6450, 460},
                      {6500, 460},
                      {6550, 460},
                      {6700, 460},
                      {6750, 460},
                      {6800, 460},
                      {6850, 460},
                      {6450, 420},
                      {6500, 420},
                      {6550, 420},
                      {6700, 420},
                      {6750, 420},
                      {6800, 420},
                      {6500, 380},
                      {6550, 380},
                      {6700, 380},
                      {6750, 380},
                      {6550, 340},
                      {6700, 340},
                      {7250, 350},
                      {7300, 350},
                      {7400, 350},
                      };
    //将坐标放入v2
    for (int i = 0; i < 51; i++) {
        v.push_back(arr[i][0]);
        v.push_back(arr[i][1]);
        v.push_back(1);            //1在后续的过程中代表砖块没有碎
        v2.push_back(v);
        v.clear();
    }
    //将v2插入m（）
    m.insert(1, v2);
}


// 碎裂砖块的函数声明，接受砖块此时的坐标
void Brick::BrickShatter(QVector<QVector<int>>::iterator it)
{
    //设置x坐标
    left_shatter_x = *it->begin();
    right_shatter_x = *it->begin() + 20;
    //设置y坐标 ，当前高度就行
    left_shatter_y =*(it->begin() + 1);
    right_shatter_y = *(it->begin() + 1);
    //表示砖块的状态为破碎
    shatter_state = 1;

}

// 获取碎块状态的函数声明
void Brick::ShatterState()
{
    // 如果砖块未破碎，直接返回
    if (shatter_state == 0)
    {
        return;
    }

    // 如果砖块正在破碎过程中
    if (shatter_state > 0 && shatter_state < 10) {
        // 砖块在水平方向上变宽
        left_shatter_x -= 20 - shatter_state;
        right_shatter_x += 20 - shatter_state;
        // 砖块在垂直方向上变高
        left_shatter_y -= 20 - shatter_state;
        right_shatter_y -= 20 - shatter_state;
        // 增加破碎状态的计数
        shatter_state++;
    }
    // 如果破碎状态已经过了扩展阶段，且砖块还未完全消失
    else if (shatter_state >= 10 && left_shatter_y < 500) {
        // 砖块向下移动
        left_shatter_y += shatter_state;
        right_shatter_y += shatter_state;
        // 增加破碎状态的计数
        shatter_state++;
    }
    // 如果砖块完全消失
    else if (left_shatter_y >= 500) {
        // 重置破碎相关的变量
        left_shatter_x = right_shatter_x = left_shatter_y = right_shatter_y = 0;
        // 重置破碎状态
        shatter_state = 0;
    }
}
