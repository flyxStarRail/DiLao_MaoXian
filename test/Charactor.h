#pragma once
#include "Shop.h"
#include <graphics.h>
#pragma comment(lib, "MSIMG32.LIB")
class Hero;
class NewAreaList;
class NewArea;

typedef NewArea Map;
typedef NewAreaList MapList;

class CharactorMoveAttribute
{
protected:
	int x;
	int y;
	bool isSpeed;
	bool isAttck;
	int step;
	bool isdamaged;
public:
	CharactorMoveAttribute(int x = 0, int y = 0);

};



class HeroMoveAttribute
	:public CharactorMoveAttribute
{
protected:
	int t;
	bool isMove;
	bool isLeft;
	bool isRight;
	bool isUp;
	bool isDown;
	bool islink;
	bool is_img_left;
	IMAGE img[2][2];
	NewAreaList* m;//用于链接NewAreaList
	Hero* body;
public:
	void move();//控制移动
	void link(NewAreaList* temp);
	HeroMoveAttribute(int x, int y);
	void judge(ExMessage&, bool&, Shop& a);//判断按键
	void put_solided();//绘制英雄
	bool isLink() { return islink; };
	int get_x() { return x; };
	int get_y() { return y; };
	Hero* get_body(){ return body; };
	void set_body(Hero*);
	void attrclear()
	{
		isLeft = isRight = isDown = isUp = isMove = isSpeed = 0 ;
	};
	bool win(int end);
	void position_clear();
};

//下面的类暂未写好


void putimage_alpha(int x, int y, IMAGE* img);
