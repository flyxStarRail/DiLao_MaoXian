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
//	//�������ڴ����Ʒ�Ļ������ԣ�ͼƬ����δװ�أ�
//	//����
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
//	//flag�Ƿ񱻹���
//	bool flag;
//public:
//	bool getflag() { return flag; }
//	void changeflag() { flag = !flag; };//��������ͳ���
//	Product() :flag(0) {};
//};

class Shop
{
public:
	int ShopEnter(Hero* hero);//�̵����
	int BUY_Enter(Hero* hero);//�������
	int SELL_Enter(Hero* hero);//���۽���
	void add_product(Props*);//�̵���Ӳ�Ʒ
	void buyoperation(int, int);//�жϵ����λ���Ƿ���
	void selloperation(int, int);//�жϵ����λ���Ƿ����
	void product_draw(bool);//������Ʒ����
protected:
	vector<Props*> p;//��Ʒ����
};



