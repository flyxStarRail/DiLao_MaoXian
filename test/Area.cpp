#include "Area.h"

void NewBarrierAttribute::print(int x, int y)
{
	setfillcolor(RGB(128, 128, 128));
	fillrectangle(x, y, x + 40, y + 40);
}

void NewArea::print()
{
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			if (barr[i][j] == NULL)
			{
				continue;
			}
			if (barr[i][j]->getflag())
			{
				barr[i][j]->print(i * 40 - screen_x + AREASIZE * index, j * 40);
			}
		}
	}
}
void Map::restart()
{
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			if (barr[i][j])
			{
				barr[i][j]->restart();
			}
		}
	}
}
bool NewArea::Meet(int x, int y, HeroMoveAttribute* hero)
{
	int idx = (x + screen_x) / AREASIZE;
	int x_block = ((x + screen_x) % AREASIZE) / 40;
	int y_block = (y) / 40;
	if (idx != index)
	{
		return false;
	}
	if (barr[x_block][y_block] == NULL)
	{
		return false;
	}
	if (barr[x_block][y_block]->getflag())
	{
		barr[x_block][y_block]->interact(hero->get_body());
		return true;
	}
	return false;
}

NewAreaList::NewAreaList(int length)
	:islink(false),len(length),screen_x(0)
{
	size = (length + AREASIZE - 1) / AREASIZE;
	for (int i = 0; i <= size; i++)
	{
		coll.push_back(new NewArea(screen_x, i));
	}
}

void MapList::restart()
{
	for (int i = 0; i <= size; i++)
	{
		coll[i]->restart();
	}
}
void NewAreaList::add_Barrier(int x, int y, int index)
{
	if (index * AREASIZE + x * 40 >= len)
	{
		return;
	}
	coll[index]->add_Barrier(x, y);
}
void MapList::add_Enermy(int x, int y, int index)
{
	if (index * AREASIZE + x * 40 >= len)
	{
		return;
	}
	coll[index]->add_Enermy(x, y);
}
void MapList::add_Salesman(int x, int y, int index, Salesman* vill)
{
	if (index * AREASIZE + x * 40 >= len)
	{
		return;
	}
	coll[index]->add_Salesman(x, y, vill);
}

void NewAreaList::load(int num)
{
	if (num != 0)	coll[num - 1]->print();
	if (num != size) coll[num]->print();
	if (num + 1 != size)	coll[num + 1]->print();
}

bool NewAreaList::Meet()
{
	//判断相邻三个区块是否有碰撞;
	int x = hero->get_x();
	int y = hero->get_y();
	int num = (screen_x) / AREASIZE;
	bool res = false;

	res = res || coll[num]->Meet(x, y, hero);
	res = res || coll[num]->Meet(x + 30, y, hero);
	res = res || coll[num]->Meet(x, y + 39, hero);
	res = res || coll[num]->Meet(x + 30, y + 39, hero);

	if (num != 0) {
		res = res || coll[num - 1]->Meet(x, y, hero);
		res = res || coll[num - 1]->Meet(x + 30, y, hero);
		res = res || coll[num - 1]->Meet(x, y + 39, hero);
		res = res || coll[num - 1]->Meet(x + 30, y + 39, hero);
	}
	
	if (num + 1 != size)
	{
		res = res || coll[num + 1]->Meet(x, y, hero);
		res = res || coll[num + 1]->Meet(x + 30, y, hero);
		res = res || coll[num + 1]->Meet(x, y + 39, hero);
		res = res || coll[num + 1]->Meet(x + 30, y + 39, hero);
	}
	return res;
}
void NewAreaList::link(HeroMoveAttribute* temp) {
	hero = temp;
	islink = true;
};