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
	TEXTS type;//���ֵ�����
	int x, y;//���ֵ�λ��
	int blink;//��˸����
	int time;//����ʱ��

};
