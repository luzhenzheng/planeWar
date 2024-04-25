#include "bomb.h"
#include"config.h"
Bomb::Bomb()
{
    //将所有爆照的pixmap放入到数组中
    for(int i=1;i<=BOMB_MAX;i++)
    {
        QString str =QString(BOMB_PATH).arg(i);
        m_pixArr.push_back(QPixmap(str));
    }
    //坐标
    m_X=0;
    m_Y=0;

    m_Free= true;
    //当前播放图片下标
    m_Index=0;
    //播放爆照间隔记录
    m_Recorder=0;
}

void Bomb::updateInfo()
{
    //这个函数用于更新m_Recorder以及m_Index以及m_Free这些成员的信息

    //空闲状态 直接return
    if(m_Free)
    {
        return;
    }
    //增加计数器
    m_Recorder++;
    //如果计数器次数还没到20,那么就直接返回
    if(m_Recorder<BOMB_INTERVAL)
    {
        return;
    }
    else
    {
        //重置计数器
        m_Recorder=0;
        //切换爆炸播放的图片下标
        m_Index++;
        //爆炸播放的图片放完了
        if(m_Index==BOMB_MAX)
        {
            //index置零
            m_Index=0;
            //炸完了 重置free为真
            m_Free=true;
        }
    }
}
