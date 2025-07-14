#include "Shop.h"
#include "Target.h"

using namespace std;

void Shop::add_product(Props* temp)
{
	//此函数为给Shop类添加产品
	if (temp==NULL)
	{
		//如果传参为空指针则添加空对象
		//还没有写析构函数
		Weapon temp(10,100);
		temp.set_img(new IMAGE);
		p.push_back(&temp);
	}
	else
	{
		p.push_back(temp);
	}
}
static int getoperation(int x, int y)
{
	//此函数用于返回给定坐标参数对应位置得到的结果
	if (x > SIZE / 2 - FONTSIZE * 2 && x < SIZE / 2 + FONTSIZE * 2)
	{
		if (y > 120 && y < 120 + FONTSIZE) { return 1;/*BUY*/ }
		if (y > 220 && y < 220 + FONTSIZE) { return 2;/*SELL*/ }
		if (y > 320 && y < 320 + FONTSIZE) { return 0;/*EXIT*/ }
	}
	return 4;
}
void Shop::buyoperation(int x, int y,Hero * hero)
{
	//此函数表示购买界面中，判断是否购买并进行操作的函数
	//可封装成 返回值为 int 的函数来传递购买的装备的下标
	//或 返回值为 Product* 的函数来传递点击到的装备的指针
	int index = 1;
	int index_c = 1;
	int item_x1, item_y1;
	int item_x2, item_y2;
	for (int i = 0; i < min(p.size(), 10); i++)
	{
		if (p[i]->getflag() == 0)
		{
			item_x1 = SIZE / 2 - ITEMSIZE * 0.5 - 300 + 100 * index;
			item_y1 = 100 * index_c;
			item_x2 = item_x1 + ITEMSIZE;
			item_y2 = item_y1 + ITEMSIZE;
			if (x > item_x1 && x<item_x2 && y>item_y1 && y < item_y2)
			{
				//P[i]为购买的装备
				//此处表示判定是否为点击到的装备。
				//if()
				if(p[i]->is_vailed(hero))
				{
					p[i]->changeflag();
					p[i]->function(*hero);
					p[i]->buy(hero);
				}
				//若购买装备，运行到此处停止
				return;
			}
			index++;
			if (index == 6)
			{
				index = 1;
				index_c++;
			}
		}
	}
	//如果没有点击到装备，则会运行到这里
}



void Shop::selloperation(int x, int y)
{
	//此函数表示出售界面中，判断是否出售并进行操作的函数
	//可封装成 返回值为 int 的函数来传递出售的装备的下标
	//或 返回值为 Product* 的函数来传递点击到的装备的指针
	int index = 1;
	int index_c = 1;
	int item_x1, item_y1;
	int item_x2, item_y2;
	for (int i = 0; i < min(p.size(), 10); i++)
	{
		if (p[i]->getflag())
		{

			item_x1 = SIZE / 2 - ITEMSIZE * 0.5 - 300 + 100 * index;
			item_y1 = 100 * index_c;
			item_x2 = item_x1 + ITEMSIZE;
			item_y2 = item_y1 + ITEMSIZE;
			if (x > item_x1 && x<item_x2 && y>item_y1 && y < item_y2)
			{
				//P[i]为出售的装备
				p[i]->changeflag();
				return;
			}
			index++;
			if (index == 6)
			{
				index = 1;
				index_c++;
			}
		}
	}
}
void Shop::product_draw(bool product_flag,Hero* hero)
{
	cleardevice();
	char temp[20];
	sprintf_s(temp, "Gold:%d",hero->getGold());
	settextstyle(10, 10, "黑体");
	settextcolor(WHITE);
	outtextxy(10, 10, temp);
	//此函数为绘制商店的物品

	int index = 1;
	int index_c = 1;
	for (int i = 0; i < min(p.size(), 10); i++)
	{

		if (p[i]->getflag()==product_flag)
		{
			//setbkcolor(RGB(128, 128, 128));
			setfillcolor(RGB(128, 128, 128));
			fillrectangle(SIZE / 2 - ITEMSIZE * 0.5 - 300 + 100 * index, 100 * index_c, SIZE / 2 - ITEMSIZE * 0.5 - 300 + 100 * index + 80, 100 * index_c + ITEMSIZE);
			putimage_alpha(SIZE / 2 - ITEMSIZE * 0.5 - 300 + 100 * index, 100 * index_c, p[i]->getimage());
			//setbkcolor(BLACK);
			index++;
			if (index == 6)
			{
				index = 1;
				index_c++;
			}
		}
	}
	settextstyle(40, 40, "Courier");
	outtextxy(SIZE / 2 - FONTSIZE * 2, 320, "EXIT");
	//FlushBatchDraw();
}

