#include "Target.h"
#include <graphics.h>
// Ӣ������˽���ս���߼���Ӣ���ȹ����ٵ��˷�����
void Enermy::img_init()
{
    loadimage(img, _T("img\\zombie.png"), 40, 40, false);
}
void  Enermy::print(int x, int y){
    putimage_alpha(x, y, img);
    fillrectangle(x + 5, y, x + 30, y + 5);
    setfillcolor(RED);
    setlinestyle(PS_NULL,1);
    fillrectangle(x + 6, y+1, x + 30*hp/full_hp, y + 5);
    setlinestyle(0, 1);
};

void Enermy::restart()
{
    flag = 1;
    hp = full_hp;
}

bool Enermy::interact(Hero* hero) {
    int damage = hero->getAtk() - def;
    if (damage > 0) {
        hp -= damage;  // ���˵�Ѫ
    }
    if (hp <= 0) {
        std::cout << "����������" << std::endl;
        flag = 0;
        hero->setDef(hero->getDef() + 1);
        SellItem::add(rand() % 10);
        return true;
    }
    damage = atk - hero->getDef();
    if (damage > 0) {
        hero->setHp(hero->getHp() - damage); // Ӣ�۵�Ѫ
    }
    if (hero->getHp() <= 0) {
        std::cout << "Ӣ��������" << std::endl;
        hero->dead();
        return false;
    }
    return true;
}

// �����̽�������������ѭ���д����̵���棬��������ֻ���� true��
bool Salesman::interact(Hero* hero) {
    Enter(hero);
    return true;
}

bool Salesman::buyItem(Hero* hero) {
    //��δʵ�֣��˴��ɵ��� Props �ı�Ӣ�����ԣ�
    return true;
}
bool Salesman::sellItem(Hero* hero) {
    //��δʵ�֣��˴��ɴ���Ӣ�۳�����Ʒ��
    return true;
}

void Salesman::print(int x,int y)
{
    putimage_alpha(x, y, img);
}
void Salesman::restart()
{
    shop->restart();
}
void Salesman::img_init()
{
    loadimage(img, _T("img\\saleman.png"),40 ,40);
}

void Hero::print()
{
    settextstyle(20, 0, _T("Arial"));
    TCHAR buf[50];
    settextcolor(RGB(255, 255, 255));
    //�����������ԣ�
    _stprintf_s(buf, _T("HP: %d"), hp);
    outtextxy(10, 610, buf);
    _stprintf_s(buf, _T("ATK: %d"), atk);
    outtextxy(10, 640, buf);
    _stprintf_s(buf, _T("DEF: %d"), def);
    outtextxy(10, 670, buf);
}
bool Hero::win(int end)
{
    return attr->win(end);
}