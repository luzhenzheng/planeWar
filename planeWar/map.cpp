#include "map.h"
#include"config.h"
#

Map::Map()
{
    //初始化地图对象
    this->m_map1.load(MAP_PATH);
    this->m_map2.load(MAP_PATH);

    //初始化两张地图Y轴的坐标
    this->m_map1_posY=-GAME_HEIGHT;
    this->m_map2_posY=0;

    //地图滚动速度
    this->m_scroll_speed = MAP_SCROLL_SPEED;

}

void Map::mapPosition()
{
    //开一个定时器 始终刷新这个函数 用于更新地图位置
    this->m_map1_posY+=MAP_SCROLL_SPEED;
    this->m_map2_posY+=MAP_SCROLL_SPEED;
    if(this->m_map1_posY>0)
    {
        //重置到初始位置
        this->m_map1_posY=-GAME_HEIGHT;
    }

    if(this->m_map2_posY>GAME_HEIGHT)
    {
        //重置到初始位置
        this->m_map2_posY=0;
    }
}
