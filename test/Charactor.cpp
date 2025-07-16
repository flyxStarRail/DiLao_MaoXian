#include "Charactor.h"
#include "Area.h"
#include "Target.h"
void putimage_alpha(int x, int y, IMAGE* img)
{
	//函数用来显示透明图像
	int w = img->getwidth();
	int h = img->getheight();
	AlphaBlend(GetImageHDC(NULL), x, y, w, h, GetImageHDC(img), 0, 0, w, h, { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA });
}


void HeroMoveAttribute::link(NewAreaList* temp) {
	islink = true;
	this->m = temp;
	//if (m->isLink())
	//{
	//	return;
	//}
	m->link(this);
};
void HeroMoveAttribute::move()
{
	isMove = isLeft || isRight || isUp || isDown;
	int temp_y = y;
	int& screen_x = m->get_screen_x();
	int temp_real_x = x + screen_x;
	//用来操作一帧内角色的移动
	if (x < 20 && isLeft) isSpeed = false;
	int screen_temp = screen_x;
	if (x > 550 && isRight) isSpeed = false;
	step = isSpeed ? 10 : 5;
	x -= isLeft ? step - 5 : 0;
	screen_x -= isLeft ? 5 : 0;
	screen_x += isRight ? 5 : 0;
	x += isRight ? step - 5 : 0;
	y += isUp ? step : 0;
	y -= isDown ? step : 0;
	y = y < 0 ? 0 : y;
	y = y > 560 ? 560 : y;
	if (screen_x < 0)
	{
		x += screen_x;
		x = x < 0 ? 0 : x;
		screen_x = 0;
	}
	int end = m->get_len() - AREASIZE + 50;
	if (screen_x > end )
	{
		x += screen_x - end;
		x = x < 0 ? 0 : x;
		screen_x = end;
	}
	if (m->Meet())
	{

		x > 550 && isLeft ? screen_x = screen_temp : 0;
		x < 10 && isRight ? screen_x = screen_temp : 0;

		int temp_x = temp_real_x - screen_x;
		x = temp_x;
		y = temp_y;
	}
}

CharactorMoveAttribute::CharactorMoveAttribute(int x, int y)
{
	this->x = x;
	this->y = y;
	step = 5;
}

HeroMoveAttribute::HeroMoveAttribute(int x, int y) :CharactorMoveAttribute(x, y), islink(false), isMove(false), t(0)
{
	isDown = isLeft = isRight = isUp = isSpeed = isdamaged = isAttck = is_img_left = 0;
	loadimage(&img[0][0], _T("img\\move_0.png"), BLOCKSIZE*K, BLOCKSIZE*K, false);
	loadimage(&img[0][1], _T("img\\move_1.png"), BLOCKSIZE*K, BLOCKSIZE*K, false);
	loadimage(&img[1][0], _T("img\\lmove_0.png"), BLOCKSIZE*K, BLOCKSIZE*K, false);
	loadimage(&img[1][1], _T("img\\lmove_1.png"), BLOCKSIZE*K, BLOCKSIZE*K, false);
}

void HeroMoveAttribute::judge(ExMessage& msg, bool& running, Shop& a)
{
	//该函数用来判断此时按下的是什么键
	if (msg.message == WM_KEYDOWN)			// 按下按键处理
	{
		switch (msg.vkcode)
		{
		case 'w':
		case 'W':
		case VK_UP:
			isDown = 1;
			break;

		case 's':
		case 'S':
		case VK_DOWN:
			isUp = 1;
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
		case 'b':
		case 'B':
			//进入商店
			isDown = 0;			isUp = 0;			isLeft = 0;			isRight = 0;			isSpeed = 0;
			//a.ShopEnter();
			break;

		case VK_ESCAPE:
			running = false;
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
			isDown = 0;
			break;

		case 's':
		case 'S':
		case VK_DOWN:
			isUp = 0;
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
		putimage_alpha(x*K, y*K, &img[is_img_left][t / n]);
	}
	else {
		putimage_alpha(x*K, y*K, &img[is_img_left][0]);
	}
	//putimage(x, y, &img);
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
static int screen2ph(int x, int screen_x)
{
	return x + screen_x;
}