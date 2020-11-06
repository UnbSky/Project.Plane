#pragma once
#include<iostream>
#include<vector>
#include<Windows.h>
using namespace std;

class Plane
{
public:
	static void Reloadbmp();
	static vector<Plane> Planelist;
	static vector<Plane>::iterator iter;
	static enum Planes { ATTACK, CARGO, ATTACKTWO, MISSILENOR, MISSILETWO, BOSS1, ATTACKTHREE, ATTACKFOUR, SANDAN, CARGOTWO, ATTACKFIVE,SHIP,HELI};
	Plane(int t, int s, Planes p);
	Plane();
	bool issmoke;//是否冒烟
	virtual void CreateBullet(int x,int y,Planes p);
	int x, y; //存放飞机的坐标(直接调用数据)
	DWORD tPre = 0, tNow = 0;
	int cooltime;//发射子弹冷却时间
	int blood, fullblood;//这是敌方该飞机的血量
	int score; //击落的得分
	int bmp_x, bmp_y;//位图的大小
	Planes type;
private:
	int random_x,random_y;
	int speed;
	vector<pair<int, int>> smokelist;
	vector<pair<int, int>>::iterator siter;
	void Smoke(int x, int y);
};

