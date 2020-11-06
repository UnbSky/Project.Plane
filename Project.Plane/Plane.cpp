#include "Plane.h"
#include "EnemyBullet.h"
#include <iostream>
#include <windows.h>
#include <tchar.h>
#include <ctime>
#include <random>
#include <iomanip>

#pragma comment(lib,"Msimg32.lib")

using namespace std;

vector<Plane> Plane::Planelist;
vector<Plane>::iterator Plane::iter;
enum Plane::Planes;
extern HDC	g_hdc, g_mdc, g_bufdc;
extern HBITMAP g_hEnemyPlane1, g_hEnemyPlane2, g_hEnemyPlane3, g_hEnemyPlane4, g_hEnemyPlane5, g_hEnemyPlane6,  g_hEnemyPlane12,
g_hEnemyPlane7, g_hEnemyPlane8, g_hEnemyPlane9 , g_hEnemyPlane10, g_hEnemyPlane11, g_hEnemyPlaneBoss1, g_hEnemyPlaneBoss2, g_hSmoke;
extern std::default_random_engine engine;
extern int g_iX, g_iY, g_iXnow, g_iYnow;

Plane::Plane(){}

Plane::Plane(int t,int s, Planes p) {
	issmoke = false;
	blood = 0;
	switch (p) {
	case(ATTACK):
		blood = 5;
		score = 10;
		bmp_x = 120;
		bmp_y = 120;
		break;
	case(ATTACKTWO):
		blood = 8;
		score = 15;
		bmp_x = 120;
		bmp_y = 120;
		break;
	case(ATTACKTHREE):
		blood = 10;
		score = 20;
		bmp_x = 120;
		bmp_y = 120;
		break;
	case(ATTACKFOUR):
		blood = 14;
		score = 24;
		bmp_x = 120;
		bmp_y = 120;
		break;
	case(ATTACKFIVE):
		blood = 16;
		score = 28;
		bmp_x = 120;
		bmp_y = 120;
		break;
	case(SANDAN):
		blood = 14;
		score = 24;
		bmp_x = 120;
		bmp_y = 120;
		break;
	case(SHIP):
		blood = 20;
		score = 30;
		bmp_x = 120;
		bmp_y = 200;
		break;
	case(MISSILENOR):
		blood = 8;
		score = 15;
		bmp_x = 120;
		bmp_y = 120;
		break;
	case(CARGO):
		blood = 10;
		score = 10;
		bmp_x = 120;
		bmp_y = 120;
		break;
	case(CARGOTWO):
		blood = 10;
		score = 20;
		bmp_x = 120;
		bmp_y = 120;
		break;
	case(MISSILETWO):
		blood = 10;
		score = 20;
		bmp_x = 120;
		bmp_y = 120;
		break;
	case(BOSS1):
		blood = 80;
		score = 200;
		bmp_x = 300;
		bmp_y = 150;
		break;
	case(HELI):
		blood = 10;
		score = 10;
		bmp_x = 60;
		bmp_y = 60;
		break;
	}
	fullblood = blood;
	speed = s;
	type = p;
	random_x = 0;
	random_y = 0;
	std::uniform_int_distribution<unsigned int> randomInt(1, 600-bmp_x);
	int r_x = randomInt(engine);
	x = r_x;
	y = -(bmp_y);
	CreateBullet(x+50,y+100,p);//创造对应这种飞机应该存放的子弹
	tPre = GetTickCount();
	cooltime = t; //发射子弹的冷却时间
}
void Plane::Reloadbmp() {//静态方法
	for (iter = Planelist.begin(); iter != Planelist.end(); iter++) {
		switch (iter->type)
		{
		case(ATTACK):
			SelectObject(g_bufdc, g_hEnemyPlane1);
			break;
		case(ATTACKTWO):
			SelectObject(g_bufdc, g_hEnemyPlane2);
			break;
		case(MISSILENOR):
			SelectObject(g_bufdc, g_hEnemyPlane3);
			break;
		case(MISSILETWO):
			SelectObject(g_bufdc, g_hEnemyPlane5);
			break;
		case(ATTACKTHREE):
			SelectObject(g_bufdc, g_hEnemyPlane6);
			break;
		case(ATTACKFOUR):
			SelectObject(g_bufdc, g_hEnemyPlane7);
			break;
		case(ATTACKFIVE):
			SelectObject(g_bufdc, g_hEnemyPlane10);
			break;
		case(SANDAN):
			SelectObject(g_bufdc, g_hEnemyPlane8);
			break;
		case(CARGO):
			SelectObject(g_bufdc, g_hEnemyPlane4);
			break;
		case(CARGOTWO):
			SelectObject(g_bufdc, g_hEnemyPlane9);
			break;
		case(SHIP):
			SelectObject(g_bufdc, g_hEnemyPlane11);
			break;
		case(BOSS1):
			SelectObject(g_bufdc, g_hEnemyPlaneBoss1);
			break;
		case(HELI):
			SelectObject(g_bufdc, g_hEnemyPlane12);
			break;

		}
		TransparentBlt(g_mdc, iter->x, iter->y, iter->bmp_x, iter->bmp_y, g_bufdc, 0, 0, iter->bmp_x, iter->bmp_y, RGB(0, 0, 0));
		iter->tNow = GetTickCount();
		if (iter->tNow - iter->tPre > iter->cooltime) {
			iter->tPre = GetTickCount();
			iter->CreateBullet(iter->x, iter->y,iter->type);
		}
		if (iter->random_y == 0 || (iter->y - iter->random_y < 2 && iter->y - iter->random_y > -2)) {
			std::uniform_int_distribution<unsigned int> randomInt(10, 230 - iter->bmp_y);
			iter->random_y = randomInt(engine);
		}
		else {
			if (iter->y < iter->random_y) {
				iter->y += iter->speed;
			}
			else {
				iter->y -= iter->speed;
			}
		}
		if (iter->random_x == 0 || (iter->x - iter->random_x < 2 && iter->x - iter->random_x > -2)) {
			std::uniform_int_distribution<unsigned int> randomInt(1, 600-iter->bmp_x);
			iter->random_x = randomInt(engine);
		}
		else {
			if (iter->x < iter->random_x) {
				iter->x += iter->speed;
			}
			else {
				iter->x -= iter->speed;
			}
		}
		if (iter->issmoke == true) {
			iter->Smoke(iter->x + iter->bmp_x/2,iter->y + 40);
		}
	}

}
void Plane::Smoke(int x,int y) {
	smokelist.push_back(pair<int, int>(x,y));
	if(smokelist.size()>20){;
	   smokelist.erase(smokelist.begin());
	}
	for (siter = smokelist.begin(); siter != smokelist.end(); siter++) {
		siter->second -= 5;
		SelectObject(g_bufdc, g_hSmoke);
		TransparentBlt(g_mdc, siter->first, siter->second, 10, 10, g_bufdc, 0, 0, 10, 10, RGB(0, 0, 0));
	}
}
void Plane::CreateBullet(int x, int y, Planes p) {
	int x_speed = 0;
	EnemyBullet bullet;
	switch (p) {
	case(ATTACK):
		bullet = EnemyBullet(x+50, y+100, 0,7, EnemyBullet::BULLETS::ENEMYNORMAL);
		EnemyBullet::bulletlist.push_back(bullet);
		break;
	case(ATTACKTWO):
		bullet = EnemyBullet(x + 40, y + 100, 0, 5, EnemyBullet::BULLETS::ENEMYNORMAL);
		EnemyBullet::bulletlist.push_back(bullet);
		bullet = EnemyBullet(x + 60, y + 100, 0, 5, EnemyBullet::BULLETS::ENEMYNORMAL);
		EnemyBullet::bulletlist.push_back(bullet);
		bullet = EnemyBullet(x + 40, y + 100, 0, 8, EnemyBullet::BULLETS::ENEMYNORMAL);
		EnemyBullet::bulletlist.push_back(bullet);
		bullet = EnemyBullet(x + 60, y + 100, 0, 8, EnemyBullet::BULLETS::ENEMYNORMAL);
		EnemyBullet::bulletlist.push_back(bullet);
		break;
	case(MISSILENOR):
		bullet = EnemyBullet(x + 50, y + 100, 0, 0, EnemyBullet::BULLETS::SPEEDMISSILE);
		EnemyBullet::bulletlist.push_back(bullet);
		break;
	case(CARGO):
		break;
	case(BOSS1):
		bullet = EnemyBullet(x + 80, y + 120, 0, 7, EnemyBullet::BULLETS::ENEMYNORMAL);
		EnemyBullet::bulletlist.push_back(bullet);
		bullet = EnemyBullet(x + 230, y + 120, 0, 7, EnemyBullet::BULLETS::ENEMYNORMAL);
		EnemyBullet::bulletlist.push_back(bullet);
		x_speed =  (g_iXnow - x - 120)/120;
		bullet = EnemyBullet(x + 120, y + 120, x_speed, 3, EnemyBullet::BULLETS::ENEMYROUND);
		EnemyBullet::bulletlist.push_back(bullet);
		x_speed = (g_iXnow - x - 160) / 80;
		bullet = EnemyBullet(x + 120, y + 120, x_speed, 6, EnemyBullet::BULLETS::ENEMYROUND);
		EnemyBullet::bulletlist.push_back(bullet);
		x_speed = (g_iXnow - x - 120) / 120;
		bullet = EnemyBullet(x + 160, y + 120, x_speed, 3, EnemyBullet::BULLETS::ENEMYROUND);
		EnemyBullet::bulletlist.push_back(bullet);
		x_speed = (g_iXnow - x - 160) / 80;
		bullet = EnemyBullet(x + 160, y + 120, x_speed, 6, EnemyBullet::BULLETS::ENEMYROUND);
		EnemyBullet::bulletlist.push_back(bullet);
		break;
	case(MISSILETWO):
		bullet = EnemyBullet(x + 50, y + 100, 0, 7, EnemyBullet::BULLETS::DIVIDEMISSILE);
		EnemyBullet::bulletlist.push_back(bullet);
		break;
	case(ATTACKTHREE):
		x_speed = (g_iXnow - x - 50) / 80;
		bullet = EnemyBullet(x + 50, y + 100, x_speed, 4, EnemyBullet::BULLETS::ENEMYROUND);
		EnemyBullet::bulletlist.push_back(bullet);
		break;
	case(ATTACKFOUR):
		x_speed = (g_iXnow - x - 40) / 80;
		bullet = EnemyBullet(x + 40, y + 100, x_speed, 4, EnemyBullet::BULLETS::ENEMYROUND);
		EnemyBullet::bulletlist.push_back(bullet);
		x_speed = (g_iXnow - x - 60) / 80;
		bullet = EnemyBullet(x + 60, y + 100, x_speed, 4, EnemyBullet::BULLETS::ENEMYROUND);
		EnemyBullet::bulletlist.push_back(bullet);
		break;
	case(SANDAN):
		bullet = EnemyBullet(x + 50, y + 100 , 0, 3, EnemyBullet::BULLETS::ENEMYBIG);
		EnemyBullet::bulletlist.push_back(bullet);
		break;
	case(CARGOTWO):
		bullet = EnemyBullet(x + 40, y + 100, 0, 5, EnemyBullet::BULLETS::ENEMYNORMAL);
		EnemyBullet::bulletlist.push_back(bullet);
		bullet = EnemyBullet(x + 60, y + 100, 0, 5, EnemyBullet::BULLETS::ENEMYNORMAL);
		EnemyBullet::bulletlist.push_back(bullet);
		break;
	case(ATTACKFIVE):
		bullet = EnemyBullet(x + 50, y + 100, 0, 3, EnemyBullet::BULLETS::DIVIDEBULLET);
		EnemyBullet::bulletlist.push_back(bullet);
		break;
	case(SHIP):

		break;
	case(HELI):

		break;
	}

}

