#include "enemyplane.h"
#include"config.h"
EnemyPlane::EnemyPlane()
{
    this->m_enemy.load(ENEMY_PATH);

    this->m_X=GAME_WIDTH;
    this->m_Y=0;

    this->m_Free=true;

    this->m_Speed=ENEMY_SPEED;

    this->m_Rect.setWidth(this->m_enemy.width());
    this->m_Rect.setHeight(this->m_enemy.height());
    this->m_Rect.moveTo(this->m_X,this->m_Y);

}

void EnemyPlane::updatePosition()
{
    //空闲状态指的是在弹匣内的 射出去的是非空闲
    if(this->m_Free==true)
    {
        return;
    }
    else
    {
        this->m_Y+=ENEMY_SPEED;
        this->m_Rect.moveTo(this->m_X,this->m_Y);

        //如果敌机从屏幕下端飞出屏幕 那么重置为free
        if(this->m_Y>GAME_HEIGHT+m_Rect.height())
        {
            this->m_Free=true;
        }
    }
}
