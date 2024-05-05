#include "castle.h"

Castle::Castle() {
       Castle_Init();
}

//初始化城堡
void Castle::Castle_Init() {
    //将城堡坐标添加进 m中
    v.push_back(9400);
    v.push_back(240);
    v1.push_back(v);
    m.insert(1, v1);
    v.clear();
    v1.clear();
}