int Shop::ShopEnter(Hero* hero)
{
	//此函数为商店的进入主界面
	//x,y用来存储鼠标点击的坐标
	int x = 0;					
	int y = 0;	
	//change
	Resize(NULL, 600, 500);
	bool running = true;
	ExMessage msg;
	while (running) {
		DWORD beginTime = GetTickCount();
		while (peekmessage(&msg)) {
			if (msg.message == WM_LBUTTONDOWN) 
				//点击时触发
			{
				x = msg.x;
				y = msg.y;
				//注释掉的内容为测试时使用，来显示得到的x y
				int flag = getoperation(x, y);
				//flag 用来 判断 得到的 接下来该做什么
				switch (flag)
				{
				case 0:
					hero->clearattr();
					//change
					Resize(NULL,600, 700);
					return 0;
				case 1:
					BUY_Enter(hero);
					break;
				case 2:
					//SELL_Enter(hero);
					cout<<"Enter Sale";
					SellItem::New_Sell_Enter(hero);
					break;
				default:
					break;
				}

			}
		}
		// 绘图
		cleardevice();					
		settextstyle(40, 40, "Courier");
		outtextxy(SIZE / 2 - FONTSIZE * 2, 20, "SHOP");
		outtextxy(SIZE / 2 - FONTSIZE * 1.5, 120, "BUY");
		outtextxy(SIZE / 2 - FONTSIZE * 2, 220, "SELL");
		outtextxy(SIZE / 2 - FONTSIZE * 2, 320, "EXIT");

		FlushBatchDraw();				
		DWORD endTime = GetTickCount();				// 记录循环结束时间
		DWORD elapsedTime = endTime - beginTime;	// 计算循环耗时
		if (elapsedTime < 1000 / 60)				// 按每秒60帧进行补时
			Sleep(1000 / 60 - elapsedTime);
	}
	return 0;
}

int Shop::SELL_Enter(Hero* hero)
{
	int x = 0;			
	int y = 0;				
	bool running = true;
	ExMessage msg;
	FlushBatchDraw();
	Props* Prop_choose = NULL;

	while (running) {
		// 消息处理	
		DWORD beginTime = GetTickCount();	
		while (peekmessage(&msg)) {
			if (msg.message == WM_MOUSEMOVE)
			{
				x = msg.x;
				y = msg.y;
				Prop_choose = choose(x, y, true);
			}
			if (msg.message == WM_LBUTTONDOWN) {
				x = msg.x;
				y = msg.y;
				selloperation(x, y);
				int flag = getoperation(x, y);
				switch (flag)
				{
				case 0:
					return 0;
				default:
					break;
				}
			}

		}
		// 绘图
		product_draw(1,hero);
		if (Prop_choose)		draw_Props(Prop_choose, x, y);
		FlushBatchDraw();
		DWORD endTime = GetTickCount();				// 记录循环结束时间
		DWORD elapsedTime = endTime - beginTime;	// 计算循环耗时
		if (elapsedTime < 1000 / 60)				// 按每秒60帧进行补时
			Sleep(1000 / 60 - elapsedTime);
						
	}
	return 0;
}

