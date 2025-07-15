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
	int ShopEnter(Hero* hero);//�̵����
	int BUY_Enter(Hero* hero);//�������
	int SELL_Enter(Hero* hero);//���۽���(������)
	void add_product(Props*);//�̵���Ӳ�Ʒ
	void buyoperation(int, int,Hero*);//�жϵ����λ���Ƿ���
	void selloperation(int, int);//�жϵ����λ���Ƿ����(������)
	void product_draw(bool,Hero*);//������Ʒ����
	Props* choose(int,int,bool);
	void draw_Props(Props*,int,int);
	void restart();
protected:
	vector<Props*> p;//��Ʒ����
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