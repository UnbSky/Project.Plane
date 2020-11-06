#include <windows.h>
#include <tchar.h>
#include <ctime>
#include <random>
#include <iomanip>
#include <list>

//再也不用这种垃圾模型写代码了awa

#include"Effect.h"
#include"Plane.h"
#include"EnemyBullet.h"
#include"Item.h"
#include"Boss1.h"
#include"EnemyBoss.h"

#pragma comment(lib,"winmm.lib")		//调用PlaySound函数所需库文件
#pragma comment(lib,"Msimg32.lib")		//添加使用TransparentBlt函数所需的库文件

#define WINDOW_WIDTH	600							
#define WINDOW_HEIGHT	600							
#define WINDOW_TITLE	L"长空之上b1.0"	

DWORD		g_tPre = 0, g_tNow = 0;	  //g_tPre(2)记录上一次绘图的时间，g_tNow记录此次准备绘图的时间,g_Create记录生成飞机时间
HBITMAP		g_hPlane = NULL, g_hPlanehudun = NULL;
HBITMAP	    g_hZidan = NULL, g_hZidan2 = NULL, g_hDazidan = NULL ,g_hMissile = NULL,g_hEnemyZidan1 = NULL, g_hEnemyZidan2 = NULL,g_hEnemyDazidan = NULL,g_hEnemyMissile1 = NULL,
g_hEnemyMissile2 = NULL;
HBITMAP		g_hPlaneinfo = NULL, g_hEnemyPlane1 = NULL, g_hEnemyPlane2 = NULL, g_hEnemyPlane3 = NULL , g_hEnemyPlane4 = NULL,
g_hEnemyPlane5 = NULL, g_hEnemyPlane6 = NULL, g_hEnemyPlane7 = NULL, g_hEnemyPlane8 = NULL, g_hEnemyPlane9 = NULL, g_hEnemyPlane10 = NULL, g_hEnemyPlane11 = NULL,
g_hEnemyPlane12 = NULL, g_hEnemyPlaneBoss1 = NULL, g_hEnemyPlaneBoss2 = NULL;
HBITMAP		g_hBack1 = NULL, g_hBack2 = NULL, g_hBack3 = NULL, g_hSmoke=NULL;
HBITMAP		g_hStart1 = NULL, g_hStart2 = NULL, g_hStart3 = NULL, g_hStartback = NULL, g_hBlue = NULL, g_hInfoBack = NULL;
HBITMAP		g_hPause1 = NULL, g_hPause2 = NULL, g_hPauseback = NULL;
HBITMAP		g_hEnd1 = NULL, g_hEnd2 = NULL, g_hEndback = NULL;
HBITMAP		g_hItem1 = NULL, g_hItem2 = NULL, g_hItem3 = NULL, g_hItem4 = NULL, g_hItem5 = NULL, g_hItem6 = NULL;
HBITMAP		g_hblood[9];
HBITMAP		g_hQ[4];
HBITMAP		g_hE[4];
HDC			g_hdc = NULL, g_mdc = NULL, g_bufdc = NULL;      //全局设备环境句柄与全局内存DC句柄
int			g_iX = 0, g_iY = 0, g_iXnow = 0, g_iYnow = 0;    //g_iX,g_iY代表鼠标光标所在位置，g_iXnow，g_iYnow代表当前飞机坐标，也就是贴图的位置
int			g_iBGOffset = 0, g_iBGOffset2 = 0, g_iBGOffset3 = 0;;       //g_iBGOffset为滚动背景所要裁剪的区域宽度
int			g_icounter = 0,g_icounter2 = 0, g_ibc1 = 0;
int			g_iblood = 6;//玩家剩余的血量(1-8)
int			g_iscore = 0;//玩家得分
int			g_igame = 0;//游戏目前情况 0:未开始 1:开始 2:暂停 3:结束 4:介绍界面
int			g_ilevel = 1;//玩家武器等级
int			g_ispeed = 10;//玩家飞机速度
int			g_imove = 3;//玩家子弹移动参数
int			g_iQweapon = 1, g_iEweapon = 1; //Q与E绑定的武器
bool		g_blose = false;//判定是否输
bool		g_bhudun = false;//判定是否为护盾状态
bool		g_isboss = false;//判定是否已经生成了boss
bool		g_isq = false, g_ise = false;
Boss1		boss1;

