#include "Enter.h"
#include "Shop.h"
#include <graphics.h>

void Enter::enter(bool& main_running)
{
	Resize(NULL, SCREENSIZE, SCREENSIZE);
	bool running = true;
	int x = 0;
	int y = 0;
	ExMessage msg;
	BeginBatchDraw();


	while (running)
	{
		DWORD beginTime = GetTickCount();			// ��¼ѭ����ʼʱ��

		// ��Ϣ����
		while (peekmessage(&msg))
		{
			if (msg.message == WM_LBUTTONDOWN) {		// �������Բ���ɫ
				x = msg.x;
				y = msg.y;
				int flag = judge(x,y);
				switch (flag)
				{
				case 1:
					Resize(NULL, SCREENSIZE, 700*K);
					return;
				case 2:
					//SellItem::clear();
					main_running = 0;
					//exit(0);
					return;
				case 0:
					break;
				default:
					break;
				}
			}
		}
		cleardevice();								// �����Ļ
		draw();

		FlushBatchDraw();
		// ֡��ʱ
		DWORD endTime = GetTickCount();				// ��¼ѭ������ʱ��
		DWORD elapsedTime = endTime - beginTime;	// ����ѭ����ʱ
		if (elapsedTime < 1000 / 60)				// ��ÿ��60֡���в�ʱ
			Sleep(1000 / 60 - elapsedTime);
	}

	EndBatchDraw();
	return ;
}

void Enter::draw()
{
	setbkcolor(BLACK);
	loadimage(NULL, _T("img\\Enter.png"), SCREENSIZE, SCREENSIZE);
	setbkmode(TRANSPARENT);
	setfillcolor(RGB(128, 128, 128));
	fillrectangle(150*K, 300*K, 450*K, 400*K);
	settextstyle(50*K,45*K,"����");
	outtextxy(185*K, 325*K, _T("Start"));
	fillrectangle(150*K, 450*K, 450*K, 550*K);
	outtextxy(210*K, 475*K, _T("Exit"));
}
int Enter::judge(int x,int y)
{
	if (x > 150*K && x < 450*K && y>300*K && y < 400*K)
	{
		return 1;
	}
	if (x > 150*K && x < 450*K && y>450*K && y < 550*K)
	{
		return 2;
	}
	return 0;
}

void Win::draw()
{
	cleardevice();
	setbkcolor(RGB(211, 55, 52));
	setfillcolor(WHITE);
	setbkmode(TRANSPARENT);
	settextstyle(50*K, 45*K, "����");
	settextcolor(RGB(236,191,8));
	outtextxy(135*K, 100*K, _T("YOU WIN"));
	settextcolor(BLACK);
	fillrectangle(150*K, 300*K, 450*K, 400*K);
	outtextxy(215*K, 325*K, _T("Back"));
	fillrectangle(150*K, 450*K, 450*K, 550*K);
	outtextxy(210*K, 475*K, _T("Exit"));
}

void Win::Animate()
{
	bool running = true;
	int x = -45*7*K;
	while (running)
	{
		DWORD beginTime = GetTickCount();			// ��¼ѭ����ʼʱ��

		// ��Ϣ����
		setbkcolor(RGB(211, 55, 52));
		cleardevice();
		setfillcolor(WHITE);
		setbkmode(TRANSPARENT);
		settextstyle(50*K, 45*K, "����");
		settextcolor(RGB(236, 191, 8));
		outtextxy(x, 100*K, _T("YOU WIN"));
		FlushBatchDraw();
		x += 15*K;
		if (x > 135*K) { running = false; }		
		// ֡��ʱ
		DWORD endTime = GetTickCount();				// ��¼ѭ������ʱ��
		DWORD elapsedTime = endTime - beginTime;	// ����ѭ����ʱ
		if (elapsedTime < 1000 / 60)				// ��ÿ��60֡���в�ʱ
			Sleep(1000 / 60 - elapsedTime);
	}

	EndBatchDraw();
}

void Win::enter(bool & main_running)
{
	Resize(NULL, SCREENSIZE, SCREENSIZE);
	bool running = true;
	int x = 0;
	int y = 0;
	ExMessage msg;
	BeginBatchDraw();
	Animate();

	while (running)
	{
		DWORD beginTime = GetTickCount();			// ��¼ѭ����ʼʱ��

		// ��Ϣ����
		while (peekmessage(&msg))
		{
			if (msg.message == WM_LBUTTONDOWN) {		// �������Բ���ɫ
				x = msg.x;
				y = msg.y;
				int flag = judge(x, y);
				switch (flag)
				{
				case 1:
					return;
					break;
				case 2:
					main_running = 0;
					return;
				}
				
			}
		}
		cleardevice();								// �����Ļ
		draw();

		FlushBatchDraw();
		// ֡��ʱ
		DWORD endTime = GetTickCount();				// ��¼ѭ������ʱ��
		DWORD elapsedTime = endTime - beginTime;	// ����ѭ����ʱ
		if (elapsedTime < 1000 / 60)				// ��ÿ��60֡���в�ʱ
			Sleep(1000 / 60 - elapsedTime);
	}

	EndBatchDraw();
	return;
}
int Win::judge(int x, int y)
{

	if (x > 150*K && x < 450*K && y>450*K && y < 550*K)
	{
		//SellItem::clear();
		return 2;
	}
	if (x > 150*K && x < 450*K && y>300*K && y < 400*K)
	{
		return 1;
	}
	return 0;
}

void Failed::draw()
{
	cleardevice();
	settextstyle(80*K, 50*K, "����");
	outtextxy(150*K, 300*K, _T("FAILED"));
}