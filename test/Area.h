#pragma once
#include "Charactor.h"
#include "Target.h"
#include "Macro.h"




class NewBarrierAttribute
	:public Block
{

public:
	NewBarrierAttribute() :Block(false) {};
	~NewBarrierAttribute(){}
	void print(int x, int y);
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
				barr[i][j] = NULL;
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
				//barr[i][j] = new NewBarrierAttribute;
				if (barr[i][j] != NULL)
				{
					delete barr[i][j];
				}
			}
		}
	}
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
	void add_Enermy(int x, int y, int index);
	void add_Salesman(int x, int y, int index,Salesman* vill);
	void load(int);
	bool Meet();
	bool isLink() { return islink; }
	int& get_screen_x() { return screen_x; };
	void link(HeroMoveAttribute*);
	int get_len() { return len; };
	void restart();
};