std::default_random_engine engine(static_cast<unsigned int>(time(0))); //随机数引擎

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
BOOL	Start_Init(HWND hwnd);
BOOL	Game_Init(HWND hwnd);	
BOOL	Back_Init(HWND hwnd);
VOID    Start_Paint(HWND hwnd);
VOID	Info_Paint(HWND hwnd);
VOID	Game_Paint(HWND hwnd);	
VOID    Pause_Paint(HWND hwnd);
VOID    End_Paint(HWND hwnd);
VOID	Loadbmps();
VOID	Mouse(HWND hwnd);
BOOL	Game_CleanUp(HWND hwnd);	
VOID	CreateEnemy(HWND hwnd);
VOID    CreateMybullet();


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	//HKL hkl = LoadKeyboardLayout((LPCTSTR)"DX0409", KLF_ACTIVATE);
	//ActivateKeyboardLayout(hkl, KLF_SETFORPROCESS);

	g_iblood = 6; //玩家默认初始血量6

	//【1】窗口创建四步曲之一：开始设计一个完整的窗口类
	WNDCLASSEX wndClass = { 0 };							//用WINDCLASSEX定义了一个窗口类
	wndClass.cbSize = sizeof(WNDCLASSEX);			//设置结构体的字节数大小
	wndClass.style = CS_HREDRAW | CS_VREDRAW;	//设置窗口的样式
	wndClass.lpfnWndProc = WndProc;					//设置指向窗口过程函数的指针
	wndClass.cbClsExtra = 0;								//窗口类的附加内存，取0就可以了
	wndClass.cbWndExtra = 0;							//窗口的附加内存，依然取0就行了
	wndClass.hInstance = hInstance;						//指定包含窗口过程的程序的实例句柄。
	wndClass.hIcon = (HICON)::LoadImage(NULL, L"icon.ico", IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_LOADFROMFILE);  //本地加载自定义ico图标
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);    //指定窗口类的光标句柄。
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);  //为hbrBackground成员指定一个白色画刷句柄	
	wndClass.lpszMenuName = NULL;						//用一个以空终止的字符串，指定菜单资源的名字。
	wndClass.lpszClassName = L"Plane";		//用一个以空终止的字符串，指定窗口类的名字。

	//【2】窗口创建四步曲之二：注册窗口类
	if (!RegisterClassEx(&wndClass))				//设计完窗口后，需要对窗口类进行注册，这样才能创建该类型的窗口
		return -1;
	//【3】窗口创建四步曲之三：正式创建窗口
	HWND hwnd = CreateWindow(L"Plane", WINDOW_TITLE,				//喜闻乐见的创建窗口函数CreateWindow
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, WINDOW_WIDTH,
		WINDOW_HEIGHT, NULL, NULL, hInstance, NULL);

	//【4】窗口创建四步曲之四：窗口的移动、显示与更新
	MoveWindow(hwnd, 250, 80, WINDOW_WIDTH, WINDOW_HEIGHT, true);		//调整窗口显示时的位置，使窗口左上角位于（250,80）处
	ShowWindow(hwnd, nShowCmd);    //调用ShowWindow函数来显示窗口
	UpdateWindow(hwnd);						//对窗口进行更新，就像我们买了新房子要装修一样

	//游戏资源的初始化，若初始化失败，弹出一个消息框，并返回FALSE
	if (!Start_Init(hwnd))
	{
		MessageBox(hwnd, L"资源初始化失败", L"消息窗口", 0); //使用MessageBox函数，创建一个消息窗口
		return FALSE;
	}

	MSG msg = { 0 };				//定义并初始化msg
	while (msg.message != WM_QUIT)		//使用while循环，如果消息不是WM_QUIT消息，就继续循环
	{
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))   //查看应用程序消息队列，有消息时将队列中的消息派发出去。
		{
			TranslateMessage(&msg);		//将虚拟键消息转换为字符消息
			DispatchMessage(&msg);			//分发一个消息给窗口程序。
		}
		else
		{
			if (g_igame == 0) {
				Start_Paint(hwnd);
			}
			if (g_igame == 1) {
				g_tNow = GetTickCount();   //获取当前系统时间
				if (g_tNow - g_tPre >= 5) { //当此次循环运行与上次绘图时间相差0.1秒时再进行重绘操作
					if (g_iblood <= 0) {
						g_blose = true;
					}
					if (g_blose) {
						ClipCursor(NULL);//取消鼠标位置锁定
						ShowCursor(true);
						g_igame = 3;
					}
					g_ibc1++;
					g_icounter++;
					g_icounter2++;
					Game_Paint(hwnd);
				}
			}
			if (g_igame == 2) {
				Pause_Paint(hwnd);
			}
			if (g_igame == 3) {
				End_Paint(hwnd);
			}
			if (g_igame == 4) {
				Info_Paint(hwnd);
			}
		}

	}

	//【6】窗口类的注销
	UnregisterClass(L"Plane", wndClass.hInstance);  //程序准备结束，注销窗口类
	return 0;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	EnemyBullet bullet;
	switch (message)	
	{

	case WM_KEYDOWN:	     //按下键盘消息
		//判断按键的虚拟键码
		switch (wParam)
		{
		case VK_ESCAPE:   //按下【Esc】键
			if (g_igame == 1) {
				ClipCursor(NULL);//取消鼠标位置锁定
				ShowCursor(true);
				g_igame = 2; //进入暂停
			}
			else if (g_igame == 2) {
				Mouse(hwnd);
				g_igame = 1;//返回游戏
			}
			else if (g_igame == 4) {
				g_igame = 0;//返回开始界面
			}
			break;
		case 81://按下Q键
			g_isq = true;
			break;
		case 69://按下E键
			g_ise = true;
			break;
		}
		break;

	case WM_LBUTTONDOWN: //单击鼠标左键消息
		if (g_igame == 0) {
			if (LOWORD(lParam) > 0 && LOWORD(lParam) < 200 && HIWORD(lParam) > 200 && HIWORD(lParam) < 275) {
				Game_Init(hwnd);
				g_igame = 1; //游戏开始
			}
			if (LOWORD(lParam) > 0 && LOWORD(lParam) < 200 && HIWORD(lParam) > 300 && HIWORD(lParam) < 375) {
				g_igame = 4; //进入说明界面
			}
			if (LOWORD(lParam) > 0 && LOWORD(lParam) < 200 && HIWORD(lParam) > 400 && HIWORD(lParam) < 475) {
				exit(0);
			}
		}
		if (g_igame == 2) {
			if (LOWORD(lParam) > 225 && LOWORD(lParam) < 375 && HIWORD(lParam) > 300 && HIWORD(lParam) < 370) {
				Mouse(hwnd);
				g_igame = 1; //游戏开始
			}
			if (LOWORD(lParam) > 225 && LOWORD(lParam) < 375 && HIWORD(lParam) > 400 && HIWORD(lParam) < 470) {
				Back_Init(hwnd);//返回开始界面
				g_igame = 0; 
			}
		}
		if (g_igame == 3) {
			if (LOWORD(lParam) > 225 && LOWORD(lParam) < 375 && HIWORD(lParam) > 300 && HIWORD(lParam) < 370) {
				Back_Init(hwnd);//重载游戏数据
				Mouse(hwnd);
				g_igame = 1; //游戏开始
			}
			if (LOWORD(lParam) > 225 && LOWORD(lParam) < 375 && HIWORD(lParam) > 400 && HIWORD(lParam) < 470) {

				Back_Init(hwnd);//返回开始界面
				g_igame = 0;
			}
		}
		break;
	case WM_MOUSEMOVE:   //鼠标移动消息		
		//对X坐标的处理
		g_iX = LOWORD(lParam);			//取得鼠标X坐标
		if (g_iX > WINDOW_WIDTH - 100)	//设置临界坐标
			g_iX = WINDOW_WIDTH - 100;
		else if (g_iX < 0)
			g_iX = 0;
		//对Y坐标的处理
		g_iY = HIWORD(lParam);			//取得鼠标Y坐标
		if (g_iY < 100 )
			g_iY = 100;
		else if (g_iY > 400)
			g_iY = 400;
		break;
		//采用类来存储飞机和子弹等物品
	case WM_DESTROY:				//若是窗口销毁消息
		Game_CleanUp(hwnd);			//调用自定义的资源清理函数Game_CleanUp（）进行退出前的资源清理
		PostQuitMessage(0);			//向系统表明有个线程有终止请求。用来响应WM_DESTROY消息
		break;									
	default:										//若上述case条件都不符合，则执行该default语句
		return DefWindowProc(hwnd, message, wParam, lParam);		//调用缺省的窗口过程
	}
	return 0;									//正常退出
}
BOOL Start_Init(HWND hwnd)
{

	HBITMAP bmp;

	g_blose = false;
	g_hdc = GetDC(hwnd);
	g_mdc = CreateCompatibleDC(g_hdc);  //创建一个和hdc兼容的内存DC
	g_bufdc = CreateCompatibleDC(g_hdc);//再创建一个和hdc兼容的缓冲DC
	bmp = CreateCompatibleBitmap(g_hdc, WINDOW_WIDTH, WINDOW_HEIGHT);

	g_iX = 400;
	g_iY = 300;
	g_iXnow = 400;
	g_iYnow = 300;

	SelectObject(g_mdc, bmp);
	Loadbmps();

	Start_Paint(hwnd);
	return TRUE;
}
BOOL Back_Init(HWND hwnd) {
	//重载游戏数据区域
	ClipCursor(NULL);//取消鼠标位置锁定
	ShowCursor(true);
	g_iblood = 6;
	g_blose = false;
	g_igame = 0;
	g_iscore = 0;
	g_icounter = 0;
	g_icounter2 = 0;
	g_ibc1 = 0;
	g_ilevel = 1;
	g_isboss = false;
	g_iQweapon = 1;
	g_iEweapon = 1;
	Plane::Planelist.clear();
	EnemyBullet::bulletlist.clear();
	Item::itemlist.clear();
	Effect::effectlist.clear();
	return TRUE;
}
BOOL Game_Init(HWND hwnd) {

	POINT pt;
	pt.x = 300;
	pt.y = 300;
	ClientToScreen(hwnd, &pt);
	SetCursorPos(pt.x, pt.y);

	//作弊专用代码区
	//g_iscore = 5000;
	//g_ilevel = 15;

	Mouse(hwnd);

	Game_Paint(hwnd);
	return TRUE;
}
VOID Info_Paint(HWND hwnd) {
	SelectObject(g_bufdc, g_hInfoBack);
	BitBlt(g_mdc, 0, 0, 600, 600, g_bufdc, 0, 0, SRCCOPY);
	BitBlt(g_hdc, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, g_mdc, 0, 0, SRCCOPY);
}
VOID Pause_Paint(HWND hwnd) {
	SelectObject(g_bufdc, g_hPauseback);
	BitBlt(g_mdc, 100, 100, 400, 400, g_bufdc, 0, 0, SRCCOPY);
	SelectObject(g_bufdc, g_hPause1);
	BitBlt(g_mdc, 225, 300, 150, 70, g_bufdc, 0, 0, SRCCOPY);
	SelectObject(g_bufdc, g_hPause2);
	BitBlt(g_mdc, 225, 400, 150, 70, g_bufdc, 0, 0, SRCCOPY);
	BitBlt(g_hdc, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, g_mdc, 0, 0, SRCCOPY);
}
VOID End_Paint(HWND hwnd) {
	SelectObject(g_bufdc, g_hEndback);
	BitBlt(g_mdc, 100, 100, 400, 400, g_bufdc, 0, 0, SRCCOPY);
	SelectObject(g_bufdc, g_hEnd1);
	BitBlt(g_mdc, 225, 300, 150, 70, g_bufdc, 0, 0, SRCCOPY);
	SelectObject(g_bufdc, g_hEnd2);
	BitBlt(g_mdc, 225, 400, 150, 70, g_bufdc, 0, 0, SRCCOPY);

	HFONT hFont = CreateFont(70, 0, 0, 0, 0, 0, 0, 0, GB2312_CHARSET, 0, 0, 0, 0, L"黑体");  //创建一种字体
	SelectObject(g_mdc, hFont);  //将字体选入设备环境中
	SetBkMode(g_mdc, TRANSPARENT);    //设置输出文字背景色为透明

	WCHAR buf[16];
	wsprintfW(buf, L"%d", g_iscore);
	SetTextColor(g_mdc, RGB(124, 4, 4));
	TextOut(g_mdc, 210, 150, buf, wcslen(buf));

	DeleteObject(hFont);//释放字体对象

	BitBlt(g_hdc, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, g_mdc, 0, 0, SRCCOPY);
}
VOID Start_Paint(HWND hwnd) {
	//透明位图
	//_BLENDFUNCTION bf;
	//bf.BlendOp = AC_SRC_OVER;
	//bf.BlendFlags = 0;
	//bf.SourceConstantAlpha = 10;
	//bf.AlphaFormat = 0;
	//AlphaBlend(g_mdc, 0, 200, 200, 75, g_bufdc, 0, 0, 200, 75, bf);
	SelectObject(g_bufdc, g_hStartback);
	BitBlt(g_mdc, 0, 0, 600, 600, g_bufdc, 0, 0, SRCCOPY);
	SelectObject(g_bufdc, g_hStart1);
	BitBlt(g_mdc, 0, 200, 200, 75, g_bufdc, 0, 0, SRCCOPY);
	SelectObject(g_bufdc, g_hStart2);
	BitBlt(g_mdc, 0, 300, 200, 75, g_bufdc, 0, 0, SRCCOPY);
	SelectObject(g_bufdc, g_hStart3);
	BitBlt(g_mdc, 0, 400, 200, 75, g_bufdc, 0, 0, SRCCOPY);
	BitBlt(g_hdc, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, g_mdc, 0, 0, SRCCOPY);
}
VOID Game_Paint(HWND hwnd)
{
	SelectObject(g_bufdc, g_hBack3);
	TransparentBlt(g_mdc, 0, 0, WINDOW_WIDTH, g_iBGOffset3, g_bufdc, 0, WINDOW_HEIGHT - g_iBGOffset3, WINDOW_WIDTH, g_iBGOffset3, RGB(0, 0, 0));
	TransparentBlt(g_mdc, 0, g_iBGOffset3, WINDOW_WIDTH, WINDOW_HEIGHT - g_iBGOffset3, g_bufdc, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT - g_iBGOffset3, RGB(0, 0, 0));
	SelectObject(g_bufdc, g_hBack2);
	TransparentBlt(g_mdc, 0, 0, WINDOW_WIDTH, g_iBGOffset, g_bufdc, 0, WINDOW_HEIGHT - g_iBGOffset, WINDOW_WIDTH, g_iBGOffset, RGB(0, 0, 0));
	TransparentBlt(g_mdc, 0, g_iBGOffset, WINDOW_WIDTH, WINDOW_HEIGHT - g_iBGOffset, g_bufdc, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT - g_iBGOffset,RGB(0, 0, 0));
	//SelectObject(g_bufdc, g_hBack1);
	//TransparentBlt(g_mdc, 0, 0, WINDOW_WIDTH, g_iBGOffset2, g_bufdc, 0, WINDOW_HEIGHT - g_iBGOffset2, WINDOW_WIDTH, g_iBGOffset2, RGB(0, 0, 0));
	//TransparentBlt(g_mdc, 0, g_iBGOffset2, WINDOW_WIDTH, WINDOW_HEIGHT - g_iBGOffset2, g_bufdc, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT - g_iBGOffset2, RGB(0, 0, 0));
	//计算贴图坐标

	g_ispeed = 10;
	g_bhudun = false;
	Effect::LoadEffect();

	if (g_iXnow < g_iX)//若当前贴图X坐标小于鼠标光标的X坐标
	{
		g_iXnow += g_ispeed;
		if (g_iXnow > g_iX)
			g_iXnow = g_iX;
	}
	else   //若当前贴图X坐标大于鼠标光标的X坐标
	{
		g_iXnow -= g_ispeed;
		if (g_iXnow < g_iX)
			g_iXnow = g_iX;
	}

	if (g_iYnow < g_iY)  //若当前贴图Y坐标小于鼠标光标的Y坐标
	{
		g_iYnow += g_ispeed;
		if (g_iYnow > g_iY)
			g_iYnow = g_iY;
	}
	else  //若当前贴图Y坐标大于于鼠标光标的Y坐标
	{
		g_iYnow -= g_ispeed;
		if (g_iYnow < g_iY)
			g_iYnow = g_iY;
	}

	//贴上飞机
	if (g_bhudun) {
		SelectObject(g_bufdc, g_hPlanehudun);
	}
	else {
		SelectObject(g_bufdc, g_hPlane);
	}
	TransparentBlt(g_mdc, g_iXnow, g_iYnow, 100, 100, g_bufdc, 0, 0, 100, 100, RGB(0, 0, 0));
	//玩家飞机与子弹目前外置

	CreateMybullet();
	CreateEnemy(hwnd);
	Plane::Reloadbmp();
	EnemyBullet::ReloadBullet(hwnd);
	Item::ReloadItem();
	//玩家飞机消息
	SelectObject(g_bufdc, g_hPlaneinfo);
	TransparentBlt(g_mdc, 50, 460, 500, 100, g_bufdc, 0, 0, 500, 100, RGB(0, 0, 0));
	switch (g_iQweapon) {
	case(0):
		SelectObject(g_bufdc, g_hQ[0]);
		break;
	case(1):
		SelectObject(g_bufdc, g_hQ[1]);
		break;
	case(2):
		SelectObject(g_bufdc, g_hQ[2]);
		break;
	case(3):
		SelectObject(g_bufdc, g_hQ[3]);
		break;
	}
	TransparentBlt(g_mdc, 50, 460, 500, 100, g_bufdc, 0, 0, 500, 100, RGB(0, 0, 0));
	switch (g_iEweapon) {
	case(0):
		SelectObject(g_bufdc, g_hE[0]);
		break;
	case(1):
		SelectObject(g_bufdc, g_hE[1]);
		break;
	case(2):
		SelectObject(g_bufdc, g_hE[2]);
		break;
	case(3):
		SelectObject(g_bufdc, g_hE[3]);
		break;
	}
	TransparentBlt(g_mdc, 50, 460, 500, 100, g_bufdc, 0, 0, 500, 100, RGB(0, 0, 0));
	switch (g_iblood)
	{
	case(0):
		SelectObject(g_bufdc, g_hblood[0]);
		break;
	case(1):
		SelectObject(g_bufdc, g_hblood[1]);
		break;
	case(2):
		SelectObject(g_bufdc, g_hblood[2]);
		break;
	case(3):
		SelectObject(g_bufdc, g_hblood[3]);
		break;
	case(4):
		SelectObject(g_bufdc, g_hblood[4]);
		break;
	case(5):
		SelectObject(g_bufdc, g_hblood[5]);
		break;
	case(6):
		SelectObject(g_bufdc, g_hblood[6]);
		break;
	case(7):
		SelectObject(g_bufdc, g_hblood[7]);
		break;
	case(8):
		SelectObject(g_bufdc, g_hblood[8]);
		break;
	}
	//分数显示
	TransparentBlt(g_mdc, 50, 460, 500, 100, g_bufdc, 0, 0, 500, 100, RGB(0, 0, 0));
	//背景滚动
	HFONT hFont = CreateFont(60, 0, 0, 0, 0, 0, 0, 0, GB2312_CHARSET, 0, 0, 0, 0, L"黑体");  //创建一种字体
	SelectObject(g_mdc, hFont);  //将字体选入设备环境中
	SetBkMode(g_mdc, TRANSPARENT);    //设置输出文字背景色为透明

	WCHAR buf[16];
	wsprintfW(buf, L"%d", g_iscore);
	SetTextColor(g_mdc, RGB(200, 50, 50));
	TextOut(g_mdc, 60, 475, buf, wcslen(buf));

	DeleteObject(hFont);//释放字体对象

	BitBlt(g_hdc, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, g_mdc, 0, 0, SRCCOPY);

	g_tPre = GetTickCount();

	g_iBGOffset3 += 1;
	if (g_iBGOffset3 == WINDOW_HEIGHT) {
		g_iBGOffset3 = 0;
	}
	g_iBGOffset += 2; 
	if (g_iBGOffset == WINDOW_HEIGHT) {
		g_iBGOffset = 0;
	}
	//g_iBGOffset2 += 3;
	//if (g_iBGOffset2 == WINDOW_HEIGHT) {
	//	g_iBGOffset2 = 0;
	//}

}
BOOL Game_CleanUp(HWND hwnd)
{
	//释放资源对象
	DeleteObject(g_hBack3);
	DeleteObject(g_hBack2);
	DeleteObject(g_hBack1);
	DeleteDC(g_bufdc);
	DeleteDC(g_mdc);
	ReleaseDC(hwnd, g_hdc);
	return TRUE;
}
VOID  CreateMybullet() {

	EnemyBullet bullet;

	if (g_isq) {
		g_isq = false;
		if (g_iQweapon > 0) {
			g_iQweapon--;
			bullet = EnemyBullet(g_iXnow + 20, g_iYnow + 30, 0, 15, EnemyBullet::BULLETS::MYMISSILE);
			EnemyBullet::bulletlist.push_back(bullet);
			bullet = EnemyBullet(g_iXnow + 65, g_iYnow + 30, 0, 15, EnemyBullet::BULLETS::MYMISSILE);
			EnemyBullet::bulletlist.push_back(bullet);
			bullet = EnemyBullet(g_iXnow + 20, g_iYnow + 30, 0, 14, EnemyBullet::BULLETS::MYMISSILE);
			EnemyBullet::bulletlist.push_back(bullet);
			bullet = EnemyBullet(g_iXnow + 65, g_iYnow + 30, 0, 14, EnemyBullet::BULLETS::MYMISSILE);
			EnemyBullet::bulletlist.push_back(bullet);
			bullet = EnemyBullet(g_iXnow + 20, g_iYnow + 30, 0, 13, EnemyBullet::BULLETS::MYMISSILE);
			EnemyBullet::bulletlist.push_back(bullet);
			bullet = EnemyBullet(g_iXnow + 65, g_iYnow + 30, 0, 13, EnemyBullet::BULLETS::MYMISSILE);
			EnemyBullet::bulletlist.push_back(bullet);
			bullet = EnemyBullet(g_iXnow + 20, g_iYnow + 30, 0, 12, EnemyBullet::BULLETS::MYMISSILE);
			EnemyBullet::bulletlist.push_back(bullet);
			bullet = EnemyBullet(g_iXnow + 65, g_iYnow + 30, 0, 12, EnemyBullet::BULLETS::MYMISSILE);
			EnemyBullet::bulletlist.push_back(bullet);
			bullet = EnemyBullet(g_iXnow + 20, g_iYnow + 30, 0, 11, EnemyBullet::BULLETS::MYMISSILE);
			EnemyBullet::bulletlist.push_back(bullet);
			bullet = EnemyBullet(g_iXnow + 65, g_iYnow + 30, 0, 11, EnemyBullet::BULLETS::MYMISSILE);
			EnemyBullet::bulletlist.push_back(bullet);
		}
	}
	if (g_ise) {
		g_ise = false;
		if (g_iEweapon > 0) {
			g_iEweapon--;
			bullet = EnemyBullet(g_iXnow + 30, g_iYnow + 30, 0, 5, EnemyBullet::BULLETS::MYBIG);
			EnemyBullet::bulletlist.push_back(bullet);
		}
	}
	switch (g_ilevel) {
	case(1):
		if (g_icounter == 10) {
			g_icounter = 0;
			bullet = EnemyBullet(g_iXnow + 20, g_iYnow + 30, 0, 10, EnemyBullet::BULLETS::MYNORMAL);
			EnemyBullet::bulletlist.push_back(bullet);
			bullet = EnemyBullet(g_iXnow + 65, g_iYnow + 30, 0, 10, EnemyBullet::BULLETS::MYNORMAL);
			EnemyBullet::bulletlist.push_back(bullet);
		}
		break;
	case(2):
		if (g_icounter == 10) {
			g_icounter = 0;
			bullet = EnemyBullet(g_iXnow + 20, g_iYnow + 30, 0, 10, EnemyBullet::BULLETS::MYNORMAL);
			EnemyBullet::bulletlist.push_back(bullet);
			bullet = EnemyBullet(g_iXnow + 65, g_iYnow + 30, 0, 10, EnemyBullet::BULLETS::MYNORMAL);
			EnemyBullet::bulletlist.push_back(bullet);
		}
		if (g_ibc1 > 40) {
			g_ibc1 = 0;
			bullet = EnemyBullet(g_iXnow + 40, g_iYnow + 20, 0, 10, EnemyBullet::BULLETS::MYNORMAL);
			EnemyBullet::bulletlist.push_back(bullet);
		}
		break;
	case(3):
		if (g_icounter == 10) {
			g_icounter = 0;
			bullet = EnemyBullet(g_iXnow + 20, g_iYnow + 30, 0, 10, EnemyBullet::BULLETS::MYNORMAL);
			EnemyBullet::bulletlist.push_back(bullet);
			bullet = EnemyBullet(g_iXnow + 65, g_iYnow + 30, 0, 10, EnemyBullet::BULLETS::MYNORMAL);
			EnemyBullet::bulletlist.push_back(bullet);
		}
		if (g_ibc1 > 40) {
			g_ibc1 = 0;
			bullet = EnemyBullet(g_iXnow + 40, g_iYnow + 20, 3, 8, EnemyBullet::BULLETS::MYROUND);
			EnemyBullet::bulletlist.push_back(bullet);
			bullet = EnemyBullet(g_iXnow + 40, g_iYnow + 20, -3, 8, EnemyBullet::BULLETS::MYROUND);
			EnemyBullet::bulletlist.push_back(bullet);
		}
		break;
	case(4):
		if (g_icounter == 10) {
			g_icounter = 0;
			bullet = EnemyBullet(g_iXnow + 20, g_iYnow + 30, 0, 10, EnemyBullet::BULLETS::MYNORMAL);
			EnemyBullet::bulletlist.push_back(bullet);
			bullet = EnemyBullet(g_iXnow + 65, g_iYnow + 30, 0, 10, EnemyBullet::BULLETS::MYNORMAL);
			EnemyBullet::bulletlist.push_back(bullet);
		}
		if (g_ibc1 > 40) {
			g_ibc1 = 0;
			bullet = EnemyBullet(g_iXnow + 40, g_iYnow + 20, 3, 8, EnemyBullet::BULLETS::MYROUND);
			EnemyBullet::bulletlist.push_back(bullet);
			bullet = EnemyBullet(g_iXnow + 40, g_iYnow + 20, 0, 8, EnemyBullet::BULLETS::MYNORMAL);
			EnemyBullet::bulletlist.push_back(bullet);
			bullet = EnemyBullet(g_iXnow + 40, g_iYnow + 20, -3, 8, EnemyBullet::BULLETS::MYROUND);
			EnemyBullet::bulletlist.push_back(bullet);
		}
		break;
	case(5):
		if (g_icounter == 10) {
			g_icounter = 0;
			bullet = EnemyBullet(g_iXnow + 20, g_iYnow + 30, 0, 10, EnemyBullet::BULLETS::MYNORMAL);
			EnemyBullet::bulletlist.push_back(bullet);
			bullet = EnemyBullet(g_iXnow + 65, g_iYnow + 30, 0, 10, EnemyBullet::BULLETS::MYNORMAL);
			EnemyBullet::bulletlist.push_back(bullet);
			bullet = EnemyBullet(g_iXnow + 40, g_iYnow + 20, 0, 10, EnemyBullet::BULLETS::MYNORMAL);
			EnemyBullet::bulletlist.push_back(bullet);
		}
		if (g_ibc1 > 40) {
			g_ibc1 = 0;
			bullet = EnemyBullet(g_iXnow + 40, g_iYnow + 20, 3, 8, EnemyBullet::BULLETS::MYROUND);
			EnemyBullet::bulletlist.push_back(bullet);
			bullet = EnemyBullet(g_iXnow + 40, g_iYnow + 20, -3, 8, EnemyBullet::BULLETS::MYROUND);
			EnemyBullet::bulletlist.push_back(bullet);
		}
		break;
	case(6):
		if (g_icounter == 10) {
			g_icounter = 0;
			bullet = EnemyBullet(g_iXnow + 20, g_iYnow + 30, 0, 10, EnemyBullet::BULLETS::MYNORMAL);
			EnemyBullet::bulletlist.push_back(bullet);
			bullet = EnemyBullet(g_iXnow + 65, g_iYnow + 30, 0, 10, EnemyBullet::BULLETS::MYNORMAL);
			EnemyBullet::bulletlist.push_back(bullet);
			bullet = EnemyBullet(g_iXnow + 40, g_iYnow + 20, 0, 10, EnemyBullet::BULLETS::MYNORMAL);
			EnemyBullet::bulletlist.push_back(bullet);
		}
		if (g_ibc1 > 30) {
			g_ibc1 = 0;
			bullet = EnemyBullet(g_iXnow + 40, g_iYnow + 20, 3, 8, EnemyBullet::BULLETS::MYROUND);
			EnemyBullet::bulletlist.push_back(bullet);
			bullet = EnemyBullet(g_iXnow + 40, g_iYnow + 20, -3, 8, EnemyBullet::BULLETS::MYROUND);
			EnemyBullet::bulletlist.push_back(bullet);
		}
		break;
	case(7):
		if (g_icounter == 10) {
			g_icounter = 0;
			bullet = EnemyBullet(g_iXnow + 20, g_iYnow + 30, 0, 10, EnemyBullet::BULLETS::MYNORMAL);
			EnemyBullet::bulletlist.push_back(bullet);
			bullet = EnemyBullet(g_iXnow + 65, g_iYnow + 30, 0, 10, EnemyBullet::BULLETS::MYNORMAL);
			EnemyBullet::bulletlist.push_back(bullet);
			bullet = EnemyBullet(g_iXnow + 40, g_iYnow + 20, 0, 10, EnemyBullet::BULLETS::MYNORMAL);
			EnemyBullet::bulletlist.push_back(bullet);
		}
		if (g_ibc1 > 30) {
			g_ibc1 = 0;
			bullet = EnemyBullet(g_iXnow + 40, g_iYnow + 20, 1, 8, EnemyBullet::BULLETS::MYROUND);
			EnemyBullet::bulletlist.push_back(bullet);
			bullet = EnemyBullet(g_iXnow + 40, g_iYnow + 20, -1, 8, EnemyBullet::BULLETS::MYROUND);
			EnemyBullet::bulletlist.push_back(bullet);
			bullet = EnemyBullet(g_iXnow + 40, g_iYnow + 20, 3, 8, EnemyBullet::BULLETS::MYROUND);
			EnemyBullet::bulletlist.push_back(bullet);
			bullet = EnemyBullet(g_iXnow + 40, g_iYnow + 20, -3, 8, EnemyBullet::BULLETS::MYROUND);
			EnemyBullet::bulletlist.push_back(bullet);
		}
		break;
	case(8):
		if (g_icounter == 10) {
			g_icounter = 0;
			bullet = EnemyBullet(g_iXnow + 20, g_iYnow + 30, 0, 10, EnemyBullet::BULLETS::MYNORMAL);
			EnemyBullet::bulletlist.push_back(bullet);
			bullet = EnemyBullet(g_iXnow + 65, g_iYnow + 30, 0, 10, EnemyBullet::BULLETS::MYNORMAL);
			EnemyBullet::bulletlist.push_back(bullet);
			bullet = EnemyBullet(g_iXnow + 40, g_iYnow + 20, 0, 10, EnemyBullet::BULLETS::MYNORMAL);
			EnemyBullet::bulletlist.push_back(bullet);
		}
		if (g_ibc1 > 12) {
			g_ibc1 = 0;
			bullet = EnemyBullet(g_iXnow + 40, g_iYnow + 20, g_imove, 6, EnemyBullet::BULLETS::MYROUND);
			EnemyBullet::bulletlist.push_back(bullet);
			bullet = EnemyBullet(g_iXnow + 40, g_iYnow + 20, -(g_imove), 6, EnemyBullet::BULLETS::MYROUND);
			EnemyBullet::bulletlist.push_back(bullet);
			g_imove--;
			if (g_imove == 0) {
				g_imove = 3;
			}
		}
		break;
	case(9):
		if (g_icounter == 10) {
			g_icounter = 0;
			bullet = EnemyBullet(g_iXnow + 20, g_iYnow + 30, 0, 10, EnemyBullet::BULLETS::MYNORMAL);
			EnemyBullet::bulletlist.push_back(bullet);
			bullet = EnemyBullet(g_iXnow + 65, g_iYnow + 30, 0, 10, EnemyBullet::BULLETS::MYNORMAL);
			EnemyBullet::bulletlist.push_back(bullet);
			bullet = EnemyBullet(g_iXnow + 40, g_iYnow + 20, 0, 10, EnemyBullet::BULLETS::MYNORMAL);
			EnemyBullet::bulletlist.push_back(bullet);
		}
		if (g_ibc1 > 10) {
			g_ibc1 = 0;
			bullet = EnemyBullet(g_iXnow + 20, g_iYnow + 20, g_imove, 6, EnemyBullet::BULLETS::MYROUND);
			EnemyBullet::bulletlist.push_back(bullet);
			bullet = EnemyBullet(g_iXnow + 65, g_iYnow + 20, -(g_imove), 6, EnemyBullet::BULLETS::MYROUND);
			EnemyBullet::bulletlist.push_back(bullet);
			g_imove--;
			if (g_imove == -4) {
				g_imove = 3;
			}
		}
		break;
	default://高于十级的未更新
	case(10):
		if (g_icounter == 10) {
			g_icounter = 0;
			bullet = EnemyBullet(g_iXnow + 20, g_iYnow + 30, 0, 10, EnemyBullet::BULLETS::MYNORMAL);
			EnemyBullet::bulletlist.push_back(bullet);
			bullet = EnemyBullet(g_iXnow + 65, g_iYnow + 30, 0, 10, EnemyBullet::BULLETS::MYNORMAL);
			EnemyBullet::bulletlist.push_back(bullet);
			bullet = EnemyBullet(g_iXnow + 40, g_iYnow + 20, 0, 10, EnemyBullet::BULLETS::MYNORMAL);
			EnemyBullet::bulletlist.push_back(bullet);
		}
		if (g_ibc1 > 10) {
			g_ibc1 = 0;
			bullet = EnemyBullet(g_iXnow + 20, g_iYnow + 20, g_imove, 8, EnemyBullet::BULLETS::MYROUND);
			EnemyBullet::bulletlist.push_back(bullet);
			bullet = EnemyBullet(g_iXnow + 65, g_iYnow + 20, -(g_imove), 8, EnemyBullet::BULLETS::MYROUND);
			EnemyBullet::bulletlist.push_back(bullet);
			g_imove--;
			if (g_imove == -4) {
				g_imove = 3;
			}
		}
		break;
	}	
}
VOID  CreateEnemy(HWND hwnd) {
	int max_plane = 2;
	int cooldown = 100;
	int diffcult = 0;
	if (g_iscore > 100 && g_iscore < 300) {
		diffcult = 1;
		max_plane = 3;
		cooldown = 95;
	}
	else if (g_iscore >= 300 && g_iscore < 500) {
		diffcult = 2;
		max_plane = 3;
		cooldown = 95;
	}
	else if (g_iscore >= 500 && g_iscore < 700) {
		diffcult = 3;
		max_plane = 1;
		cooldown = 95;
	}
	else if (g_iscore >= 700 && g_iscore < 1250) {
		diffcult = 4;
		max_plane = 3;
		cooldown = 95;
	}
	else if (g_iscore >= 1250 && g_iscore < 2000) {
		diffcult = 5;
		max_plane = 3;
		cooldown = 90;
	}
	else if (g_iscore >= 2000 && g_iscore < 2300) {
		if (Plane::Planelist.empty()) {
			if (!g_isboss) {
				boss1 = Boss1(200, -120, 300, 300, 200, 120);
				g_isboss = true;
			}
			else {
				boss1.Move();
				boss1.Attack();
				if (boss1.Getblood() <= 0) {
					g_iscore += 300;
					g_isboss = false;
				}
			}
		}
		max_plane = 0;
	}
	else if (g_iscore >= 2300 && g_iscore < 3000) {
		diffcult = 6;
		max_plane = 4;
		cooldown = 100;
	}
	else  if (g_iscore >= 3000) {
		//防止无飞机生成
		diffcult = 6;
		max_plane = 4;
		cooldown = 100;
	}
	if (g_icounter2 >= cooldown && Plane::Planelist.size()< max_plane) {
		Plane enemy_attack;
		g_icounter2 = 0;
		int type;
		std::uniform_int_distribution<unsigned int> randomInt1(1,3);
		std::uniform_int_distribution<unsigned int> randomInt2(1,7);
		switch (diffcult){
		case(0):
			enemy_attack = Plane(400, 1, Plane::Planes::ATTACK);
			Plane::Planelist.push_back(enemy_attack);
			break;
		case(1):
			type = randomInt1(engine);
			switch (type)
			{
			case(1):
				enemy_attack = Plane(400, 1, Plane::Planes::ATTACK);
				break;
			case(2):
				enemy_attack = Plane(800, 1, Plane::Planes::ATTACKTWO);
				break;
			case(3):
				enemy_attack = Plane(750, 1, Plane::Planes::MISSILENOR);
				break;
			}
			Plane::Planelist.push_back(enemy_attack);
			break;
		case(2):
			type = randomInt2(engine);
			switch (type)
			{
			case(1):
			case(2):
				enemy_attack = Plane(400, 2, Plane::Planes::ATTACK);
				break;
			case(3):
			case(4):
				enemy_attack = Plane(800, 1, Plane::Planes::ATTACKTWO);
				break;
			case(5):
			case(6):
				enemy_attack = Plane(750, 1, Plane::Planes::MISSILENOR);
				break;
			case(7):
				enemy_attack = Plane(700, 1, Plane::Planes::CARGO);
				break;
			}
			Plane::Planelist.push_back(enemy_attack);
			break;
		case(3):
			enemy_attack = Plane(750, 1, Plane::Planes::BOSS1);
			Plane::Planelist.push_back(enemy_attack);
			break;
		case(4):
			type = randomInt2(engine);
			switch (type)
			{
			case(1):
				enemy_attack = Plane(450, 2, Plane::Planes::ATTACK);
				break;
			case(2):
				enemy_attack = Plane(400, 1, Plane::Planes::ATTACK);
				break;
			case(3):
				enemy_attack = Plane(500, 2, Plane::Planes::ATTACKTHREE);
				break;
			case(4):
				enemy_attack = Plane(800, 1, Plane::Planes::ATTACKTWO);
				break;
			case(5):
				enemy_attack = Plane(700, 1, Plane::Planes::MISSILETWO);
				break;
			case(6):
				enemy_attack = Plane(750, 1, Plane::Planes::MISSILENOR);
				break;
			case(7):
				enemy_attack = Plane(700, 1, Plane::Planes::CARGO);
				break;
			}
			Plane::Planelist.push_back(enemy_attack);
			break;
		case(5):
			type = randomInt2(engine);
			switch (type)
			{
			case(1):
			case(2):
				enemy_attack = Plane(500, 1, Plane::Planes::ATTACKTHREE);
				break;
			case(3):
				enemy_attack = Plane(750, 1, Plane::Planes::ATTACKFOUR);
				break;
			case(4):
				enemy_attack = Plane(800, 1, Plane::Planes::ATTACKTWO);
				break;
			case(5):
				enemy_attack = Plane(700, 1, Plane::Planes::MISSILETWO);
				break;
			case(6):
				enemy_attack = Plane(1200, 1, Plane::Planes::SANDAN);
				break;
			case(7):
				enemy_attack = Plane(1800, 1, Plane::Planes::CARGOTWO);
				break;
			}
			Plane::Planelist.push_back(enemy_attack);
			break;
		case(6):
			type = randomInt2(engine);
			switch (type)
			{
			case(1):
				enemy_attack = Plane(700, 1, Plane::Planes::ATTACKFIVE);
				break;
			case(2):
				enemy_attack = Plane(500, 1, Plane::Planes::ATTACKTHREE);
				break;
			case(3):
				enemy_attack = Plane(750, 1, Plane::Planes::ATTACKFOUR);
				break;
			case(4):
				enemy_attack = Plane(800, 1, Plane::Planes::ATTACKTWO);
				break;
			case(5):
				enemy_attack = Plane(700, 1, Plane::Planes::MISSILETWO);
				break;
			case(6):
				enemy_attack = Plane(1200, 1, Plane::Planes::SANDAN);
				break;
			case(7):
				enemy_attack = Plane(1800, 1, Plane::Planes::CARGOTWO);
				break;
			}
			Plane::Planelist.push_back(enemy_attack);
			break;
		}		


	}
}

