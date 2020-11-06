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
	bool issmoke;//�Ƿ�ð��
	virtual void CreateBullet(int x,int y,Planes p);
	int x, y; //��ŷɻ�������(ֱ�ӵ�������)
	DWORD tPre = 0, tNow = 0;
	int cooltime;//�����ӵ���ȴʱ��
	int blood, fullblood;//���ǵз��÷ɻ���Ѫ��
	int score; //����ĵ÷�
	int bmp_x, bmp_y;//λͼ�Ĵ�С
	Planes type;
private:
	int random_x,random_y;
	int speed;
	vector<pair<int, int>> smokelist;
	vector<pair<int, int>>::iterator siter;
	void Smoke(int x, int y);
};