int Shop::BUY_Enter(Hero* hero)
{
	//进入界面
	int x = 0;						
	int y = 0;						
	bool running = true;
	ExMessage msg;
	Props* Prop_choose = NULL;

	FlushBatchDraw();

	while (running) {
		DWORD beginTime = GetTickCount();
		while (peekmessage(&msg)) {
			if (msg.message == WM_MOUSEMOVE)
			{
				x = msg.x;
				y = msg.y;
				Prop_choose = choose(x,y,false);
			}
			if (msg.message == WM_LBUTTONDOWN) //鼠标左键单击时
			{
				x = msg.x;
				y = msg.y;

				buyoperation(x, y,hero);//判断是否购买
				int flag = getoperation(x, y);//判断是否退出
				switch (flag)
				{
				case 0:
					return 0;//退出
				default:
					break;
				}

			}

		}
		// 绘图
		product_draw(0,hero);
		if(Prop_choose)		draw_Props(Prop_choose,x,y);
		settextstyle(40, 40, "Courier");
		outtextxy(SIZE / 2 - FONTSIZE * 2, 320, "EXIT");
		FlushBatchDraw();				// 刷新批量绘图
		DWORD endTime = GetTickCount();				// 记录循环结束时间
		DWORD elapsedTime = endTime - beginTime;	// 计算循环耗时
		if (elapsedTime < 1000 / 60)				// 按每秒60帧进行补时
			Sleep(1000 / 60 - elapsedTime);
	}
	return 0;
}
//
//Item::Item(LPCSTR& temp)
//{
//	//loadimage(img, temp, ITEMSIZE, ITEMSIZE,false);
//}

Props* Shop::choose(int x, int y, bool flag)
{
	int index = 1;
	int index_c = 1;
	int item_x1, item_y1;
	int item_x2, item_y2;
	for (int i = 0; i < min(p.size(), 10); i++)
	{
		if (p[i]->getflag()==flag)
		{

			item_x1 = SIZE / 2 - ITEMSIZE * 0.5 - 300 + 100 * index;
			item_y1 = 100 * index_c;
			item_x2 = item_x1 + ITEMSIZE;
			item_y2 = item_y1 + ITEMSIZE;
			if (x > item_x1 && x<item_x2 && y>item_y1 && y < item_y2)
			{
				//P[i]为出售的装备
				//p[i]->changeflag();
				return p[i];
			}
			index++;
			if (index == 6)
			{
				index = 1;
				index_c++;
			}
		}
	}
	return NULL;
}

void Shop::draw_Props(Props* temp,int x,int y)
{
	x = 200;
	y = 10;
	setbkcolor(RGB(100, 100, 100));
	settextcolor(WHITE);
	settextstyle(10, 10, "黑体");
	char t[50];
	temp->getInfo(t, 50);
	outtextxy(x, y, t);
	sprintf_s(t, "price:%d", (temp->getPrice()));
	outtextxy(x, y+10, t);
	setbkcolor(BLACK);
}

void Shop::restart()
{
	for (int i = 0; i < p.size(); i++)
	{
		if (p[i]->getflag())
		{
			p[i]->changeflag();
		}
	}
}

void SellItem::New_Sell_Enter(Hero* hero)
{
	int x = 0;
	int y = 0;
	bool running = true;
	ExMessage msg;
	FlushBatchDraw();
	int SellItem_choose = -1;

	while (running) {
		// 消息处理	
		DWORD beginTime = GetTickCount();
		while (peekmessage(&msg)) {
			if (msg.message == WM_MOUSEMOVE)
			{
				x = msg.x;
				y = msg.y;
				SellItem_choose = choose(x, y);
			}
			if (msg.message == WM_LBUTTONDOWN) {
				x = msg.x;
				y = msg.y;
				SellItem_choose = choose(x, y);
				selloperation(SellItem_choose,hero);
				int flag = getoperation(x, y);
				switch (flag)
				{
				case 0:
					return ;
				default:
					break;
				}
			}
		}
		
		SellItem_draw(hero);
		if (SellItem_choose != -1)		choose_draw(SellItem_choose,x,y);
		FlushBatchDraw();
		DWORD endTime = GetTickCount();				// 记录循环结束时间
		DWORD elapsedTime = endTime - beginTime;	// 计算循环耗时
		if (elapsedTime < 1000 / 60)				// 按每秒60帧进行补时
			Sleep(1000 / 60 - elapsedTime);

	}
	return ;
}

