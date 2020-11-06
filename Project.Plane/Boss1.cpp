#include "Boss1.h"
#include "EnemyBullet.h"
#include <iostream>
#include <windows.h>
#include <tchar.h>
#include <iomanip>

extern HDC	g_hdc, g_mdc, g_bufdc;
extern HBITMAP g_hEnemyPlaneBoss2;
extern int g_iX, g_iY, g_iXnow, g_iYnow;

void Boss1::Attack() {//¼Ì³ÐÐéº¯Êý
	Attacked();//±»¹¥»÷ÅÐ¶¨
	EnemyBullet bullet;
	if (ready) {
		if (blood > fullblood * 3 / 4 && blood <= fullblood) { // >75%
			ic1++;
			ic2++;
			if (ic1 > 120) {
				ic1 = 0;
				bullet = EnemyBullet(x, y + 100, 0, 7, EnemyBullet::BULLETS::DIVIDEMISSILE);
				EnemyBullet::bulletlist.push_back(bullet);
				bullet = EnemyBullet(x + 100, y + 100, 0, 7, EnemyBullet::BULLETS::DIVIDEMISSILE);
				EnemyBullet::bulletlist.push_back(bullet);
				bullet = EnemyBullet(x + 200, y + 100, 0, 7, EnemyBullet::BULLETS::DIVIDEMISSILE);
				EnemyBullet::bulletlist.push_back(bullet);
			}
			if (ic2 > 30) {
				ic2 = 0;
				bullet = EnemyBullet(x + 100, y + 100, xspeed , 2, EnemyBullet::BULLETS::ENEMYROUND);
				EnemyBullet::bulletlist.push_back(bullet);
				bullet = EnemyBullet(x + 100, y + 100, -(xspeed), 2, EnemyBullet::BULLETS::ENEMYROUND);
				EnemyBullet::bulletlist.push_back(bullet);
				xspeed -= 1;
				if (xspeed == 0) {
					xspeed = 5;
				}
			}
		}
		else if (blood > fullblood * 2 / 4 && blood <= fullblood * 3 / 4) { //75% - 50%
			ic2++;
			ic1++;
			if (ic2 > 10) {
				ic2 = 0;
				bullet = EnemyBullet(x + 150, y + 100, xspeed, 2, EnemyBullet::BULLETS::ENEMYROUND);
				EnemyBullet::bulletlist.push_back(bullet);
				bullet = EnemyBullet(x + 50, y + 100, -(xspeed), 2, EnemyBullet::BULLETS::ENEMYROUND);
				EnemyBullet::bulletlist.push_back(bullet);
				xspeed -= 1;
				if (xspeed == -6) {
					xspeed = 5;
				}
			}
			if (ic1 > 50) {
				ic1 = 0;
				int x_speed;				
				x_speed = (g_iXnow - x - 100) / 100;
				bullet = EnemyBullet(x + 100, y + 100, x_speed, 4, EnemyBullet::BULLETS::ENEMYROUND);
				EnemyBullet::bulletlist.push_back(bullet);
			}
		}
		else if (blood > fullblood * 1 / 4 && blood <= fullblood * 2 / 4) { //50% - 25%
			ic2++;
			ic1++;
			if (ic2 > 10) {
				ic2 = 0;
				bullet = EnemyBullet(x + 150, y + 100, xspeed, 2, EnemyBullet::BULLETS::ENEMYROUND);
				EnemyBullet::bulletlist.push_back(bullet);
				bullet = EnemyBullet(x + 50, y + 100, -(xspeed), 2, EnemyBullet::BULLETS::ENEMYROUND);
				EnemyBullet::bulletlist.push_back(bullet);
				xspeed -= 1;
				if (xspeed == -6) {
					xspeed = 5;
				}
			}
			if (ic1 > 80) {
				ic1 = 0;
				int x_speed;
				x_speed = (g_iXnow - x - 100) / 100;
				bullet = EnemyBullet(x + 100, y + 100, x_speed, 4, EnemyBullet::BULLETS::ENEMYBIG);
				EnemyBullet::bulletlist.push_back(bullet);
				x_speed = (g_iXnow - x - 100) / 60;
				bullet = EnemyBullet(x + 100, y + 100, x_speed, 2, EnemyBullet::BULLETS::ENEMYROUND);
				EnemyBullet::bulletlist.push_back(bullet);
			}
		}
		else if (blood > 0 && blood <= fullblood * 1 / 4) { // <25%
			ic2++;
			ic1++;
			if (ic2 > 10) {
				ic2 = 0;
				bullet = EnemyBullet(x + 150, y + 100, xspeed, 2, EnemyBullet::BULLETS::ENEMYROUND);
				EnemyBullet::bulletlist.push_back(bullet);
				bullet = EnemyBullet(x + 50, y + 100, -(xspeed), 2, EnemyBullet::BULLETS::ENEMYROUND);
				EnemyBullet::bulletlist.push_back(bullet);
				bullet = EnemyBullet(x + 100, y + 100, 0, 4, EnemyBullet::BULLETS::ENEMYROUND);
				EnemyBullet::bulletlist.push_back(bullet);
				xspeed -= 1;
				if (xspeed == -6) {
					xspeed = 5;
				}
			}
			if (ic1 > 50) {
				ic1 = 0;
				bullet = EnemyBullet(missilex, y + 100, 0, 0, EnemyBullet::BULLETS::SPEEDMISSILE);
				EnemyBullet::bulletlist.push_back(bullet);
				missilex += 50;
				if (missilex == 600) {
					missilex = 50;
				}
			}
		}
	}
}
void Boss1::Move() {
	SelectObject(g_bufdc, g_hEnemyPlaneBoss2);
	TransparentBlt(g_mdc, x, y, bmp_x, bmp_y, g_bufdc, 0, 0, bmp_x, bmp_y, RGB(0, 0, 0));
	if (y < 50) {
		y += 1;
	}
	else {
		ready = true;
	}
}