#pragma once
class EnemyBoss
{
public:
	EnemyBoss(int lx,int ly,int c,int fb, int bx, int by);
	EnemyBoss();
	virtual void Attack() = 0;//���麯����������
	virtual void Move() = 0;
	int Getblood();
protected:
	void Attacked();
	int x, y;//Boss�ɻ���λ��
	int bmp_x, bmp_y;//��ͼ��С
	int blood, fullblood;//Boss�ɻ���Ѫ��
	bool ready;
};

