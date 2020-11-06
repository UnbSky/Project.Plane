#include "EnemyBullet.h"
#include "Plane.h"
#include "Item.h"
#include <iostream>
#include <windows.h>
#include <tchar.h>
#include <ctime>
#include <random>
#include <iomanip>
#include <stack>


#pragma comment(lib,"Msimg32.lib")

using namespace std;

extern std::default_random_engine engine;
extern bool g_blose,g_bhudun;
extern int g_iXnow, g_iYnow, g_iblood, g_iscore;
extern HDC	g_hdc, g_mdc, g_bufdc;
extern HBITMAP	g_hZidan, g_hZidan2, g_hEnemyZidan1, g_hEnemyMissile1, g_hEnemyZidan2, g_hEnemyMissile2 ,g_hEnemyDazidan
, g_hDazidan, g_hMissile;

vector<EnemyBullet> EnemyBullet::bulletlist;
vector<EnemyBullet>::iterator EnemyBullet::iter;
enum EnemyBullet::BULLETS;

EnemyBullet::EnemyBullet(){}

EnemyBullet::EnemyBullet(int p_x,int p_y,int s_x,int s_y,BULLETS b) { 
	x = p_x;
	y = p_y;
	speed_y = s_y;
	speed_x = s_x;
	type = b;
	tPre = GetTickCount();
	tNow = GetTickCount();
}
void EnemyBullet::ReloadBullet(HWND hwnd) {
	stack<EnemyBullet> addlist;
	EnemyBullet bullet;
	bool needput = false;
	for (iter = EnemyBullet::bulletlist.begin(); iter != EnemyBullet::bulletlist.end();) {
		switch (iter->type) {
		case(EnemyBullet::BULLETS::MYBIG):
			SelectObject(g_bufdc, g_hDazidan);
			TransparentBlt(g_mdc, iter->x, iter->y, 40, 40, g_bufdc, 0, 0, 40, 40, RGB(0, 0, 0));
			iter->y -= iter->speed_y;
			iter->x += iter->speed_x;
			if (iter->y < 200) {
				bullet = EnemyBullet(iter->x, iter->y, 2, 3, EnemyBullet::BULLETS::MYROUND);
				addlist.push(bullet);
				bullet = EnemyBullet(iter->x, iter->y, -2, 3, EnemyBullet::BULLETS::MYROUND);
				addlist.push(bullet);
				bullet = EnemyBullet(iter->x, iter->y, 1, 3, EnemyBullet::BULLETS::MYROUND);
				addlist.push(bullet);
				bullet = EnemyBullet(iter->x, iter->y, -1, 3, EnemyBullet::BULLETS::MYROUND);
				addlist.push(bullet);
				bullet = EnemyBullet(iter->x, iter->y, 2, 2, EnemyBullet::BULLETS::MYROUND);
				addlist.push(bullet);
				bullet = EnemyBullet(iter->x, iter->y, -2, 2, EnemyBullet::BULLETS::MYROUND);
				addlist.push(bullet);
				bullet = EnemyBullet(iter->x, iter->y, 1, 2, EnemyBullet::BULLETS::MYROUND);
				addlist.push(bullet);
				bullet = EnemyBullet(iter->x, iter->y, -1, 2, EnemyBullet::BULLETS::MYROUND);
				addlist.push(bullet);
				bullet = EnemyBullet(iter->x, iter->y, 1, 0, EnemyBullet::BULLETS::MYROUND);
				addlist.push(bullet);
				bullet = EnemyBullet(iter->x, iter->y, 2, 0, EnemyBullet::BULLETS::MYROUND);
				addlist.push(bullet);
				bullet = EnemyBullet(iter->x, iter->y, 3, 0, EnemyBullet::BULLETS::MYROUND);
				addlist.push(bullet);
				bullet = EnemyBullet(iter->x, iter->y, 0, 2, EnemyBullet::BULLETS::MYROUND);
				addlist.push(bullet);
				bullet = EnemyBullet(iter->x, iter->y, -2, 0, EnemyBullet::BULLETS::MYROUND);
				addlist.push(bullet);
				bullet = EnemyBullet(iter->x, iter->y, 1, 1, EnemyBullet::BULLETS::MYROUND);
				addlist.push(bullet);
				bullet = EnemyBullet(iter->x, iter->y, -1, 1, EnemyBullet::BULLETS::MYROUND);
				addlist.push(bullet);
				bullet = EnemyBullet(iter->x, iter->y, 2, 1, EnemyBullet::BULLETS::MYROUND);
				addlist.push(bullet);
				bullet = EnemyBullet(iter->x, iter->y, -2, 1, EnemyBullet::BULLETS::MYROUND);
				addlist.push(bullet);
				bullet = EnemyBullet(iter->x, iter->y, 0, 1, EnemyBullet::BULLETS::MYROUND);
				addlist.push(bullet);
				bullet = EnemyBullet(iter->x, iter->y, -1, 0, EnemyBullet::BULLETS::MYROUND);
				addlist.push(bullet);
				iter = EnemyBullet::bulletlist.erase(iter);
				continue;
			}
			CheckBullet();
			break;
		case(EnemyBullet::BULLETS::MYMISSILE):
			SelectObject(g_bufdc, g_hMissile);
			TransparentBlt(g_mdc, iter->x, iter->y, 20, 40, g_bufdc, 0, 0, 20, 40, RGB(0, 0, 0));
			iter->y -= iter->speed_y;
			iter->x += iter->speed_x;
			CheckBullet();
			break;
		case(EnemyBullet::BULLETS::MYROUND):
			SelectObject(g_bufdc, g_hZidan2);
			TransparentBlt(g_mdc, iter->x, iter->y, 20, 20, g_bufdc, 0, 0, 20, 20, RGB(0, 0, 0));
			iter->y -= iter->speed_y;
			iter->x += iter->speed_x;
			CheckBullet();
			break;
		case(EnemyBullet::BULLETS::MYNORMAL):
			SelectObject(g_bufdc, g_hZidan);
			TransparentBlt(g_mdc, iter->x, iter->y, 20, 20, g_bufdc, 0, 0, 20, 20, RGB(0, 0, 0));
			iter->y -= iter->speed_y;
			iter->x += iter->speed_x;
			CheckBullet();
			break;
		case(EnemyBullet::BULLETS::ENEMYNORMAL):
			SelectObject(g_bufdc, g_hEnemyZidan1);
			TransparentBlt(g_mdc, iter->x, iter->y, 20, 20, g_bufdc, 0, 0, 20, 20, RGB(0, 0, 0));
			iter->y += iter->speed_y;
			if (iter->y > 640) {
				iter = EnemyBullet::bulletlist.erase(iter);
				continue;
			}
			if (iter->x - g_iXnow > 25 && iter->x - g_iXnow < 75 && iter->y - g_iYnow > 25 && iter->y - g_iYnow < 75) {
				if (!g_bhudun) {
					g_iblood -= 1;
				}
				iter = EnemyBullet::bulletlist.erase(iter);
				continue;
			}
			iter++;
			break;
		case(EnemyBullet::BULLETS::SPEEDMISSILE):
			SelectObject(g_bufdc, g_hEnemyMissile1);
			TransparentBlt(g_mdc, iter->x, iter->y, 20, 40, g_bufdc, 0, 0, 20, 40, RGB(0, 0, 0));
			iter->y += iter->speed_y;
			if (iter->speed_y < 10) {
				iter->speed_y += 1;
			}
			if (iter->y > 640) {
				iter = EnemyBullet::bulletlist.erase(iter);
				continue;
			}
			if (iter->x - g_iXnow > 25 && iter->x - g_iXnow < 75 && iter->y - g_iYnow > 25 && iter->y - g_iYnow < 75) {
				if (!g_bhudun) {
					g_iblood -= 1;
				}
				iter = EnemyBullet::bulletlist.erase(iter);
				continue;
			}
			iter++;
			break;
		case(EnemyBullet::BULLETS::ENEMYROUND):
			SelectObject(g_bufdc, g_hEnemyZidan2);
			TransparentBlt(g_mdc, iter->x, iter->y, 20, 20, g_bufdc, 0, 0, 20, 20, RGB(0, 0, 0));
			iter->y += iter->speed_y;
			iter->x += iter->speed_x;
			if (iter->y > 640) {
				iter = EnemyBullet::bulletlist.erase(iter);
				continue;
			}
			if (iter->x - g_iXnow > 25 && iter->x - g_iXnow < 75 && iter->y - g_iYnow > 25 && iter->y - g_iYnow < 75) {
				if (!g_bhudun) {
					g_iblood -= 1;
				}
				iter = EnemyBullet::bulletlist.erase(iter);
				continue;
			}
			iter++;
			break;
		case(EnemyBullet::BULLETS::DIVIDEMISSILE):
			SelectObject(g_bufdc, g_hEnemyMissile2);
			TransparentBlt(g_mdc, iter->x, iter->y, 20, 40, g_bufdc, 0, 0, 20, 20, RGB(0, 0, 0));
			iter->y += iter->speed_y;
			iter->tNow = GetTickCount();
			if (iter->tNow - iter->tPre >= 350) {
				bullet = EnemyBullet(iter->x, iter->y, 2, 4, EnemyBullet::BULLETS::ENEMYROUND);
				addlist.push(bullet);
				bullet = EnemyBullet(iter->x, iter->y, -2, 4, EnemyBullet::BULLETS::ENEMYROUND);
				addlist.push(bullet);
				iter->tPre = GetTickCount();
			}
			if (iter->y > 640) {
				iter = EnemyBullet::bulletlist.erase(iter);
				continue;
			}
			if (iter->x - g_iXnow > 25 && iter->x - g_iXnow < 75 && iter->y - g_iYnow > 25 && iter->y - g_iYnow < 75) {
				if (!g_bhudun) {
					g_iblood -= 1;
				}
				iter = EnemyBullet::bulletlist.erase(iter);
				continue;
			}
			iter++;
			break;
		case(EnemyBullet::BULLETS::ENEMYBIG):
			SelectObject(g_bufdc, g_hEnemyDazidan);
			TransparentBlt(g_mdc, iter->x, iter->y, 40, 40, g_bufdc, 0, 0, 40, 40, RGB(0, 0, 0));
			iter->y += iter->speed_y;
			iter->x += iter->speed_x;
			if (iter->y > 640) {
				iter = EnemyBullet::bulletlist.erase(iter);
				continue;
			}
			if (iter->y > 350) {
				bullet = EnemyBullet(iter->x, iter->y, 2, 2, EnemyBullet::BULLETS::ENEMYROUND);
				addlist.push(bullet);
				bullet = EnemyBullet(iter->x, iter->y, -2, -2, EnemyBullet::BULLETS::ENEMYROUND);
				addlist.push(bullet);
				bullet = EnemyBullet(iter->x, iter->y, -2, 2, EnemyBullet::BULLETS::ENEMYROUND);
				addlist.push(bullet);
				bullet = EnemyBullet(iter->x, iter->y, 2, -2, EnemyBullet::BULLETS::ENEMYROUND);
				addlist.push(bullet);
				iter = EnemyBullet::bulletlist.erase(iter);
				continue;
			}
			if (iter->x - g_iXnow > 25 && iter->x - g_iXnow < 75 && iter->y - g_iYnow > 25 && iter->y - g_iYnow < 75) {
				if (!g_bhudun) {
					g_iblood -= 2;//大子弹伤害为2
				}
				iter = EnemyBullet::bulletlist.erase(iter);
				continue;
			}
			iter++;
			break;
		case(EnemyBullet::BULLETS::DIVIDEBULLET):
			SelectObject(g_bufdc, g_hEnemyZidan2);
			TransparentBlt(g_mdc, iter->x, iter->y, 20, 20, g_bufdc, 0, 0, 20, 20, RGB(0, 0, 0));
			iter->y += iter->speed_y;
			iter->x += iter->speed_x;
			iter->tNow = GetTickCount();
			if (iter->tNow - iter->tPre >= 600) {
				bullet = EnemyBullet(iter->x, iter->y, 2, 3, EnemyBullet::BULLETS::DIVIDEBULLET);
				addlist.push(bullet);
				bullet = EnemyBullet(iter->x, iter->y, -2, 3, EnemyBullet::BULLETS::DIVIDEBULLET);
				addlist.push(bullet);
				iter->tPre = GetTickCount();
				iter = EnemyBullet::bulletlist.erase(iter);
				continue;
				
			}
			if (iter->y > 640) {
				iter = EnemyBullet::bulletlist.erase(iter);
				continue;
			}
			if (iter->x - g_iXnow > 25 && iter->x - g_iXnow < 75 && iter->y - g_iYnow > 25 && iter->y - g_iYnow < 75) {
				if (!g_bhudun) {
					g_iblood -= 1;
				}
				iter = EnemyBullet::bulletlist.erase(iter);
				continue;
			}
			iter++;
			break;
		}

	}
	while (!addlist.empty()) {
		bulletlist.push_back(addlist.top());
		addlist.pop();
	}
}

