#pragma once
#include<iostream>
#include<vector>
#include<Windows.h>
using namespace std;

class Item
{
public:
	static vector<Item> itemlist;
	static vector<Item>::iterator iter;
	static enum ITEMS {RECOVER,DEFEND,SPEED,LEVELUP,MISSILE,BIG};
	static void ReloadItem();
	Item(ITEMS t);
	Item();
	int x, y; //���ߵ�λ��
	ITEMS type;//���ߵ�����
};

