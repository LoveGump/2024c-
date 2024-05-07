#include "mushroom.h"

MushRoom::MushRoom() {
    MushRoom_Init();
}

//初始化mushroom
void MushRoom::MushRoom_Init()
{

    Grow_up_Music = new QSoundEffect;
    Grow_up_Music->setSource(QUrl::fromLocalFile(":/music/mushroom.wav"));
    Grow_up_Music->setVolume(0.5f);

    mushroom_kind=0;
    mushroom_x=0;
    mushroom_y=0;
    mushroom_state=0;
    mushroom_fall_down_distance=19;
}

//mushroom的移动函数
void MushRoom::MushRoom_Move(QVector<QVector<int>>::iterator it,Unknown_Surprise *u,Brick *r, Mario *m){
    unknown = u;
    brick = r;
    mario = m;
    //如果马里奥的颜色是1 那就将此时的蘑菇种类更新为1
    if(mario->colour==1)
    {
        mushroom_kind = 1;
    }//否则蘑菇种类为2
    else
    {
        mushroom_kind = 2;
    }
    mushroom_x = *it->begin();
    mushroom_y = *(it->begin() + 1);
    //蘑菇的状态为1
    mushroom_state = 1;
}
void MushRoom::Move_state(){
    //如果蘑菇状态不为 0 或者 -2
    if (mushroom_state != 0 && mushroom_state != -2) {
        //如果蘑菇的状态小于等于20
        if (mushroom_state <= 20)
        {
            //
            mushroom_y -= 2;

            mushroom_state++;
        } else if (mushroom_state > 20)
        {
            mushroom_x += 2;

            mushroom_state++;
        }
        // 检查蘑菇是否与砖块碰撞
        for (QVector < QVector < int >> ::iterator it = brick->m.begin()->begin(); it != brick->m.begin()->end();it++){
            if (*it->begin() - mushroom_x >= -50 && *it->begin() - mushroom_x <= 30 &&
                *(it->begin() + 1) <= mushroom_y + 40 && *(it->begin() + 1) >= mushroom_y && *(it->begin() + 2) != 0) {
                return;
            }
        }
        // 检查蘑菇是否与未知砖块碰撞
        for (QVector < QVector < int >> ::iterator it = unknown->m.begin()->begin(); it != unknown->m.begin()->end();it++){
            if (*it->begin() - mushroom_x >= -50 && *it->begin() - mushroom_x <= 30 &&
                *(it->begin() + 1) <= mushroom_y + 40 && *(it->begin() + 1) >= mushroom_y) {
                return;
            }
        }
        //
        //
        // 检查蘑菇是否与管道碰撞
        for (QVector < QVector < int >> ::iterator it = unknown->m.begin()->begin(); it != unknown->m.begin()->end();it++){
            if (*it->begin() - mushroom_x >= -50 && *it->begin() - mushroom_x <= 30 &&
                *(it->begin() + 1) <= mushroom_y + 40 && *(it->begin() + 1) >= mushroom_y) {
                return;
            }
        }

        mushroom_state = -1;
        mushroom_y += 20 - mushroom_fall_down_distance;
        mushroom_fall_down_distance--;
    }
    //吃掉蘑菇

    if (mushroom_y >= 460 && mushroom_state != 0) {
        if (mushroom_x - 330 <= mario->x && mushroom_x - 270 >= mario->x && mushroom_y - mario->y == 5) {
            Grow_up_Music->play();

            mushroom_state = 0;
            mario->colour = mushroom_kind + 1;
            mushroom_fall_down_distance = 19;
            return;
        }
        mushroom_state = -2;
        mushroom_y = 460;
        mushroom_x -= 2;
    }
}
