#pragma once
#include "Charactor.h"
#include "Target.h"
//#include "Area.h"
#define AREASIZE 600 //定义区块大小500




class NewBarrierAttribute
	:public Block
{

public:
	NewBarrierAttribute() :Block(false) {};
	void print(int x, int y);
	bool interact(Hero* hero) { return false; };
	//void change_flag() { flag = !flag; };
	//bool getflag() { return flag; };
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
				barr[i][j] = new NewBarrierAttribute;
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
	void add_Enermy(int x, int y) {
		if (barr[x][y])
		{
			delete barr[x][y];
		}
		barr[x][y] = new Enermy(100,100);
		barr[x][y]->change_flag();
	};
	void add_Salesman(int x, int y,Salesman* vill) {
		if (barr[x][y])
		{
			delete barr[x][y];
		}
		barr[x][y] = vill;
		barr[x][y]-> change_flag();
	};
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
	void add_Barrier(int x,int y,int index);
	void add_Enermy(int x, int y, int index);
	void add_Salesman(int x, int y, int index,Salesman* vill);
	void load(int);
	bool Meet();
	bool isLink() { return islink; }
	int& get_screen_x() { return screen_x; };
	void link(HeroMoveAttribute*);
	int get_len() { return len; };
	//int& get_screen_x() { return screen_x; };
};







/*
class BarrierAttribute
{
protected:
	int x1;
	int y1;
	int x2;
	int y2;
	int block_x;
	int block_y;
	int AreaIndex;
	int& screen_x;//绑定的坐标系,用于将物理坐标转换为屏幕坐标
public:
	BarrierAttribute(int, int, int, int, int&);
	BarrierAttribute(int, int, int,int&);
	void print() const;
	int get_x1() const;
};

class BarrierList
{
protected:
	vector<BarrierAttribute*> coll;
public:
	void load();//用来绘制障碍物
	void add_Barrier(BarrierAttribute* temp);
};

class Area
{
protected:
	BarrierList barr;
	//EnermyList
public:
	void add_Barrier(BarrierAttribute*);
	void load();
};

class AreaList
{
protected:
	vector<Area*> coll;
	int size;
public:
	AreaList(int);
	~AreaList();
	void add_Barrier(BarrierAttribute*);
	void load(int);
};
*/