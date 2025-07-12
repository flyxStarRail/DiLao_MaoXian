#include "Enter.h"
#include <graphics.h>

void Enter::enter()
{
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
					Resize(NULL, 600, 700);
					return;
				case 2:
					exit(0);
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
	loadimage(NULL, _T("img\\Enter.png"), 600, 600);
	setbkmode(TRANSPARENT);
	setfillcolor(RGB(128, 128, 128));
	fillrectangle(300 - 150, 300, 150 + 300, 400);
	settextstyle(50,45,"����");
	outtextxy(185, 325, _T("Start"));
	fillrectangle(300 - 150, 450, 150 + 300, 550);
	outtextxy(210, 475, _T("Exit"));
}
int Enter::judge(int x,int y)
{
	if (x > 150 && x < 450 && y>300 && y < 400)
	{
		return 1;
	}
	if (x > 150 && x < 450 && y>450 && y < 550)
	{
		return 2;
	}
	return 0;
}
