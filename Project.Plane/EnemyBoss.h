#pragma once
class EnemyBoss
{
public:
	EnemyBoss(int lx,int ly,int c,int fb, int bx, int by);
	EnemyBoss();
	virtual void Attack() = 0;//纯虚函数留给基类
	virtual void Move() = 0;
	int Getblood();
protected:
	void Attacked();
	int x, y;//Boss飞机的位置
	int bmp_x, bmp_y;//贴图大小
	int blood, fullblood;//Boss飞机的血量
	bool ready;
};

