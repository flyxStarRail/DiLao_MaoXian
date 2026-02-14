#include "Area.h"

void NewBarrierAttribute::print(int x, int y)
{
	setfillcolor(RGB(128, 128, 128));
	fillrectangle(x, y, static_cast<int>(x + BLOCKSIZE * K), static_cast<int>(y + BLOCKSIZE * K));	
}

void NewArea::print()
{
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			if (barr[i][j] == nullptr)
			{
				continue;
			}
			if (barr[i][j]->getflag())
			{
				barr[i][j]->print(static_cast<int>(i * BLOCKSIZE * K - screen_x * K + AREASIZE * index * K), static_cast<int>(j * BLOCKSIZE * K));
			}
		}
	}
}

#ifdef MAP_EXPORT
void out(int x, int y, int index, int map_index, ofstream& fout);
void NewBarrierAttribute::out(int x, int y, int index, int map_index, ofstream& fout)
{
	fout << (int)0 << ' ' << x << ' ' << y << ' ' << index << ' ' << map_index << endl;
	//printf("ar[%d]->add_Barrier(%d,%d,%d);\n", map_index, x, y, index);
}
#endif // MAP_EXPORT
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
	if (y > 600 || y < 0) return false;

	int idx = (x + screen_x) / (int)AREASIZE;
	int x_block = ((x + screen_x) % (int)AREASIZE) / (int)BLOCKSIZE;
	int y_block = (y) / (int)BLOCKSIZE;
	if (x_block < 0 || x_block>14 || y_block < 0 || y_block>14)
	{
		throw("理论上不会出现该错误");
		return false;
	}
	if (idx != index)
	{
		throw("理论上不会出现该错误");
	}
	if (barr[x_block][y_block] == nullptr)
	{
		return false;
	}
	if (barr[x_block][y_block]->getflag())
	{
		hero->get_body()->interact(barr[x_block][y_block]);
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
	for (auto i : coll)
	{
		delete i;
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
void MapList::add_Enermy(int x, int y, int index)
{
	if (index * AREASIZE + x * BLOCKSIZE >= len)
	{
		return;
	}
	coll[index]->add_Enermy(x, y);
}
void MapList::add_Enermy(int x, int y, int index, int atk, int hp)
{
	if (index * AREASIZE + x * BLOCKSIZE >= len)
	{
		return;
	}
	coll[index]->add_Enermy(x, y, atk, hp);
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
	int l = screen_x / AREASIZE;
	int r = floor(static_cast<double>(screen_x+DRAW_WIDTH) / AREASIZE);
	for (int i = l; i <= r; i++)
	{
		coll[i]->print();
		if (i == coll.size())
		{
			throw("理论上不会出现该错误");
		}
	}
}


void NewAreaList::MeetPart(int& x, Direction && n) const
{
	if(n == Direction::right)
	{
		if (x % 40 < 12)
		{
			x -= x % 40;
		}
		return;
	}
	if (x % 40 > 27)
	{
		x -= x % 40;
		x += 40;
	}
}

// 0b00 -> 没遇到
// 0b01 -> x 复原
// 0b10 -> y 复原
int NewAreaList::Meet()
{

	int& x = hero->x;
	int& y = hero->y;

	int real_x = screen_x + x;
	int num_0 = (real_x + 2) / AREASIZE;
	int num_1 = (real_x + 38) / AREASIZE;
	bool lefttop = coll[num_0]->Meet(x+2,y+1,hero);
	bool righttop = coll[num_1]->Meet(x + 38, y+1, hero);
	bool leftbottom = coll[num_0]->Meet(x+2, y + 39, hero);
	bool rightbottom = coll[num_1]->Meet(x + 38, y + 39, hero);
	hero->body->release_interact();
	bool res = lefttop || leftbottom || rightbottom || righttop;
	if (!res) return 0;
	int inf = lefttop << 3 | righttop << 2 | leftbottom << 1 | rightbottom << 0;

	if (hero->isLeft && inf == 0b1000)
	{
		MeetPart(y, Direction::up);
		return 1;
	}
	if (hero->isLeft && inf == 0b0010)
	{
		MeetPart(y, Direction::down);
		return 1;
	}
	if (hero->isRight && inf == 0b0100)
	{
		MeetPart(y, Direction::up);
		return 1;
	}
	if (hero->isRight && inf == 0b001)
	{
		MeetPart(y, Direction::down);
		return 1;
	}
	
	if (hero->isUp && (inf == 0b1000) )
	{
		MeetPart(real_x,Direction::left);
		x = real_x - screen_x;
		return 2;
	}
	if (hero->isUp && (inf == 0b0100) )
	{
		MeetPart(real_x, Direction::right);
		x = real_x - screen_x;
		return 2;
	}
	if (hero->isDown && (inf == 0b0010) )
	{
		MeetPart(real_x, Direction::left);
		x = real_x - screen_x;
		return 2;
	}

	if (hero->isDown && (inf == 0b0001) )
	{
		MeetPart(real_x, Direction::right);
		x = real_x - screen_x;
		return 2;
	}

	return 3;
}


void NewAreaList::link(HeroMoveAttribute* temp) {
	hero = temp;
	islink = true;
};
