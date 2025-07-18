#include "Area.h"

void NewBarrierAttribute::print(int x, int y)
{
	setfillcolor(RGB(128, 128, 128));
	fillrectangle(x, y, x + BLOCKSIZE*K, y + BLOCKSIZE*K);
}
void NewBarrierAttribute::out(int x, int y, int index, int map_index, ofstream& fout)
{
	fout << (int)0 << ' ' << x << ' ' << y << ' ' << index << ' ' << map_index << endl;
	printf("ar[%d]->add_Barrier(%d,%d,%d);\n", map_index, x, y, index);
}

NewArea::NewArea(int& x, int idx) :screen_x(x), index(idx) {
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			//barr[i][j] = new NewBarrierAttribute;
			barr[i][j] = NULL;
		}
	}
};
NewArea::~NewArea()
{
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			//barr[i][j] = new NewBarrierAttribute;
			if (barr[i][j] != NULL)
			{
				delete barr[i][j];
			}
		}
	}
}
void NewArea::add_Barrier(int x, int y) {
	if (barr[x][y])
	{
		delete barr[x][y];
	}
	barr[x][y] = new NewBarrierAttribute;
	barr[x][y]->change_flag();
};
void Map::add_Enermy(int x, int y, int atk, int hp) {
	if (barr[x][y])
	{
		delete[] barr[x][y];
	}
	barr[x][y] = new Enermy(atk, hp);
	barr[x][y]->change_flag();
};
void Map::add_Salesman(int x, int y, Salesman* vill) {
	barr[x][y] = vill;
	barr[x][y]->change_flag();
};

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
				barr[i][j]->print(i * BLOCKSIZE*K - screen_x*K + AREASIZE * index*K, j * BLOCKSIZE*K);
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
void Map::erasor(int x, int y)
{
	if (barr[x][y])
	{
		delete barr[x][y];
	}
	barr[x][y] = NULL;
}
void Map::out(int map_index, ofstream& fout)
{
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			//barr[i][j] = new NewBarrierAttribute;
			if (barr[i][j] != NULL)
			{
				barr[i][j]->out(i, j, index, map_index, fout);
			}
		}
	}
}
bool NewArea::Meet(int x, int y, HeroMoveAttribute* hero)
{
	int idx = (x + screen_x) / (int)AREASIZE;
	int x_block = ((x + screen_x) % (int)AREASIZE) / (int)BLOCKSIZE;
	int y_block = (y) / (int)BLOCKSIZE;
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
	:islink(false),len(length),screen_x(0),hero(nullptr)
{
	size = (length + AREASIZE - 1) / AREASIZE;
	for (int i = 0; i <= size; i++)
	{
		coll.push_back(new NewArea(screen_x, i));
	}
}
NewAreaList::~NewAreaList()
{
	for (int i = 0; i <= size; i++)
	{
		delete coll[i];
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
	if (index * AREASIZE + x * BLOCKSIZE >= len)
	{
		return;
	}
	coll[index]->add_Barrier(x, y);
}
void MapList::add_Enermy(int x, int y, int index, int atk , int hp)
{
	if (index * AREASIZE + x * BLOCKSIZE >= len)
	{
		return;
	}
	coll[index]->add_Enermy(x, y,atk,hp);
}
void MapList::add_Salesman(int x, int y, int index, Salesman* vill)
{
	if (index * AREASIZE + x * BLOCKSIZE >= len)
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
	x1 = AREASIZE * AreaIndex + block_x * BLOCKSIZE;
	y1 = block_y * BLOCKSIZE;
	x2 = x1 + BLOCKSIZE;
	y2 = y1 + BLOCKSIZE;
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