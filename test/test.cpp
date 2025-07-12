// test.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include "Charactor.h"
#include "Shop.h"
#include "Props.h"
#include "Area.h"
#include "Target.h"
#include "Enter.h"
//void Areainit(AreaList& a,int& x);
IMAGE* Salesman::img = new IMAGE;
IMAGE* Enermy::img = new IMAGE;
int main() {
	//初始化 商人和敌人的贴图
	Salesman::img_init();
	Enermy::img_init();
	//新增入口
	initgraph(600, 600);
restart:
	//游戏入口
	Enter::enter();

	int x = 0; //screen_x
	//添加区块链
	NewAreaList ar(x,5000);
	//添加障碍物
	for (int i = 0; i < 100; i++)
	{
		ar.add_Barrier(rand()%15, rand() % 15, rand() % 9);
	}
	//添加敌人
	for (int i = 0; i < 20; i++)
	{
		ar.add_Enermy(rand() % 15, rand() % 15, rand() % 9);
	}
	//添加商店
	Shop a;
	//给商店添加产品
	for (int i = 0; i < 6; i++)
	{
		Props* temp = new Weapon(1,100);
		char str[20];
		IMAGE* img = new IMAGE;
		sprintf_s(str, "equip\\prop (%d).png", i + 1);
		loadimage(img, _T(str), 80, 80);
		temp->set_img(img);
		a.add_product(temp);
	}
	//添加商人
	Salesman vill;
	//给商人绑定商店
	vill.link(&a);
	//在区块链中添加商人
	ar.add_Salesman(10, 10, 0, &vill);
	//添加主角本体、运动属性，并进行绑定
	Hero body(10,10);
	HeroMoveAttribute * hero = new HeroMoveAttribute(0,0);
	hero->link(&ar);
	hero->set_body(&body);
	setbkmode(TRANSPARENT);
	//加载背景图片
	IMAGE img;
	loadimage(&img, _T("img\\background.png"), 5000, 600,false);
	//下面是主游戏流程
	bool running = true;
	ExMessage msg;
	//setfillcolor(RGB(128, 128, 128));
	BeginBatchDraw();

	while (running)
	{
		DWORD beginTime = GetTickCount();			// 记录循环开始时间

		// 消息处理
		while (peekmessage(&msg))
		{
			hero->judge(msg, running, a);

		}
		cleardevice();								// 清除屏幕
		putimage(-x, 0, &img); //绘制背景图片
		hero->move();
		ar.load(x/AREASIZE);
		hero->put_solided();
		body.print();
		if (body.get_is_dead())
		{
			cleardevice();
			settextstyle(80, 50,"宋体");
			outtextxy(150, 300, _T("FAILED"));
			FlushBatchDraw();
			Sleep(1000);
			Resize(NULL,600, 600);
			goto restart;
		}
		

		FlushBatchDraw();
		// 帧延时
		DWORD endTime = GetTickCount();				// 记录循环结束时间
		DWORD elapsedTime = endTime - beginTime;	// 计算循环耗时
		if (elapsedTime < 1000 / 120)				// 按每秒60帧进行补时
			Sleep(1000 / 120 - elapsedTime);
	}

	EndBatchDraw();
	closegraph();
	return 0;
}
