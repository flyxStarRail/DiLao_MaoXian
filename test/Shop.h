#pragma once
#include <graphics.h>
#pragma comment(lib, "MSIMG32.LIB")
#include <iostream>
#include <string>
#include <vector>
#include "Props.h"

#define ITEMSIZE 80
#define FONTSIZE 40
#define SIZE 600

using namespace std;

//class Item
//{
//	//此类用于存放物品的基本属性，图片（暂未装载）
//	//名称
//protected:
//	IMAGE* img;
//	std::string name;
//public:
//	Item() {};
//	Item(LPCSTR&);
//};
//
//class Product
//	:public Item
//{
//	//flag是否被购买
//	bool flag;
//public:
//	bool getflag() { return flag; }
//	void changeflag() { flag = !flag; };//操作购买和出售
//	Product() :flag(0) {};
//};

class Shop
{
public:
	int ShopEnter(Hero* hero);//商店入口
	int BUY_Enter(Hero* hero);//购买界面
	int SELL_Enter(Hero* hero);//出售界面
	void add_product(Props*);//商店添加产品
	void buyoperation(int, int);//判断点击的位置是否购买
	void selloperation(int, int);//判断点击的位置是否出售
	void product_draw(bool);//绘制商品界面
protected:
	vector<Props*> p;//商品向量
};



