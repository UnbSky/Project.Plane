#pragma once
#include<iostream>
#include<vector>
#include<Windows.h>
using namespace std;

class EnemyBullet
{
public:
	int time;//��ȴʱ��
	static vector<EnemyBullet> bulletlist;
	static vector<EnemyBullet>::iterator iter;
	static enum BULLETS { MYNORMAL, ENEMYNORMAL, SPEEDMISSILE, ENEMYROUND, DIVIDEMISSILE,MYROUND,ENEMYBIG,MYBIG,MYMISSILE,DIVIDEBULLET};
	EnemyBullet();
	EnemyBullet(int p_x, int p_y, int s_x, int s_y, BULLETS b);
	static void ReloadBullet(HWND hwnd);
	static void CheckBullet();
	int x, y; //�ӵ���λ��
	BULLETS type;
	int speed_x,speed_y;
	DWORD tPre = 0, tNow = 0;//�����ӵ��������ж�
private:


};

