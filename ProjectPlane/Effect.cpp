#include "Effect.h"
#include <iostream>
#include <windows.h>
#include <tchar.h>
#include <ctime>
#include <random>
#include <iomanip>

vector<Effect> Effect::effectlist;
vector<Effect>::iterator Effect::iter;
enum Effect::EFFECTS;

extern int g_ispeed;
extern bool g_bhudun;

Effect::Effect(){}
Effect::Effect(EFFECTS e, int t) {
	type = e;
	time = t;
	tPre = GetTickCount();
	tNow = GetTickCount();
}

void Effect::LoadEffect() {
	for (iter = effectlist.begin(); iter != effectlist.end();) {
		iter->tNow = GetTickCount();
		if (iter->tNow - iter->tPre > iter->time) {
			iter = effectlist.erase(iter);
			continue;
		}
		switch (iter->type) {
		case(SPEEDUP):
			g_ispeed = 15;
			break;
		case(DEFEND):
			g_bhudun = true;
			break;
		}
		iter++;
	}
}