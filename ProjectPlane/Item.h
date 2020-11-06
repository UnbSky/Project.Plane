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
	int x, y; //道具的位置
	ITEMS type;//道具的类型
};

