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
			if (barr[i][j]->getflag())
			{
				barr[i][j]->print(i * 40 - screen_x + AREASIZE * index, j * 40);
				//cout << index <<" "<< i << " " << j << '\n';
			}
		}
	}
}
bool NewArea::Meet(int x, int y, HeroMoveAttribute* hero)
{
	int idx = (x + screen_x) / AREASIZE;
	int x_block = ((x + screen_x) % AREASIZE) / 40;
	int y_block = (y) / 40;
	//cout << x_block << " " << y_block << endl;
	if (idx != index)
	{
		return false;
	}
	if (barr[x_block][y_block] == NULL)
	{
		//cout << "NULL" << endl;
		return false;
	}
	//return true;
	if (barr[x_block][y_block]->getflag())
	{
		cout << 'THis' << x << ' ' << y << '\n';
		barr[x_block][y_block]->interact(hero->get_body());
		cout << true;
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
	//res = res || coll[num - 1]->Meet(x, y);
	
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
	//if (!(hero->isLink()))
	//{
	//	hero->link(this);
	//}
};


/*
void BarrierAttribute::print() const
{
	fillrectangle(x1 - screen_x, y1, x2 - screen_x, y2);
}


int BarrierAttribute::get_x1() const
{
	return x1;
}
void BarrierList::add_Barrier(BarrierAttribute* temp)
{
	coll.push_back(temp);
}
void BarrierList::load()
{
	vector<BarrierAttribute*>::iterator pos;
	for (pos = coll.begin(); pos != coll.end(); pos++)
	{
		(*pos)->print();
	}
}
BarrierAttribute::BarrierAttribute(int n1, int n2, int n3, int n4, int& n5)
	:x1(n1), y1(n2), x2(n3), y2(n4), screen_x(n5)
{
	//未设计碰撞的经典物理坐标初始化
}
BarrierAttribute::BarrierAttribute(int blockx, int blocky, int index, int& n4)
	:block_x(blockx), block_y(blocky), AreaIndex(index), screen_x(n4)
{
	x1 = AREASIZE * AreaIndex + block_x * 40;
	y1 = block_y * 40;
	x2 = x1 + 40;
	y2 = y1 + 40;
}

AreaList::AreaList(int num)
{
	//构造函数
	for (int i = 0; i < num; i++)
	{
		coll.push_back(new Area);
	}
	size = num;
}

AreaList::~AreaList()
{
	//析构函数
	vector<Area*>::iterator pos;
	for (pos=coll.begin();pos!=coll.end(); pos++)
	{
		delete *pos;
	}
}

void AreaList::load(int num)
{
	if(num!=0)	coll[num-1]->load();
	coll[num]->load();
	if (num+1!=size)	coll[num+1]->load();
}
void Area::load()
{
	barr.load();
}

void AreaList::add_Barrier(BarrierAttribute* temp)
{
	//Index为Barrier区块的序列号
	int index = temp->get_x1() / AREASIZE;
	coll[index]->add_Barrier(temp);
}

void Area::add_Barrier(BarrierAttribute* temp)
{
	barr.add_Barrier(temp);
}
*/