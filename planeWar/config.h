#ifndef CONFIG_H
#define CONFIG_H

#define GAME_WIDTH 512
#define GAME_HEIGHT 768
#define GAME_TITLE "飞机大战 v1.0"
#define GAME_ICON ":/Image/app.ico"
#define GAME_RATE 10

#define MAP_PATH ":/Image/img_bg_level_3.jpg"
#define MAP_SCROLL_SPEED 2

#define PLANE_PATH ":/Image/hero2.png"

#define BULLET_PATH ":/Image/bullet_1.png"
#define BULLET_SPEED 5

#define BULLET_NUM 30
//计时器 每次间隔10ms 呼叫shoot函数 有一个计数器m_recorder 如果m_recorder从1累加到BULLET_INTERVAL也就是
//20，才允许发射出去，相当于过去了20x10=200ms
#define BULLET_INTERVAL 20


#define ENEMY_PATH ":/Image/img-plane_6.png"
#define ENEMY_SPEED 5
#define ENEMY_NUM 20
#define ENEMY_INTERVAL 30 //计时器 每次间隔10ms 呼叫产生敌机函数 有一个计数器m_recorder 如果m_recorder从1累加到BULLET_INTERVAL也就是
//30，才允许产生敌机，相当于过去了30x10=300ms

#define BOMB_PATH ":/Image/bomb-%1.png"
#define BOMB_NUM 20
#define BOMB_MAX 7
//计时器 每次间隔10ms都会呼叫爆炸函数 但是有一个计数器 如果计数器从0长进到了20 才允许发生爆炸 相当于间隔了20*10=200ms才允许爆炸
#define BOMB_INTERVAL 20

#endif // CONFIG_H
