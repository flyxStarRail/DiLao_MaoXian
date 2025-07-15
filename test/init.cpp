#include "init.h"


//body,hero,vill,a
void init_Map_List(NewAreaList* ar_l[MAP_NUM])
{
	//添加障碍物
	for (int i = 0; i < 100; i++)
	{
		ar_l[0]->add_Barrier(rand() % 15, rand() % 15, rand() % 9);
	}

	for (int i = 0; i < 100; i++)
	{
		ar_l[1]->add_Barrier(rand() % 15, rand() % 15, rand() % 9);
	}

	//添加敌人
	for (int i = 0; i < 20; i++)
	{
		ar_l[0]->add_Enermy(rand() % 15, rand() % 15, rand() % 9);
	}
}

void load_background(IMAGE& img, int length)
{//加载背景图片
	loadimage(&img, _T("img\\background.png"), max(5000, length), 600, true);
	Resize(&img, length + 50, 600);
	SetWorkingImage(&img);
	setlinecolor(RED);
	setfillcolor(BLUE);
	////填充终点后的场景
	fillrectangle(length, 0, length + 50, 600);
	SetWorkingImage(NULL);
}

void next_map(NewAreaList*& ar, NewAreaList* ar_l[], int& index, HeroMoveAttribute* hero, int*& x)
{
	ar = ar_l[index];
	hero->link(ar);
	hero->attrclear();
	hero->position_clear();
	*x = 0;
	x = &ar->get_screen_x();

}

void restart(NewAreaList*& ar, NewAreaList* ar_l[], int& index, HeroMoveAttribute* hero, int*& x)
{
	index = 0;
	ar = ar_l[index];
	hero->link(ar);
	hero->attrclear();
	hero->position_clear();
	*x = 0;
	x = &ar->get_screen_x();
	for (int i = 0; i < MAP_NUM; i++)
	{
		ar_l[i]->restart();
	}
	SellItem::restart();
}