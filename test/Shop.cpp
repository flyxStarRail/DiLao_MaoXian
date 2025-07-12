#include "Shop.h"
#include "Target.h"

using namespace std;

void Shop::add_product(Props* temp)
{
	//�˺���Ϊ��Shop����Ӳ�Ʒ
	if (temp==NULL)
	{
		//�������Ϊ��ָ������ӿն���
		//��û��д��������
		temp = new Weapon(1,100);
		temp->set_img(new IMAGE);
		p.push_back(temp);
	}
	else
	{
		p.push_back(temp);
	}
}
static int getoperation(int x, int y)
{
	//�˺������ڷ��ظ������������Ӧλ�õõ��Ľ��
	if (x > SIZE / 2 - FONTSIZE * 2 && x < SIZE / 2 + FONTSIZE * 2)
	{
		if (y > 120 && y < 120 + FONTSIZE) { return 1;/*BUY*/ }
		if (y > 220 && y < 220 + FONTSIZE) { return 2;/*SELL*/ }
		if (y > 320 && y < 320 + FONTSIZE) { return 0;/*EXIT*/ }
	}
	return 4;
}
void Shop::buyoperation(int x, int y)
{
	//�˺�����ʾ��������У��ж��Ƿ��򲢽��в����ĺ���
	//�ɷ�װ�� ����ֵΪ int �ĺ��������ݹ����װ�����±�
	//�� ����ֵΪ Product* �ĺ��������ݵ������װ����ָ��
	int index = 1;
	int index_c = 1;
	int item_x1, item_y1;
	int item_x2, item_y2;
	for (int i = 0; i < min(p.size(), 10); i++)
	{
		if (p[i]->getflag() == 0)
		{
			item_x1 = SIZE / 2 - ITEMSIZE * 0.5 - 300 + 100 * index;
			item_y1 = 100 * index_c;
			item_x2 = item_x1 + ITEMSIZE;
			item_y2 = item_y1 + ITEMSIZE;
			if (x > item_x1 && x<item_x2 && y>item_y1 && y < item_y2)
			{
				//P[i]Ϊ�����װ��
				//�˴���ʾ�ж��Ƿ�Ϊ�������װ����
				p[i]->changeflag();
				cout << i << endl;
				//������װ�������е��˴�ֹͣ
				return;
			}
			index++;
			if (index == 6)
			{
				index = 1;
				index_c++;
			}
		}
	}
	//���û�е����װ����������е�����
}

void Shop::selloperation(int x, int y)
{
	//�˺�����ʾ���۽����У��ж��Ƿ���۲����в����ĺ���
	//�ɷ�װ�� ����ֵΪ int �ĺ��������ݳ��۵�װ�����±�
	//�� ����ֵΪ Product* �ĺ��������ݵ������װ����ָ��
	int index = 1;
	int index_c = 1;
	int item_x1, item_y1;
	int item_x2, item_y2;
	for (int i = 0; i < min(p.size(), 10); i++)
	{
		if (p[i]->getflag())
		{

			item_x1 = SIZE / 2 - ITEMSIZE * 0.5 - 300 + 100 * index;
			item_y1 = 100 * index_c;
			item_x2 = item_x1 + ITEMSIZE;
			item_y2 = item_y1 + ITEMSIZE;
			if (x > item_x1 && x<item_x2 && y>item_y1 && y < item_y2)
			{
				//P[i]Ϊ���۵�װ��
				p[i]->changeflag();
				cout << i << endl;
				return;
			}
			index++;
			if (index == 6)
			{
				index = 1;
				index_c++;
			}
		}
	}
}
void Shop::product_draw(bool product_flag)
{
	//�˺���Ϊ�����̵����Ʒ
	cleardevice();
	int index = 1;
	int index_c = 1;
	for (int i = 0; i < min(p.size(), 10); i++)
	{

		if (p[i]->getflag()==product_flag)
		{
			//setbkcolor(RGB(128, 128, 128));
			setfillcolor(RGB(128, 128, 128));
			fillrectangle(SIZE / 2 - ITEMSIZE * 0.5 - 300 + 100 * index, 100 * index_c, SIZE / 2 - ITEMSIZE * 0.5 - 300 + 100 * index + 80, 100 * index_c + ITEMSIZE);
			putimage_alpha(SIZE / 2 - ITEMSIZE * 0.5 - 300 + 100 * index, 100 * index_c, p[i]->getimage());
			//setbkcolor(BLACK);
			index++;
			if (index == 6)
			{
				index = 1;
				index_c++;
			}
		}
	}
	settextstyle(40, 40, "Courier");
	outtextxy(SIZE / 2 - FONTSIZE * 2, 320, "EXIT");
	FlushBatchDraw();
}

