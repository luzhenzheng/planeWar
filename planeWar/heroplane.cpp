#include "heroplane.h"
#include"config.h"
HeroPlane::HeroPlane()
{
    //加载飞机图片
    this->m_Plane.load(PLANE_PATH);

    //初始化飞机位置
    this->m_X= 0.5*GAME_WIDTH-0.5*this->m_Plane.width();
    this->m_Y= GAME_HEIGHT-this->m_Plane.height();

    //初始化矩形边框
    this->m_Rect.setHeight(this->m_Plane.height());
    this->m_Rect.setWidth(this->m_Plane.width());

    this->m_Rect.moveTo(this->m_X,this->m_Y);

    this->m_recorder=0;
}

void HeroPlane::shoot()
{
    //shoot函数会被定时器每隔10ms调用 每次被调用 会累加这个m_recorder直到
    //直到m_recorder超过BULLET_INTERVAL了以后才允许被发射
    //累加时间间隔记录变量
    m_recorder++;

    //如果记录的数字，未达到发射子弹时间间隔，直接return，不发射子弹
    if(m_recorder<BULLET_INTERVAL)
    {
        return;
    }

    //达到发射时间
    m_recorder=0;
    //发射子弹 遍历所有子弹
    for(int i=0;i<BULLET_NUM;i++)
    {
        //如果是空闲的子弹，进行发射
        if(m_bullets[i].m_Free)
        {
            m_bullets[i].m_Free=false;
            //设置子弹从机身上离开的初始位置
            m_bullets[i].m_X= m_X+0.4*this->m_Plane.width();
            m_bullets[i].m_Y=m_Y-25;
            break;
        }
    }
}

void HeroPlane::setPosition(int x,int y)
{
    this->m_X=x;
    this->m_Y=y;
    this->m_Rect.moveTo(x,y);
}
