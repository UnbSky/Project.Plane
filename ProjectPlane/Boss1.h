#pragma once
#include "EnemyBoss.h"
using namespace std;
class Boss1 :
    public EnemyBoss
{
public:
    Boss1(int lx,int ly,int b,int fb,int bx,int by):EnemyBoss(lx,ly,b,fb,bx,by){}//�̳й��캯��
    Boss1():EnemyBoss(){}
    void Attack();
    void Move();
private:
    int ic1 = 0,ic2 = 0;//һ��ic �� 5
    int xspeed = 5;//�ӵ���������
    int missilex = 50; //���䵼����λ��
};

