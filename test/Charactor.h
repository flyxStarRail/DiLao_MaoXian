#pragma once
#include "Shop.h"
#include "Tool.h"
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
	int step;
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
	bool isDown;
	bool isUp;
	bool islink;
	bool is_img_left;
#ifdef DEBUG
	char c;
#endif // DEBUG

	IMAGE img[2][2];
	NewAreaList* m;//用于链接NewAreaListattrclear
	Hero* body;
public:
	friend class NewAreaList;
	void move();//控制移动
	void link(NewAreaList* temp);
	HeroMoveAttribute(int x, int y);
#ifndef MAP_EXPORT
	void judge(ExMessage&, bool&, Shop&);
#endif // !MAP_EXPORT
#ifdef MAP_EXPORT
		void judge(ExMessage&, bool&, Shop&,vector<unique_ptr<NewAreaList>>& ar_l);
#endif // MAP_EXPORT
	//判断按键
	void put_solided();//绘制英雄
	bool isLink() const { return islink; };
	int get_x() { return x; };
	int get_y() { return y; };
	Hero* get_body(){ return body; };
	void set_body(Hero*);
	void attrclear()
	{
		isLeft = isRight = isUp = isDown = isMove = isSpeed = 0 ;
	};
	bool win(int end);
	void position_clear();
};


