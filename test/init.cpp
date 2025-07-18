#include "init.h"


//body,hero,vill,a
void init_Map_List(vector<NewAreaList*>& ar,int & length,int & _map_num)
{
	ifstream map_init ("map\\map.txt");
	int map_num;
	int len;
	map_init >> map_num >> len;
	_map_num = map_num;
	length = len;
	for (int i = 0; i < map_num; i++)
	{
		ar.push_back(new NewAreaList(len));
	}
	int n;
	int x;
	int y;
	int index;
	int map_index;
	int atk;
	int hp;
	map_init >> n;
	while (n != -1)
	{
		map_init >> x >> y >> index >> map_index;
		switch (n)
		{
		case 0:
			ar[map_index]->add_Barrier(x,y,index);
			cout << "ar[" << map_index << "]->add_Barrier(" << x<<"," << y<<"," <<index<<"); \n";
			break;
		case 1:
			map_init >> atk >> hp;
			ar[map_index]->add_Enermy(x, y, index,atk,hp);
			cout << "ar[" << map_index << "]->add_Enermy(" << x << "," << y << "," << index << "); \n";
			break;
		}
		map_init >> n;
	}
}

void load_background(IMAGE& img, int length)
{//º”‘ÿ±≥æ∞Õº∆¨
	loadimage(&img, _T("img\\background.png"), max(5000, length*K), SCREENSIZE, true);
	Resize(&img, length*K + 50*K, SCREENSIZE);
	SetWorkingImage(&img);
	setlinecolor(RED);
	setfillcolor(BLUE);
	////ÃÓ≥‰÷’µ„∫Ûµƒ≥°æ∞
	fillrectangle(length*K, 0, length*K + 50*K, SCREENSIZE);
	SetWorkingImage(NULL);
}

void next_map(NewAreaList*& ar, vector<NewAreaList*>& ar_l, int& index, HeroMoveAttribute* hero, int*& x)
{
	ar = ar_l[index];
	hero->link(ar);
	hero->attrclear();
	hero->position_clear();
	*x = 0;
	x = &ar->get_screen_x();

}

void restart(NewAreaList*& ar, vector<NewAreaList*>& ar_l, int& index, HeroMoveAttribute* hero, int*& x)
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