void EnemyBullet::CheckBullet() {
	bool needremove = false;
	std::uniform_int_distribution<unsigned int> randomInt(1, 7);
	std::uniform_int_distribution<unsigned int> randomInt2(1, 30);
	if (iter->y < -20) {
		iter = EnemyBullet::bulletlist.erase(iter);
		return;
	}
	if (iter->y > 620) {
		iter = EnemyBullet::bulletlist.erase(iter);
		return;
	}
	if (iter->x < -20) {
		iter = EnemyBullet::bulletlist.erase(iter);
		return;
	}
	if (iter->x > 620) {
		iter = EnemyBullet::bulletlist.erase(iter);
		return;
	}
	if (!Plane::Planelist.empty()) {
		for (Plane::iter = Plane::Planelist.begin(); Plane::iter != Plane::Planelist.end();) {
			if ((Plane::iter->x - iter->x > -(Plane::iter->bmp_x - 20) && Plane::iter->x - iter->x < -20) && (Plane::iter->y - iter->y > -(Plane::iter->bmp_y - 20) && Plane::iter->y - iter->y < -20)) {
				Plane::iter->blood -= 1;
				if (Plane::iter->blood <= Plane::iter->fullblood / 2) {
					Plane::iter->issmoke = true;
				}
				if (Plane::iter->blood <= 0) {
					g_iscore += Plane::iter->score;
					if (Plane::iter->type == Plane::Planes::CARGO || Plane::iter->type == Plane::Planes::CARGOTWO) {
						int typ = randomInt(engine);
						Item item;
						switch (typ) {
						case(1):
						case(2):
						case(3):
							item = Item(Item::ITEMS::RECOVER);
							break;
						case(4):
							item = Item(Item::ITEMS::DEFEND);
							break;
						case(5):
							item = Item(Item::ITEMS::SPEED);
							break;
						case(6):
						case(7):
							item = Item(Item::ITEMS::LEVELUP);
							break;
						}
						Item::itemlist.push_back(item);
					}
					if (Plane::iter->type == Plane::Planes::BOSS1) {
						Item item = Item(Item::ITEMS::RECOVER);
						Item::itemlist.push_back(item);
						item = Item(Item::ITEMS::LEVELUP);
						Item::itemlist.push_back(item);
					}
					if (randomInt2(engine) == 1) {
						Item item = Item(Item::ITEMS::MISSILE);
						Item::itemlist.push_back(item);
					}
					else if (randomInt2(engine) == 1) {
						Item item = Item(Item::ITEMS::BIG);
						Item::itemlist.push_back(item);
					}
					//在此处移除飞机
					Plane::iter = Plane::Planelist.erase(Plane::iter);
					continue;
				}
				needremove = true;
			}
			Plane::iter++;
		}
	}
	if (needremove) {
		iter = EnemyBullet::bulletlist.erase(iter);
		return;
	}
	iter++;
}