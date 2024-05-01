#include "pipe.h"

Pipe::Pipe() {
    //初始化管道
}
//初始话管道
void Pipe::Pipe_Init()
{
    //长管道
    int arr_long[4][2] = {{1800, 400},
                          {2100, 400},
                          {2400, 400},
                          {2700, 400}};
    //短管道
    int arr_short[3][2] = {{1500, 450},
                           {7100, 450},
                           {7650, 450}};
    //将长管道插入v2
    for (int i = 0; i < 4; i++) {
        v.push_back(arr_long[i][0]);
        v.push_back(arr_long[i][1]);
        v2.push_back(v);
        v.clear();
    }
    //将长管道坐标插入long_map
    long_m.insert(1, v2);
    v2.clear();
    //将短管道坐标插入v2
    for (int i = 0; i < 3; i++) {
        v.push_back(arr_short[i][0]);
        v.push_back(arr_short[i][1]);
        v2.push_back(v);
        v.clear();
    }
    //将短管道插short_map
    short_m.insert(1, v2);
    v2.clear();

}
