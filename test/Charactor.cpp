#include "Charactor.h"
#include "Area.h"
#include "Target.h"
#include <fstream>


void HeroMoveAttribute::link(NewAreaList* temp) {
	islink = true;
	this->m = temp;
	m->link(this);
};


#ifdef MAP_EXPORT
void export_map(vector<unique_ptr<NewAreaList>>& ar_l)
{
	ifstream map_init("map\\map.txt");
	int map_num;
	int len;
	map_init >> map_num >> len;
	ofstream fout("map\\map.txt");
	fout << map_num << ' ' << len << endl;
	for (int i = 0; i < map_num; i++)
	{
		ar_l[i]->out(i, fout);
	}
	fout << -1;
}
#endif

void HeroMoveAttribute::move()
{
	isMove = isLeft || isRight || isDown || isUp;
	int temp_y = y;
	int& screen_x = m->get_screen_x();
	int temp_real_x = x + screen_x;
	int real_x = temp_real_x;
	int screen_temp = screen_x;

	if (x < 50 && isLeft || x > DRAW_WIDTH - 60 * K && isRight)
	{
		isSpeed = false;
	}

	step = isSpeed ? 10 : 5;

	//移动
	real_x += isRight ? step : 0;
	real_x -= isLeft ? step : 0;

	y += isDown ? step : 0;
	y -= isUp ? step : 0;

	//防止出界

	y = y < 0 ? 0 : y;
	y = y > 560 ? 560 : y;



	bool isScreenMove = true;

	//防止屏幕左侧出界
	if (screen_x <= 0)
	{
		screen_x = 0;
		if (isLeft) {
			isScreenMove = false;
		}
	}

	int end = m->get_len();

	//防止屏幕右侧出界
	if (screen_x + DRAW_WIDTH > end)
	{
		if (isRight)
			isScreenMove = false;
	}


	if (real_x - screen_x < 200 && isRight)
	{
		isScreenMove = false;
	}
	else if (real_x - screen_x > DRAW_WIDTH * 2.0 / 3 && isLeft)
	{
		isScreenMove = false;
	}

	int screen_step = isScreenMove ? 5 : 0;
	screen_x += isRight ? screen_step : 0;
	screen_x -= isLeft ? screen_step : 0;
	x = real_x - screen_x;
	int isMeet = m->Meet();
	if (isMeet)
	{

		if (isMeet & 0b10)
		{
			y = temp_y;
		}
		if (isMeet & 0b01)
		{
			real_x = temp_real_x;
		}
		else {
			real_x = x + screen_x;
		}
	}
	screen_x < 0 ? screen_x = 0 : 0;
	real_x < 0 ? real_x = 0 : 0;
	x = real_x - screen_x;

}



CharactorMoveAttribute::CharactorMoveAttribute(int x, int y)
	:isSpeed(0)
{
	this->x = x;
	this->y = y;
	step = 5;
}

HeroMoveAttribute::HeroMoveAttribute(int x, int y) :CharactorMoveAttribute(x, y), islink(false), isMove(false), t(0), m(nullptr), body(nullptr)
{
	isUp = isLeft = isRight = isDown = isSpeed = is_img_left = 0;
	loadimage(&img[0][0], _T("img\\move_0.png"), BLOCKSIZE * K, BLOCKSIZE * K, false);
	loadimage(&img[0][1], _T("img\\move_1.png"), BLOCKSIZE * K, BLOCKSIZE * K, false);
	loadimage(&img[1][0], _T("img\\lmove_0.png"), BLOCKSIZE * K, BLOCKSIZE * K, false);
	loadimage(&img[1][1], _T("img\\lmove_1.png"), BLOCKSIZE * K, BLOCKSIZE * K, false);
}



#ifndef MAP_EXPORT
void HeroMoveAttribute::judge(ExMessage& msg, bool& running, Shop& a)
#endif // !MAP_EXPORT
#ifdef MAP_EXPORT
void HeroMoveAttribute::judge(ExMessage& msg, bool& running, Shop& a, vector<unique_ptr<NewAreaList>>& ar_l)
#endif // MAP_EXPORT
{
#ifdef DEBUG

	if (msg.message == WM_LBUTTONDOWN)
	{
		int _x = msg.x / K + m->get_screen_x();
		int _y = msg.y / K;
		int temp_row = _x % 600 / 40;
		int temp_col = _y / 40;
		int index = _x / 600;
		switch (c)
		{
#ifdef ERASOR
		case 'E':
		case 'e':

			m->erasor(temp_row, temp_col, index);
			break;
#endif
		case 'B':
		case'b':
			m->add_Barrier(temp_row, temp_col, index);
			break;
		case 'Z':
		case 'z':
			m->add_Enermy(temp_row, temp_col, index);
			break;
		}
	}
#endif // DEBUG
	//该函数用来判断此时按下的是什么键
	if (msg.message == WM_KEYDOWN)			// 按下按键处理
	{

		switch (msg.vkcode)
		{
		case 'w':
		case 'W':
		case VK_UP:
			isUp = 1;
			break;

		case 's':
		case 'S':
		case VK_DOWN:
			isDown = 1;
			break;

		case 'a':
		case 'A':
		case VK_LEFT:
			is_img_left = 1;
			isLeft = 1;
			break;

		case 'd':
		case 'D':
		case VK_RIGHT:
			is_img_left = 0;
			isRight = 1;
			break;

		case 'h':
		case 'H':
			isSpeed = 1;
			break;

#ifdef DEBUG
		case 't':
		case 'T':
			//进入商店
			isDown = 0;			isUp = 0;			isLeft = 0;			isRight = 0;			isSpeed = 0;
			a.ShopEnter(body);
			break;
#endif // DEBUG

		case VK_ESCAPE:
			running = false;
			break;

#ifdef MAP_EXPORT
		case 'p':
		case 'P':
			export_map(ar_l);
			break;
#endif
		default:
#ifdef DEBUG
			c = msg.vkcode;
#endif // DEBUG
			break;
		}
	}
	if (msg.message == WM_KEYUP)			// 松开按键处理
	{


		switch (msg.vkcode)
		{
		case 'w':
		case 'W':
		case VK_UP:
			isUp = 0;
			break;

		case 's':
		case 'S':
		case VK_DOWN:
			isDown = 0;
			break;

		case 'a':
		case 'A':
		case VK_LEFT:
			isLeft = 0;
			break;

		case 'd':
		case 'D':
		case VK_RIGHT:
			isRight = 0;
			break;
		case 'h':
		case 'H':
			isSpeed = 0;
			break;
		}

	}
}



//下面的函数还没写好
void HeroMoveAttribute::put_solided()
{
	if (isMove)
	{
		t++;
		int n;
		n = isSpeed ? 3 : 15;
		t = t % (2 * n);
		putimage_alpha(x * K, y * K, &img[is_img_left][t / n]);
	}
	else {
		putimage_alpha(x * K, y * K, &img[is_img_left][0]);
	}
}
void HeroMoveAttribute::set_body(Hero* temp)
{
	body = temp;
	body->link_attr(this);
}
bool HeroMoveAttribute::win(int end)
{
	int& screen_x = m->get_screen_x();
	if (screen_x + x > end)
	{
		return 1;
	}
	return 0;
}
void HeroMoveAttribute::position_clear()
{
	x = 0;
	y = 0;
}
