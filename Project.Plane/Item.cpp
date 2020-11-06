#include "Item.h"
#include "Effect.h"
#include <iostream>
#include <windows.h>
#include <tchar.h>
#include <ctime>
#include <random>
#include <iomanip>

vector<Item> Item::itemlist;
vector<Item>::iterator Item::iter;
enum Item::ITEMS;

extern int g_ilevel;
extern std::default_random_engine engine;
extern int g_iXnow, g_iYnow, g_iblood, g_iscore, g_iQweapon, g_iEweapon;
extern HDC	g_hdc, g_mdc, g_bufdc;
extern HBITMAP	g_hItem1, g_hItem2, g_hItem3, g_hItem4  ,g_hItem5, g_hItem6;

Item::Item() {}
Item::Item(ITEMS t) {
	type = t;
	std::uniform_int_distribution<unsigned int> randomInt(30, 520);
	x = randomInt(engine);
	std::uniform_int_distribution<unsigned int> randomInt2(200, 400);
	y = randomInt2(engine);
}
void Item::ReloadItem() {
	Effect e;
	for (iter = itemlist.begin(); iter != itemlist.end();) {
		switch (iter->type) {
		case(RECOVER):
			SelectObject(g_bufdc, g_hItem1);
			break;
		case(DEFEND):
			SelectObject(g_bufdc, g_hItem2);
			break;
		case(SPEED):
			SelectObject(g_bufdc, g_hItem3);
			break;
		case(LEVELUP):
			SelectObject(g_bufdc, g_hItem4);
			break;	
		case(MISSILE):
			SelectObject(g_bufdc, g_hItem5);
			break;
		case(BIG):
			SelectObject(g_bufdc, g_hItem6);
			break;
		}
		TransparentBlt(g_mdc, iter->x, iter->y, 50, 50, g_bufdc, 0, 0, 50, 50, RGB(0, 0, 0));
		if (iter->x > g_iXnow && iter->y > g_iYnow && iter->x + 50 < g_iXnow + 100 && iter->y + 50 < g_iYnow + 100) {
			switch (iter->type) {
			case(RECOVER):
				g_iblood += 2;
				if (g_iblood >= 8) {
					g_iblood = 8;
				}
				break;
			case(LEVELUP):
				g_ilevel++;
				break;
			case(DEFEND):
				e = Effect(Effect::EFFECTS::DEFEND,5000);
				Effect::effectlist.push_back(e);
				break;
			case(SPEED):
				e = Effect(Effect::EFFECTS::SPEEDUP,5000);
				Effect::effectlist.push_back(e);
				break;
			case(MISSILE):
				g_iQweapon++;
				if (g_iQweapon == 4) {
					g_iQweapon = 3;
				}
				break;
			case(BIG):
				g_iEweapon++;
				if (g_iEweapon == 4) {
					g_iEweapon = 3;
				}
				break;
			}
			iter = itemlist.erase(iter);
			continue;
		}
		iter++;
	}
}
