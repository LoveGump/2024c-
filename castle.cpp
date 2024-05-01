#include "castle.h"

Castle::Castle() {
       Castle_Init();
}
void Castle::Castle_Init() { // Castle 类的 Castle_Init 函数定义开始

    v.push_back(8700); // 向整数向量 v 中添加值 8700
    v.push_back(70);   // 向整数向量 v 中添加值 70
    v1.push_back(v);   // 将整数向量 v 添加到二维整数向量 v1 中
    m.insert(1, v1);   // 将键值对 <1, v1> 插入到 QMap m 中
    v.clear();         // 清空整数向量 v
    v1.clear();        // 清空二维整数向量 v1

}
