#include "bullet.h"
#include"config.h"
Bullet::Bullet()
{
    //构造函数就是初始化这个类中的所有属性

    //子弹加载图片
    this->m_bullet.load(BULLET_PATH);

    //子弹坐标
    this->m_X = GAME_WIDTH*0.5-0.5*this->m_bullet.width();
    this->m_Y = GAME_HEIGHT;

    //子弹状态
    this->m_Free =true;

    //子弹速度
    this->m_Speed = BULLET_SPEED;

    //子弹边框 碰撞检测

    this->m_Rect.setWidth(this->m_bullet.width());
    this->m_Rect.setHeight(this->m_bullet.height());
    this->m_Rect.moveTo(this->m_X,this->m_Y);

}

void Bullet::updatePosition()
{
    //空闲状态指的是在弹匣内的 射出去的是非空闲
    if(this->m_Free==true)
    {
        return;
    }
    else
    {
        this->m_Y-=BULLET_SPEED;
        this->m_Rect.moveTo(this->m_X,this->m_Y);

        if(this->m_Y<-m_Rect.height())
        {
            this->m_Free=true;
        }
    }

}
