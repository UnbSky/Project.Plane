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
    EFFECTS type;//���ߵ�����
	DWORD tPre = 0, tNow = 0;//�ж�Ч���Ƿ����
	int time;//Ч������ʱ��
};

