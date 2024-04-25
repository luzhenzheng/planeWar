#ifndef BOMB_H
#define BOMB_H
#include<QPixmap>
#include<QVector>

class Bomb
{
public:
    Bomb();
    void updateInfo();

public :
    QVector<QPixmap> m_pixArr;
    int m_X;
    int m_Y;

    //free == true means it has not exploded
    //free ==false means it has exploded
    bool m_Free;
    //爆炸切图的时间间隔
    //
    int m_Recorder;
    //爆炸时加载的图片下标
    int m_Index;
};

#endif // BOMB_H
