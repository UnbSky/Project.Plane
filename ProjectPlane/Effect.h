#pragma once
#include<iostream>
#include<vector>
#include<Windows.h>
using namespace std;

class Effect
{
public:
	static vector<Effect> effectlist;
	static vector<Effect>::iterator iter;
	static enum EFFECTS {DEFEND,SPEEDUP};
	static void LoadEffect();
	Effect(EFFECTS e,int t);
	Effect();
    EFFECTS type;//道具的类型
	DWORD tPre = 0, tNow = 0;//判定效果是否结束
	int time;//效果持续时间
};

