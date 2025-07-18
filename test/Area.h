#pragma once
#include "Charactor.h"
#include "Target.h"
#include "Macro.h"
#include "fstream"

class NewBarrierAttribute
	:public Block
{

public:
	NewBarrierAttribute() :Block(false) {};
	~NewBarrierAttribute() {};
	void print(int x, int y);
	bool getflag() { return flag; };
	void change_flag() { flag = !flag; };
	void out(int x, int y, int index, int map_index, ofstream& fout);
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
	NewArea(int& x, int idx);
	void add_Barrier(int x, int y);
	void add_Enermy(int x, int y, int atk, int hp);
	void add_Salesman(int x, int y, Salesman* vill);
	void restart();
	~NewArea();
	void erasor(int x, int y);
	void out(int map_index, ofstream& fout);
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
	~NewAreaList();
	void add_Barrier(int x,int y,int index);
	void add_Enermy(int x, int y, int index, int atk = 100, int hp = 100);
	void add_Salesman(int x, int y, int index,Salesman* vill);
	void load(int);
	bool Meet();
	bool isLink() { return islink; }
	int& get_screen_x() { return screen_x; };
	void link(HeroMoveAttribute*);
	int get_len() { return len; };
	void restart();
	void erasor(int x, int y, int index) {
		if (index * AREASIZE + x * BLOCKSIZE >= len)
		{
			return;
		}
		coll[index]->erasor(x, y);
	};
	void out(int map_index, ofstream& fout)
	{
		for (int i = 0; i <= size; i++)
		{
			coll[i]->out(map_index,fout);
		}
	}
};