void SellItem::choose_draw(int index,int x,int y)
{
	x = 200;
	y = 10;
	setbkcolor(RGB(100, 100, 100));
	settextcolor(WHITE);
	settextstyle(10, 10, "黑体");
	char t[20];
	sprintf_s(t, "price:%d", price[index]);
	outtextxy(x, y, t);
	sprintf_s(t, "Num:%d", flag[index]);
	outtextxy(x, y + 10, t);

	setbkcolor(BLACK);
}

int SellItem::choose(int x, int y)
{
	int index = 1;
	int index_c = 1;
	int item_x1, item_y1;
	int item_x2, item_y2;
	for (int i = 0; i < 10; i++)
	{
		if (SellItem::flag[i])
		{

			item_x1 = SIZE / 2 - ITEMSIZE * 0.5 - 300 + 100 * index;
			item_y1 = 100 * index_c;
			item_x2 = item_x1 + ITEMSIZE;
			item_y2 = item_y1 + ITEMSIZE;
			if (x > item_x1 && x<item_x2 && y>item_y1 && y < item_y2)
			{
				return i;
			}
			index++;
			if (index == 6)
			{
				index = 1;
				index_c++;
			}
		}
	}
	return -1;
}

void SellItem::selloperation(int index,Hero* hero)
{
	flag[index] --;
	hero->setGold(hero->getGold() + price[index]);
}
void SellItem::add(int index)
{
	flag[index]++;
}
void SellItem::SellItem_draw( Hero* hero)
{
	cleardevice();
	char temp[20];
	sprintf_s(temp, "Gold:%d", hero->getGold());
	settextstyle(10, 10, "黑体");
	settextcolor(WHITE);
	outtextxy(10, 10, temp);
	//此函数为绘制商店的物品

	int index = 1;
	int index_c = 1;
	for (int i = 0; i <  10; i++)
	{

		if (flag[i])
		{
			//setbkcolor(RGB(128, 128, 128));
			setfillcolor(RGB(128, 128, 128));
			fillrectangle(SIZE / 2 - ITEMSIZE * 0.5 - 300 + 100 * index, 100 * index_c, SIZE / 2 - ITEMSIZE * 0.5 - 300 + 100 * index + 80, 100 * index_c + ITEMSIZE);
			//if(i!=9)
			//cout << img[9] <<endl;
			 //putimage(SIZE / 2 - ITEMSIZE * 0.5 - 300 + 100 * index, 100 * index_c, img[i]);
			//if (img[i]!=NULL)

			putimage_alpha(SIZE / 2 - ITEMSIZE * 0.5 - 300 + 100 * index, 100 * index_c, img[i]);
			//setbkcolor(BLACK);
			index++;
			if (index == 6)
			{
				index = 1;
				index_c++;
			}
		}
	}
	settextstyle(40, 40, "Courier");
	outtextxy(SIZE / 2 - FONTSIZE * 2, 320, "EXIT");
	//FlushBatchDraw();
}

void SellItem::init()
{
	char temp[50];
	for (int i = 0; i < SELLITEM_SIZE; i++)
	{
		flag[i] = 1;
		img[i] = new IMAGE;
		sprintf_s(temp,"SellItem\\sellitem (%d).png",i);
		loadimage(img[i], _T(temp), 80, 80, false);
	}
}

void SellItem::restart()
{
	for (int i = 0; i < SELLITEM_SIZE; i++)
	{
		flag[i] = 0;
	}
}