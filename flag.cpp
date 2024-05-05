#include "flag.h"

Flag::Flag() {
    Flag_Init();
}
void Flag::Flag_Init()
{
    //将旗帜坐标添加进 m中
    v.push_back(9100);
    v.push_back(20);
    v1.push_back(v);
    m.insert(1, v1);
    v.clear();
    v1.clear();
}