int Shop::ShopEnter(Hero* hero)
{
	//�˺���Ϊ�̵�Ľ���������
	//x,y�����洢�����������
	int x = 0;					
	int y = 0;	
	//change
	Resize(NULL, 600, 500);
	bool running = true;
	ExMessage msg;
	while (running) {
		DWORD beginTime = GetTickCount();
		while (peekmessage(&msg)) {
			if (msg.message == WM_LBUTTONDOWN) 
				//���ʱ����
			{
				x = msg.x;
				y = msg.y;
				//ע�͵�������Ϊ����ʱʹ�ã�����ʾ�õ���x y
				//std::cout << x << '\n' << y << std::endl;
				int flag = getoperation(x, y);
				//flag ���� �ж� �õ��� ����������ʲô
				switch (flag)
				{
				case 0:
					hero->clearattr();
					//change
					Resize(NULL,600, 700);
					return 0;
				case 1:
					BUY_Enter(hero);
					break;
				case 2:
					SELL_Enter(hero);
					break;
				default:
					break;
				}

			}
		}
		// ��ͼ
		cleardevice();					
		settextstyle(40, 40, "Courier");
		outtextxy(SIZE / 2 - FONTSIZE * 2, 20, "SHOP");
		outtextxy(SIZE / 2 - FONTSIZE * 1.5, 120, "BUY");
		outtextxy(SIZE / 2 - FONTSIZE * 2, 220, "SELL");
		outtextxy(SIZE / 2 - FONTSIZE * 2, 320, "EXIT");

		FlushBatchDraw();				
		DWORD endTime = GetTickCount();				// ��¼ѭ������ʱ��
		DWORD elapsedTime = endTime - beginTime;	// ����ѭ����ʱ
		if (elapsedTime < 1000 / 60)				// ��ÿ��60֡���в�ʱ
			Sleep(1000 / 60 - elapsedTime);
	}
	return 0;
}

int Shop::SELL_Enter(Hero* hero)
{
	int x = 0;			
	int y = 0;				
	bool running = true;
	ExMessage msg;
	FlushBatchDraw();

	while (running) {
		// ��Ϣ����	
		DWORD beginTime = GetTickCount();	
		while (peekmessage(&msg)) {
			if (msg.message == WM_LBUTTONDOWN) {
				x = msg.x;
				y = msg.y;
				std::cout << x << '\n' << y << std::endl;
				selloperation(x, y);
				int flag = getoperation(x, y);
				switch (flag)
				{
				case 0:
					return 0;
				default:
					break;
				}
			}

		}
		// ��ͼ
		product_draw(1);
		DWORD endTime = GetTickCount();				// ��¼ѭ������ʱ��
		DWORD elapsedTime = endTime - beginTime;	// ����ѭ����ʱ
		if (elapsedTime < 1000 / 60)				// ��ÿ��60֡���в�ʱ
			Sleep(1000 / 60 - elapsedTime);
						
	}
	return 0;
}

int Shop::BUY_Enter(Hero* hero)
{
	//�������
	int x = 0;						
	int y = 0;						
	bool running = true;
	ExMessage msg;
	FlushBatchDraw();

	while (running) {
		DWORD beginTime = GetTickCount();
		while (peekmessage(&msg)) {
			if (msg.message == WM_LBUTTONDOWN) //����������ʱ
			{
				x = msg.x;
				y = msg.y;

				buyoperation(x, y);//�ж��Ƿ���
				int flag = getoperation(x, y);//�ж��Ƿ��˳�
				switch (flag)
				{
				case 0:
					return 0;//�˳�
				default:
					break;
				}

			}

		}
		// ��ͼ
		product_draw(0);
		settextstyle(40, 40, "Courier");
		outtextxy(SIZE / 2 - FONTSIZE * 2, 320, "EXIT");
		FlushBatchDraw();				// ˢ��������ͼ
		DWORD endTime = GetTickCount();				// ��¼ѭ������ʱ��
		DWORD elapsedTime = endTime - beginTime;	// ����ѭ����ʱ
		if (elapsedTime < 1000 / 60)				// ��ÿ��60֡���в�ʱ
			Sleep(1000 / 60 - elapsedTime);
	}
	return 0;
}
//
//Item::Item(LPCSTR& temp)
//{
//	//loadimage(img, temp, ITEMSIZE, ITEMSIZE,false);
//}