VOID Mouse(HWND hwnd) {
	//设定光标位置
	POINT pt, lt, rb;
	RECT rect;

	//隐藏鼠标光标(似乎不太行)
	ShowCursor(false);

	//限制鼠标光标移动区域
	GetClientRect(hwnd, &rect);  //取得窗口内部矩形
	//将矩形左上点坐标存入lt中
	lt.x = rect.left;
	lt.y = rect.top;
	//将矩形右下坐标存入rb中
	rb.x = rect.right;
	rb.y = rect.bottom;
	//将lt和rb的窗口坐标转换为屏幕坐标
	ClientToScreen(hwnd, &lt);
	ClientToScreen(hwnd, &rb);
	//以屏幕坐标重新设定矩形区域
	rect.left = lt.x;
	rect.top = lt.y;
	rect.right = rb.x;
	rect.bottom = rb.y;
	//限制鼠标光标移动区域
	ClipCursor(&rect);
}
VOID Loadbmps() {
	g_hItem1 = (HBITMAP)LoadImage(NULL, L"GameMedia\\item\\item_blood.bmp", IMAGE_BITMAP, 50, 50, LR_LOADFROMFILE);
	g_hItem2 = (HBITMAP)LoadImage(NULL, L"GameMedia\\item\\item_defend.bmp", IMAGE_BITMAP, 50, 50, LR_LOADFROMFILE);
	g_hItem3 = (HBITMAP)LoadImage(NULL, L"GameMedia\\item\\item_speed.bmp", IMAGE_BITMAP, 50, 50, LR_LOADFROMFILE);
	g_hItem4 = (HBITMAP)LoadImage(NULL, L"GameMedia\\item\\item_weaponup.bmp", IMAGE_BITMAP, 50, 50, LR_LOADFROMFILE);
	g_hItem5 = (HBITMAP)LoadImage(NULL, L"GameMedia\\item\\item_missile.bmp", IMAGE_BITMAP, 50, 50, LR_LOADFROMFILE);
	g_hItem6 = (HBITMAP)LoadImage(NULL, L"GameMedia\\item\\item_big.bmp", IMAGE_BITMAP, 50, 50, LR_LOADFROMFILE);
	g_hPause1 = (HBITMAP)LoadImage(NULL, L"GameMedia\\background\\pause1.bmp", IMAGE_BITMAP, 150, 70, LR_LOADFROMFILE);
	g_hPause2 = (HBITMAP)LoadImage(NULL, L"GameMedia\\background\\pause2.bmp", IMAGE_BITMAP, 150, 70, LR_LOADFROMFILE);
	g_hPauseback = (HBITMAP)LoadImage(NULL, L"GameMedia\\background\\pauseback.bmp", IMAGE_BITMAP, 400, 400, LR_LOADFROMFILE);
	g_hEnd1 = (HBITMAP)LoadImage(NULL, L"GameMedia\\background\\end1.bmp", IMAGE_BITMAP, 150, 70, LR_LOADFROMFILE);
	g_hEnd2 = (HBITMAP)LoadImage(NULL, L"GameMedia\\background\\end2.bmp", IMAGE_BITMAP, 150, 70, LR_LOADFROMFILE);
	g_hEndback = (HBITMAP)LoadImage(NULL, L"GameMedia\\background\\endback.bmp", IMAGE_BITMAP, 400, 400, LR_LOADFROMFILE);
	g_hStart1 = (HBITMAP)LoadImage(NULL, L"GameMedia\\background\\start1.bmp", IMAGE_BITMAP, 200, 75, LR_LOADFROMFILE);
	g_hStart2 = (HBITMAP)LoadImage(NULL, L"GameMedia\\background\\start2.bmp", IMAGE_BITMAP, 200, 75, LR_LOADFROMFILE);
	g_hStart3 = (HBITMAP)LoadImage(NULL, L"GameMedia\\background\\start3.bmp", IMAGE_BITMAP, 200, 75, LR_LOADFROMFILE);
	g_hBlue = (HBITMAP)LoadImage(NULL, L"GameMedia\\background\\blue.bmp", IMAGE_BITMAP, 200, 75, LR_LOADFROMFILE);
	g_hStartback = (HBITMAP)LoadImage(NULL, L"GameMedia\\background\\startback.bmp", IMAGE_BITMAP, 600, 600, LR_LOADFROMFILE);
	g_hSmoke = (HBITMAP)LoadImage(NULL, L"GameMedia\\smoke.bmp", IMAGE_BITMAP, 10, 10, LR_LOADFROMFILE);
	g_hPlane = (HBITMAP)LoadImage(NULL, L"GameMedia\\plane.bmp", IMAGE_BITMAP, 100, 100, LR_LOADFROMFILE);
	g_hZidan = (HBITMAP)LoadImage(NULL, L"GameMedia\\zidan.bmp", IMAGE_BITMAP, 20, 20, LR_LOADFROMFILE);
	g_hPlanehudun = (HBITMAP)LoadImage(NULL, L"GameMedia\\planehudun.bmp", IMAGE_BITMAP, 100, 100, LR_LOADFROMFILE);
	g_hZidan2 = (HBITMAP)LoadImage(NULL, L"GameMedia\\zidan2.bmp", IMAGE_BITMAP, 20, 20, LR_LOADFROMFILE);
	g_hDazidan = (HBITMAP)LoadImage(NULL, L"GameMedia\\zidan3.bmp", IMAGE_BITMAP, 40, 40, LR_LOADFROMFILE);
	g_hMissile = (HBITMAP)LoadImage(NULL, L"GameMedia\\missile.bmp", IMAGE_BITMAP, 20, 40, LR_LOADFROMFILE);
	g_hEnemyPlane1 = (HBITMAP)LoadImage(NULL, L"GameMedia\\enemy\\enemyattack1.bmp", IMAGE_BITMAP, 120, 120, LR_LOADFROMFILE);
	g_hEnemyPlane2 = (HBITMAP)LoadImage(NULL, L"GameMedia\\enemy\\enemyattack2.bmp", IMAGE_BITMAP, 120, 120, LR_LOADFROMFILE);
	g_hEnemyPlane3 = (HBITMAP)LoadImage(NULL, L"GameMedia\\enemy\\enemymissileplane1.bmp", IMAGE_BITMAP, 120, 120, LR_LOADFROMFILE);
	g_hEnemyPlane4 = (HBITMAP)LoadImage(NULL, L"GameMedia\\enemy\\enemycargo1.bmp", IMAGE_BITMAP, 120, 120, LR_LOADFROMFILE);
	g_hEnemyPlane5 = (HBITMAP)LoadImage(NULL, L"GameMedia\\enemy\\enemymissileplane2.bmp", IMAGE_BITMAP, 120, 120, LR_LOADFROMFILE);
	g_hEnemyPlane6 = (HBITMAP)LoadImage(NULL, L"GameMedia\\enemy\\enemyattack3.bmp", IMAGE_BITMAP, 120, 120, LR_LOADFROMFILE);
	g_hEnemyPlane7 = (HBITMAP)LoadImage(NULL, L"GameMedia\\enemy\\enemyattack4.bmp", IMAGE_BITMAP, 120, 120, LR_LOADFROMFILE);
	g_hEnemyPlane8 = (HBITMAP)LoadImage(NULL, L"GameMedia\\enemy\\enemysandan.bmp", IMAGE_BITMAP, 120, 120, LR_LOADFROMFILE);
	g_hEnemyPlane9 = (HBITMAP)LoadImage(NULL, L"GameMedia\\enemy\\enemycargo2.bmp", IMAGE_BITMAP, 120, 120, LR_LOADFROMFILE);
	g_hEnemyPlane10 = (HBITMAP)LoadImage(NULL, L"GameMedia\\enemy\\enemyattack5.bmp", IMAGE_BITMAP, 120, 120, LR_LOADFROMFILE);
	g_hEnemyPlane11 = (HBITMAP)LoadImage(NULL, L"GameMedia\\enemy\\enemyplane1.bmp", IMAGE_BITMAP, 120, 200, LR_LOADFROMFILE);
	g_hEnemyPlane12 = (HBITMAP)LoadImage(NULL, L"GameMedia\\enemy\\enemyheli.bmp", IMAGE_BITMAP, 60, 60, LR_LOADFROMFILE);
	g_hEnemyPlaneBoss1 = (HBITMAP)LoadImage(NULL, L"GameMedia\\enemy\\enemyboss1.bmp", IMAGE_BITMAP, 300, 150, LR_LOADFROMFILE);
	g_hEnemyPlaneBoss2 = (HBITMAP)LoadImage(NULL, L"GameMedia\\enemy\\enemyboss2.bmp", IMAGE_BITMAP, 200, 120, LR_LOADFROMFILE);
	g_hEnemyZidan1 = (HBITMAP)LoadImage(NULL, L"GameMedia\\enemy\\enemyzidan1.bmp", IMAGE_BITMAP, 20, 20, LR_LOADFROMFILE);
	g_hEnemyMissile1 = (HBITMAP)LoadImage(NULL, L"GameMedia\\enemy\\enemymissile1.bmp", IMAGE_BITMAP, 20, 40, LR_LOADFROMFILE);
	g_hEnemyZidan2 = (HBITMAP)LoadImage(NULL, L"GameMedia\\enemy\\enemyzidan2.bmp", IMAGE_BITMAP, 20, 20, LR_LOADFROMFILE);
	g_hEnemyDazidan = (HBITMAP)LoadImage(NULL, L"GameMedia\\enemy\\enemyzidan3.bmp", IMAGE_BITMAP, 40, 40, LR_LOADFROMFILE);
	g_hEnemyMissile2 = (HBITMAP)LoadImage(NULL, L"GameMedia\\enemy\\enemymissile2.bmp", IMAGE_BITMAP, 20, 40, LR_LOADFROMFILE);
	g_hInfoBack = (HBITMAP)LoadImage(NULL, L"GameMedia\\background\\info.bmp", IMAGE_BITMAP, WINDOW_WIDTH, WINDOW_HEIGHT, LR_LOADFROMFILE);
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
	g_hQ[0] = (HBITMAP)LoadImage(NULL, L"GameMedia\\planeinfo\\q0.bmp", IMAGE_BITMAP, 500, 100, LR_LOADFROMFILE);
	g_hQ[1] = (HBITMAP)LoadImage(NULL, L"GameMedia\\planeinfo\\q1.bmp", IMAGE_BITMAP, 500, 100, LR_LOADFROMFILE);
	g_hQ[2] = (HBITMAP)LoadImage(NULL, L"GameMedia\\planeinfo\\q2.bmp", IMAGE_BITMAP, 500, 100, LR_LOADFROMFILE);
	g_hQ[3] = (HBITMAP)LoadImage(NULL, L"GameMedia\\planeinfo\\q3.bmp", IMAGE_BITMAP, 500, 100, LR_LOADFROMFILE);
	g_hE[0] = (HBITMAP)LoadImage(NULL, L"GameMedia\\planeinfo\\e0.bmp", IMAGE_BITMAP, 500, 100, LR_LOADFROMFILE);
	g_hE[1] = (HBITMAP)LoadImage(NULL, L"GameMedia\\planeinfo\\e1.bmp", IMAGE_BITMAP, 500, 100, LR_LOADFROMFILE);
	g_hE[2] = (HBITMAP)LoadImage(NULL, L"GameMedia\\planeinfo\\e2.bmp", IMAGE_BITMAP, 500, 100, LR_LOADFROMFILE);
	g_hE[3] = (HBITMAP)LoadImage(NULL, L"GameMedia\\planeinfo\\e3.bmp", IMAGE_BITMAP, 500, 100, LR_LOADFROMFILE);
}