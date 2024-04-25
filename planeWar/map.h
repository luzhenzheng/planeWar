#ifndef MAP_H
#define MAP_H
#include<QPixmap>
#include<QTimer>
class Map
{
public:
    void mapPosition();
    Map();
    //就是两张图罢了
    QPixmap m_map1;
    QPixmap m_map2;
    int m_map1_posY;
    int m_map2_posY;
    //地图滚动速度
    int m_scroll_speed;


};

#endif // MAP_H
