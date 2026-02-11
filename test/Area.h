#pragma once
#include "Charactor.h"
#include "Target.h"
#include "Macro.h"
#include <fstream>

struct loc
{
	int x;
	int y;
	loc(int a, int b) :x(a), y(b) {};
};


class NewBarrierAttribute
	:public Block
{

public:
	NewBarrierAttribute() :Block(false) {};
	~NewBarrierAttribute(){}
	void print(int x, int y);
#ifdef MAP_EXPORT
	void out(int x, int y, int index, int map_index, ofstream& fout);
#endif // MAP_EXPORT
	bool interact(Hero* hero) { return false; };
};

class NewArea
{
protected:
	Block * barr[15][15];
	int& screen_x;
	int index;
public:
	bool Meet(int x,int y,HeroMoveAttribute* hero);
	void print();
	NewArea(int& x,int idx) :screen_x(x),index(idx) {
		for (int i = 0; i < 15; i++)
		{
			for (int j = 0; j < 15; j++)
			{
				barr[i][j] = nullptr;
			}
		}
	};
	void add_Barrier(int x, int y) { 
		if (barr[x][y])
		{
			delete barr[x][y];
		}
		barr[x][y] = new NewBarrierAttribute;
		barr[x][y]->change_flag(); };
	void add_Enermy(int x, int y,int atk = 100,int hp = 100) {
		if (barr[x][y])
		{
			delete barr[x][y];
		}
		barr[x][y] = new Enermy(atk,hp);
		barr[x][y]->change_flag();
	};
	void add_Salesman(int x, int y,Salesman* vill) {
		barr[x][y] = vill;
		barr[x][y]-> change_flag();
	};
	void restart();
	~NewArea()
	{
		for (int i = 0; i < 15; i++)
		{
			for (int j = 0; j < 15; j++)
			{
				if (barr[i][j] != nullptr)
				{
					delete barr[i][j];
				}
			}
		}
	}
#ifdef ERASOR
	void erasor(int x, int y)
	{
		if (barr[x][y]!=nullptr)
		{
			delete barr[x][y];
		}
		barr[x][y] = nullptr;
	}
#endif
#ifdef MAP_EXPORT
	void out(int map_index, ofstream& fout) {
		for (int i = 0; i < 15; i++)
		{
			for (int j = 0; j < 15; j++)
			{
				if (barr[i][j] != NULL)
				{
					barr[i][j]->out(i, j, index, map_index, fout);
				}
			}
		}
	}
#endif // MAP_EXPORT

};


class NewAreaList
{
protected:
	vector<NewArea*> coll;
	int size;
	int screen_x;
	int len;
	HeroMoveAttribute * hero;
	bool islink;

public:
	NewAreaList(int length);
	~NewAreaList()		;
	void add_Barrier(int x,int y,int index);
	void add_Enermy(int x, int y, int index);
	void add_Enermy(int x, int y, int index, int atk, int hp);
	void add_Salesman(int x, int y, int index,Salesman* vill);
	void load(int);
	void MeetPart(int& x) const;
	int Meet();
	bool isLink() { return islink; }
	int& get_screen_x() { return screen_x; };
	void link(HeroMoveAttribute*);
	int get_len() { return len; };
	void restart();
#ifdef ERASOR
	void erasor(int x, int y, int index) {
		if (index * AREASIZE + x * BLOCKSIZE >= len)
		{
			return;
		}
		coll[index]->erasor(x, y);
	};
#endif
#ifdef MAP_EXPORT
	void out(int map_index, ofstream& fout)
	{
		for (int i = 0; i <= size; i++)
		{
			coll[i]->out(map_index, fout);
		}
	}
#endif // MAP_EXPORT


};