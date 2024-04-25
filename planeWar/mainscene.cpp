#include "mainscene.h"
#include"config.h"
#include<QIcon>
#include"map.h"
#include<QPainter>
#include<heroplane.h>
#include <QMouseEvent>
#include<ctime>
#include<bomb.h>
MainScene::MainScene(QWidget *parent)
    : QWidget(parent)
{
    //在窗口的构造函数中
    initScene();
    //启动游戏 就是启动定时器
    playGame();
    //敌机出场的间隔 计数
    this->m_recorder=0;

    //随机数种子
    srand((unsigned int)time(NULL));
}

MainScene::~MainScene()
{

}

void MainScene::initScene()
{
    this->setFixedHeight(GAME_HEIGHT);
    this->setFixedWidth(GAME_WIDTH);
    this->setWindowTitle(GAME_TITLE);
    this->setWindowIcon(QIcon(GAME_ICON));

    //定时器间隔
    this->m_timer.setInterval(GAME_RATE);
}

void MainScene::playGame()
{
    //启动定时器 就是开始游戏了
    this->m_timer.start();

    //监听定时器的timeout事件
    connect(&m_timer,&QTimer::timeout,this,[=](){
        //更新元素的坐标
        updatePosition();

        //敌机出场
        this->createEnemy();
        //绘制到屏幕中
        update();//相当于绘制窗口中所有信息

        collisonDetection();
    });
}

void MainScene::updatePosition()
{
    //这个函数放在connect里，被定时器每隔10ms呼叫一次用来更新主场景的
    //这个函数负责图片来回滚动
    m_map.mapPosition();
    //飞机随着定时器始终发射子弹
    m_hero.shoot();



    //计算所有非空闲子弹的坐标
    for(int i=0;i<BULLET_NUM;i++)
    {
        //如果非空闲 则更新子弹位置
        if(m_hero.m_bullets[i].m_Free==false)
        {
            m_hero.m_bullets[i].updatePosition();
        }
    }
    //计算所有非空闲敌机的位置
    for(int i=0;i<ENEMY_NUM;i++)
    {
        //如果非空闲 则更新子弹位置
        if(this->m_enemies[i].m_Free==false)
        {
            m_enemies[i].updatePosition();
        }
    }
    //更新所有非空闲爆炸的信息
    for(int i=0;i<BOMB_NUM;i++)
    {
        if(this->m_bombs[i].m_Free==false)
        {
            m_bombs[i].updateInfo();
        }
    }
    //    temp_bullet.m_Free=false;
    //    temp_bullet.updatePosition();
}

void MainScene::mouseMoveEvent(QMouseEvent *event)
{
    //每次点击鼠标就会发生这个函数 把鼠标坐标写入飞机对象的位置
    //x y是鼠标点击的位置 他和飞机左上角坐标m_x m_y差了半个飞机宽度高度的平移

    int x=event->x()-0.5*this->m_hero.m_Plane.width();
    int y=event->y()-0.5*this->m_hero.m_Plane.height();

    //边界检测
    if(x<0)
    {
        x=0;
    }

    if(x>GAME_WIDTH-this->m_hero.m_Plane.width())
    {
        x=GAME_WIDTH-this->m_hero.m_Plane.width();
    }

    if(y<0)
    {
        y=0;
    }
    if(y>GAME_HEIGHT-this->m_hero.m_Plane.height())
    {
        y=GAME_HEIGHT-this->m_hero.m_Plane.height();
    }

    this->m_hero.setPosition(x,y);
}

void MainScene::paintEvent(QPaintEvent *)
{
    //这个函数会被connect中的update()每10ms调用
    QPainter painter(this);
    //画地图
    painter.drawPixmap(0,m_map.m_map1_posY,m_map.m_map1);
    painter.drawPixmap(0,m_map.m_map2_posY,m_map.m_map2);

    //画飞机
    painter.drawPixmap(m_hero.m_X,m_hero.m_Y,m_hero.m_Plane);


    //画子弹
    //painter.drawPixmap(temp_bullet.m_X,temp_bullet.m_Y,temp_bullet.m_bullet);
    for(int i=0;i<BULLET_NUM;i++)
    {
        //如果非空闲 则更新子弹位置
        if(m_hero.m_bullets[i].m_Free==false)
        {
            painter.drawPixmap(m_hero.m_bullets[i].m_X,m_hero.m_bullets[i].m_Y,m_hero.m_bullets[i].m_bullet);
        }
    }

    //画敌机
    for(int i=0;i<ENEMY_NUM;i++)
    {
        if(m_enemies[i].m_Free==false)
        {
            painter.drawPixmap(m_enemies[i].m_X,m_enemies[i].m_Y,m_enemies[i].m_enemy);
        }
    }

    //画爆炸
    for(int i=0;i<BOMB_NUM;i++)
    {
        if(this->m_bombs[i].m_Free==false)
        {
            painter.drawPixmap(m_bombs[i].m_X,m_bombs[i].m_Y,
                               m_bombs[i].m_pixArr[m_bombs[i].m_Index]);
        }
    }
}

void MainScene::createEnemy()
{
    //参考shoot

    //shoot函数会被定时器每隔10ms调用 每次被调用 会累加这个m_recorder直到
    //直到m_recorder超过BULLET_INTERVAL了以后才允许被发射
    //累加时间间隔记录变量
    m_recorder++;

    //如果记录的数字，未达到产生敌机时间间隔，直接return，不发射子弹
    if(m_recorder<ENEMY_INTERVAL)
    {
        return;
    }

    //产生敌机时间间隔 置零
    m_recorder=0;
    //产生敌机 遍历所有敌机
    for(int i=0;i<ENEMY_NUM;i++)
    {
        //如果是空闲的敌机，则产生空闲敌机
        if(m_enemies[i].m_Free)
        {
            m_enemies[i].m_Free=false;
            //设置敌机出场的位置
            m_enemies[i].m_X= rand()%(GAME_WIDTH-m_enemies[i].m_enemy.width());
            m_enemies[i].m_Y= -m_enemies[i].m_enemy.height();
            break;
        }
    }

}

void MainScene::collisonDetection()
{
    //遍历所有非空闲的子弹
    for(int i=0;i<BULLET_NUM;i++)
    {
        if(this->m_hero.m_bullets[i].m_Free)
        {
            continue;
        }

        //对于这发非空闲的子弹 遍历所以非空闲的飞机
        for(int i=0;i<ENEMY_NUM;i++)
        {
            if(this->m_enemies[i].m_Free)
            {
                continue;
            }
        }
        //如果子弹和飞机相交，发生碰撞，同时将飞机和子弹的空闲状态设为真
        if(this->m_hero.m_bullets[i].m_Rect.intersects(this->m_enemies[i].m_Rect))
        {
            this->m_enemies[i].m_Free=true;
            this->m_hero.m_bullets[i].m_Free=true;

            //播放爆炸效果
            for(int k=0;k<BOMB_NUM;k++)
            {
                if(m_bombs[k].m_Free)
                {
                    //空闲状态则让它爆炸
                    m_bombs[k].m_Free=false;
                    //更新爆炸坐标
                    m_bombs[k].m_X=m_enemies[i].m_X;
                    m_bombs[k].m_Y=m_enemies[i].m_Y;
                    //只要播放一个爆炸效果就可以了 所以break掉
                    break;
                }
            }
        }
    }
}
