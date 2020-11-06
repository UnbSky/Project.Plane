#pragma once
#include<iostream>
#include<vector>
#include<Windows.h>
using namespace std;
class Text
{
public:
	static vector<Text> textlist;
	static vector<Text>::iterator iter;
	static enum TEXTS {WARNING};
	static void ReloadText();
	Text(TEXTS t);
private:
	TEXTS type;//贴字的种类
	int x, y;//贴字的位置
	int blink;//闪烁次数
	int time;//持续时间

};
