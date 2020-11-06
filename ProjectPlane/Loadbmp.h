#pragma once
#include <windows.h>
#include <tchar.h>

HBITMAP		g_hPlane = NULL, g_hZidan = NULL, g_hEnemyZidan1 = NULL, g_hEnemyPlane1 = NULL;
HBITMAP		g_hPlaneinfo = NULL, g_hEnemyPlane2 = NULL, g_hEnemyPlane3 = NULL, g_hEnemyPlane4 = NULL, g_hEnemyMissile1 = NULL;
HBITMAP		g_hBack1 = NULL, g_hBack2 = NULL, g_hBack3 = NULL, g_hSmoke = NULL;
HBITMAP		g_hStart1 = NULL, g_hStart2 = NULL, g_hStart3 = NULL, g_hStartback = NULL;
HBITMAP		g_hblood[9];

void Loadbmps() {
	g_hStart1 = (HBITMAP)LoadImage(NULL, L"GameMedia\\background\\start1.bmp", IMAGE_BITMAP, 200, 75, LR_LOADFROMFILE);
	g_hStart2 = (HBITMAP)LoadImage(NULL, L"GameMedia\\background\\start2.bmp", IMAGE_BITMAP, 200, 75, LR_LOADFROMFILE);
	g_hStart3 = (HBITMAP)LoadImage(NULL, L"GameMedia\\background\\start3.bmp", IMAGE_BITMAP, 200, 75, LR_LOADFROMFILE);
	g_hStartback = (HBITMAP)LoadImage(NULL, L"GameMedia\\background\\startback.bmp", IMAGE_BITMAP, 600, 600, LR_LOADFROMFILE);
	g_hSmoke = (HBITMAP)LoadImage(NULL, L"GameMedia\\smoke.bmp", IMAGE_BITMAP, 10, 10, LR_LOADFROMFILE);
	g_hPlane = (HBITMAP)LoadImage(NULL, L"GameMedia\\plane.bmp", IMAGE_BITMAP, 100, 100, LR_LOADFROMFILE);
	g_hZidan = (HBITMAP)LoadImage(NULL, L"GameMedia\\zidan.bmp", IMAGE_BITMAP, 20, 20, LR_LOADFROMFILE);
	g_hEnemyPlane1 = (HBITMAP)LoadImage(NULL, L"GameMedia\\enemy\\enemyattack1.bmp", IMAGE_BITMAP, 120, 120, LR_LOADFROMFILE);
	g_hEnemyPlane2 = (HBITMAP)LoadImage(NULL, L"GameMedia\\enemy\\enemyattack2.bmp", IMAGE_BITMAP, 120, 120, LR_LOADFROMFILE);
	g_hEnemyPlane3 = (HBITMAP)LoadImage(NULL, L"GameMedia\\enemy\\enemymissileplane1.bmp", IMAGE_BITMAP, 120, 120, LR_LOADFROMFILE);
	g_hEnemyPlane4 = (HBITMAP)LoadImage(NULL, L"GameMedia\\enemy\\enemycargo1.bmp", IMAGE_BITMAP, 120, 120, LR_LOADFROMFILE);
	g_hEnemyZidan1 = (HBITMAP)LoadImage(NULL, L"GameMedia\\enemy\\enemyzidan1.bmp", IMAGE_BITMAP, 20, 20, LR_LOADFROMFILE);
	g_hEnemyMissile1 = (HBITMAP)LoadImage(NULL, L"GameMedia\\enemy\\enemymissile1.bmp", IMAGE_BITMAP, 20, 40, LR_LOADFROMFILE);
	g_hBack1 = (HBITMAP)LoadImage(NULL, L"GameMedia\\background\\background_layer1.bmp", IMAGE_BITMAP, WINDOW_WIDTH, WINDOW_HEIGHT, LR_LOADFROMFILE);
	g_hBack2 = (HBITMAP)LoadImage(NULL, L"GameMedia\\background\\background_layer2.bmp", IMAGE_BITMAP, WINDOW_WIDTH, WINDOW_HEIGHT, LR_LOADFROMFILE);
	g_hBack3 = (HBITMAP)LoadImage(NULL, L"GameMedia\\background\\background_layer3.bmp", IMAGE_BITMAP, WINDOW_WIDTH, WINDOW_HEIGHT, LR_LOADFROMFILE);
	g_hPlaneinfo = (HBITMAP)LoadImage(NULL, L"GameMedia\\planeinfo\\planeinfo.bmp", IMAGE_BITMAP, 500, 100, LR_LOADFROMFILE);
	g_hblood[0] = (HBITMAP)LoadImage(NULL, L"GameMedia\\planeinfo\\blood0.bmp", IMAGE_BITMAP, 500, 100, LR_LOADFROMFILE);
	g_hblood[1] = (HBITMAP)LoadImage(NULL, L"GameMedia\\planeinfo\\blood1.bmp", IMAGE_BITMAP, 500, 100, LR_LOADFROMFILE);
	g_hblood[2] = (HBITMAP)LoadImage(NULL, L"GameMedia\\planeinfo\\blood2.bmp", IMAGE_BITMAP, 500, 100, LR_LOADFROMFILE);
	g_hblood[3] = (HBITMAP)LoadImage(NULL, L"GameMedia\\planeinfo\\blood3.bmp", IMAGE_BITMAP, 500, 100, LR_LOADFROMFILE);
	g_hblood[4] = (HBITMAP)LoadImage(NULL, L"GameMedia\\planeinfo\\blood4.bmp", IMAGE_BITMAP, 500, 100, LR_LOADFROMFILE);
	g_hblood[5] = (HBITMAP)LoadImage(NULL, L"GameMedia\\planeinfo\\blood5.bmp", IMAGE_BITMAP, 500, 100, LR_LOADFROMFILE);
	g_hblood[6] = (HBITMAP)LoadImage(NULL, L"GameMedia\\planeinfo\\blood6.bmp", IMAGE_BITMAP, 500, 100, LR_LOADFROMFILE);
	g_hblood[7] = (HBITMAP)LoadImage(NULL, L"GameMedia\\planeinfo\\blood7.bmp", IMAGE_BITMAP, 500, 100, LR_LOADFROMFILE);
	g_hblood[8] = (HBITMAP)LoadImage(NULL, L"GameMedia\\planeinfo\\blood8.bmp", IMAGE_BITMAP, 500, 100, LR_LOADFROMFILE);
}
