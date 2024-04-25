#ifndef BULLET_H
#define BULLET_H
#include<QPixmap>

class Bullet
{
public:
    Bullet();

    void updatePosition();

    QPixmap m_bullet;

    int m_X;
    int m_Y;

    int m_Speed;

    bool m_Free;

    //用于碰撞检测
    QRect m_Rect;
};

#endif // BULLET_H
