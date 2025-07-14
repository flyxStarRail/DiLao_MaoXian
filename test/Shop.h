#pragma once
#include <graphics.h>
#pragma comment(lib, "MSIMG32.LIB")
#include <iostream>
#include <string>
#include <vector>
#include "Props.h"
#define SELLITEM_SIZE 11
#define ITEMSIZE 80
#define FONTSIZE 40
#define SIZE 600

using namespace std;

class Shop
{
public:
	int ShopEnter(Hero* hero);//商店入口
	int BUY_Enter(Hero* hero);//购买界面
	int SELL_Enter(Hero* hero);//出售界面(已弃用)
	void add_product(Props*);//商店添加产品
	void buyoperation(int, int,Hero*);//判断点击的位置是否购买
	void selloperation(int, int);//判断点击的位置是否出售(已弃用)
	void product_draw(bool,Hero*);//绘制商品界面
	Props* choose(int,int,bool);
	void draw_Props(Props*,int,int);
	void restart();
protected:
	vector<Props*> p;//商品向量
};

class SellItem
{
private:
	static int price[SELLITEM_SIZE];
	static IMAGE* img[SELLITEM_SIZE];
	static int flag[SELLITEM_SIZE];
public:
	static void init();
	static int choose(int, int);
	static void New_Sell_Enter(Hero* hero);
	static void SellItem_draw(Hero*);
	static void selloperation(int, Hero*);
	static void add(int);
	static void choose_draw(int, int, int);
	static void restart();
};