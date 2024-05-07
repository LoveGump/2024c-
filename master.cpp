#include "master.h"
#include<QSoundEffect>

Master::Master() {
    Master_Init();
}
//怪兽初始化
void Master::Master_Init()
{
    master_Death_Music = new QSoundEffect;
    master_Death_Music->setSource(QUrl::fromLocalFile(":/music/master_death.wav"));
    master_Death_Music->setVolume(0.5f);

    die_state = 0;
    //怪兽坐标
    int arr[10][2] = {{1100, 460},
                      {2670, 460},
                      {3000, 460},
                      {3200, 460},
                      {3230, 460},
                      {3600, 460},
                      {4000, 460},
                      {4500, 460},
                      {5500, 460},
                      {6200, 460}};

    for (int i = 0; i < 10; i++)
    {
        v.push_back(arr[i][0]);
        v.push_back(arr[i][1]);
        v.push_back(1);
        v.push_back(0);//0代表左
        v.push_back(0);//0代表没有展示压扁的master
        v1.push_back(v);
        v.clear();
    }
    m.insert(1, v1);
    v1.clear();
}

void Master::Master_State(Mario *m, Pipe *p, Brick *r)
{
    mario = m;
    pipe = p;
    brick = r;
}

void Master::Master_Move()
{
    if (die_state != 0)
    {
        die_state++;
    }
    for (QVector<QVector < int>>::iterator itm = m.begin()->begin(); itm != m.begin()->end(); itm++)
    {
        if (die_state == 25 && *(itm->begin() + 4) == 1)
        {
            die_state = 0;
            *(itm->begin() + 4) = 2;
        }
        if (*itm->begin() - mario->x >= -40 && *itm->begin() - mario->x <= 800 && *(itm->begin() + 2) == 1)
        {
            //如果在马里奥的脚下就被踩死
            if (*itm->begin() - mario->x <= 340 && *itm->begin() - mario->x >= 270
                && mario->y - *(itm->begin() + 1) > -50 && mario->y -*(itm->begin() + 1)< -5 && !mario->is_jump)
            {
                master_Death_Music->play();
                die_state = 1;
                *(itm->begin() + 4) = 1;
                mario->is_jump_end = false;//跳跃状态开始
                mario->distance = 1;
                *(itm->begin() + 2) = 0;
                return;
            }

            //如果碰到马里奥
            if (((*itm->begin() - mario->x >= 330 && *itm->begin() - mario->x <= 340) ||
                 (*itm->begin() - mario->x >= 270 && *itm->begin() - mario->x <= 280)) && mario->y - *(itm->begin()+1) == -5)
            {
                //如果马里奥状态为普通的 1 状态，马里奥死亡
                if (mario->colour == 1 && !mario->is_invincible)
                {
                    mario->is_die = true;
                }
                //如果马里奥吃了蘑菇，马里奥颜色消失 暂时无敌
                else if (mario->colour != 1 && !mario->is_invincible)
                {
                    mario->colour = 1;
                    mario->is_invincible = true;

                }
            }

            //开始移动
            if (*(itm->begin() + 3) == 1)
            {
                *itm->begin() += 1;
            }
            else if (*(itm->begin() + 3) == 0)
            {
                *itm->begin() -= 1;
            }

            //碰到砖块master改变方向
            for (QVector < QVector < int >> ::iterator it = brick->m.begin()->begin(); it != brick->m.begin()->end();it++)
            {
                if (*it->begin() - *itm->begin() == 40 && *(it->begin() + 2) == 1 &&*(itm->begin() + 3) ==1 &&
                    *(it->begin() + 1) == *(itm->begin() + 1))
                {
                    *(itm->begin() + 3) = 0;
                    return;
                }
                if (*it->begin() - *itm->begin() == -50 && *(it->begin() + 2) == 1 &&*(itm->begin() + 3) ==0 &&
                    *(it->begin() + 1) == *(itm->begin() + 1))
                {
                    *(itm->begin() + 3) = 1;
                    return;
                }
            }

            //碰到管道master改变方向
            for (QVector < QVector < int >> ::iterator it = pipe->long_m.begin()->begin(); it != pipe->long_m.begin()->end();it++)
            {
                if (*it->begin() - *itm->begin() == 40)
                {
                    *(itm->begin() + 3) = 0;
                    return;
                }
                else if (*it->begin() - *itm->begin() == -80)
                {
                    *(itm->begin() + 3) = 1;
                    return;
                }
            }
            for (QVector < QVector < int >> ::iterator it = pipe->short_m.begin()->begin(); it != pipe->short_m.begin()->end();it++)
            {
                if (*it->begin() - *itm->begin() == 40)
                {
                    *(itm->begin() + 3) = 0;
                    return;
                }
                else if (*it->begin() - *itm->begin() == -80)
                {
                    *(itm->begin() + 3) = 1;
                    return;
                }
            }


        }

    }

}




