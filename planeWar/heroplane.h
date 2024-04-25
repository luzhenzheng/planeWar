#ifndef HEROPLANE_H
#define HEROPLANE_H
#include<QPixmap>
#include<QRect>
#include"bullet.h"
#include"config.h"
class HeroPlane
{
public:
    HeroPlane();
public:
    void shoot();
    void setPosition(int x,int y);
    //飞机图片
    QPixmap m_Plane;
    //飞机资源
    int m_X;
    int m_Y;
    //飞机矩形 用于碰撞检测
    QRect m_Rect;
    //弹匣
    Bullet m_bullets[BULLET_NUM];
    //发射间隔记录
    int m_recorder;
};

#endif // HEROPLANE_H
