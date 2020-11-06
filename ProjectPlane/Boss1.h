#pragma once
#include "EnemyBoss.h"
using namespace std;
class Boss1 :
    public EnemyBoss
{
public:
    Boss1(int lx,int ly,int b,int fb,int bx,int by):EnemyBoss(lx,ly,b,fb,bx,by){}//继承构造函数
    Boss1():EnemyBoss(){}
    void Attack();
    void Move();
private:
    int ic1 = 0,ic2 = 0;//一个ic 是 5
    int xspeed = 5;//子弹特殊属性
    int missilex = 50; //发射导弹的位置
};

