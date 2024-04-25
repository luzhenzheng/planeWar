#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include"map.h"
#include"heroplane.h"
#include"bullet.h"
#include"enemyplane.h"
#include"bomb.h"

class MainScene : public QWidget
{
    Q_OBJECT

public:
    MainScene(QWidget *parent = 0);
    ~MainScene();
    void initScene();

    //启动游戏
    void playGame();

    //更新所有元素坐标
    void updatePosition();

    //重写鼠标移动事件
    void mouseMoveEvent(QMouseEvent *);


    //(用上面的updatePosition更新完坐标后就)绘制到屏幕中
    void paintEvent(QPaintEvent*);
    //定时器
    QTimer m_timer;
    //地图对象
    Map m_map;
    //飞机对象
    HeroPlane m_hero;
    //子弹对象
    Bullet m_bullets[BULLET_NUM];
    //敌机对象
    EnemyPlane m_enemies[ENEMY_NUM];
    //爆炸数组
    Bomb m_bombs[BOMB_NUM];

    int m_recorder;

    //飞机出场
    void createEnemy();
    //
    void collisonDetection();
};

#endif // WIDGET_H
