// test.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include "Charactor.h"
#include "Shop.h"
#include "Props.h"
#include "Area.h"
#include "Target.h"
#include "Enter.h"

#define MAP_NUM 2

IMAGE* Salesman::img = new IMAGE;
IMAGE* Enermy::img = new IMAGE;

int main() {
	//初始化 商人和敌人的贴图
	Salesman::img_init();
	Enermy::img_init();
	//新增入口
	initgraph(600, 600);
	int length = 1200;
	//添加区块链
	//int map_num = 2;
	NewAreaList* ar_l[MAP_NUM] = { new MapList(length),new MapList(length) };
	int index = 0;
	NewAreaList * ar = ar_l[0];
	//添加障碍物
	for (int i = 0; i < 100; i++)
	{
		ar->add_Barrier(rand()%15, rand() % 15, rand() % 9);
	}

	for (int i = 0; i < 100; i++)
	{
		ar_l[1]->add_Barrier(rand() % 15, rand() % 15, rand() % 9);
	}

	//添加敌人
	for (int i = 0; i < 20; i++)
	{
		ar->add_Enermy(rand() % 15, rand() % 15, rand() % 9);
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
	ar->add_Salesman(10, 10, 0, &vill);

restart:
	//游戏入口
	Enter::enter();

	int* x = &(ar->get_screen_x());

	//添加主角本体、运动属性，并进行绑定
	Hero body(10,10);
	HeroMoveAttribute * hero = new HeroMoveAttribute(0,0);
	hero->link(ar);
	hero->set_body(&body);

	setbkmode(TRANSPARENT);
	//加载背景图片
	IMAGE img;
	loadimage(&img, _T("img\\background.png"), max(5000,length), 600,true);
	Resize(&img, length+50, 600);
	SetWorkingImage(&img);
	setlinecolor(RED);
	setfillcolor(BLUE);
	////填充终点后的场景
	fillrectangle(length, 0, length + 50, 600);
	SetWorkingImage(NULL);

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
		putimage(-*x, 0, &img); //绘制背景图片
		hero->move();
		ar->load(*x /AREASIZE);
		hero->put_solided();
		body.print();
		if (body.get_is_dead())
		{
			Failed::draw();
			FlushBatchDraw();
			Sleep(1000);
			*x = 0;
			goto restart;
		}
		if (body.win(length-10))
		{
			index++;
			if (index == MAP_NUM)
			{
				Win::enter();
				index = 0;
				ar = ar_l[index];
				hero->link(ar);
				hero->attrclear();
				hero->position_clear();
				*x = 0;
				x = &ar->get_screen_x();
				goto restart;
			}
			ar = ar_l[index];
			hero->link(ar);
			hero->attrclear();
			hero->position_clear();
			*x = 0;
			x = & ar->get_screen_x();
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
