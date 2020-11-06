#include "EnemyBoss.h"
#include "EnemyBullet.h"

EnemyBoss::EnemyBoss(int lx, int ly, int b, int fb,int bx,int by) {
	x = lx;
	y = ly;
	blood = b;
	fullblood = fb;
	bmp_x = bx;
	bmp_y = by;
	ready = false;
}
EnemyBoss::EnemyBoss() {

}

int EnemyBoss::Getblood() {
	return blood;
}

void EnemyBoss::Attacked() {
	if (ready){
		for (EnemyBullet::iter = EnemyBullet::bulletlist.begin(); EnemyBullet::iter != EnemyBullet::bulletlist.end();){
			if (EnemyBullet::iter->type == EnemyBullet::BULLETS::MYNORMAL || EnemyBullet::iter->type == EnemyBullet::BULLETS::MYROUND){
				if ((x - EnemyBullet::iter->x > -(bmp_x - 20) && x - EnemyBullet::iter->x < -20) && (y - EnemyBullet::iter->y > -(bmp_y - 20) && y - EnemyBullet::iter->y < -20)) {
					blood -= 1;	
					EnemyBullet::iter = EnemyBullet::bulletlist.erase(EnemyBullet::iter);
					continue;
				}								
			}
			EnemyBullet::iter++;
		}
	}
}
