#include "Target.h"
#include <graphics.h>
// 英雄与敌人交互战斗逻辑（英雄先攻，再敌人反击）
void Enermy::img_init()
{
    loadimage(img, _T("img\\zombie.png"), 40, 40, false);
}
void  Enermy::print(int x, int y){
    putimage_alpha(x, y, img);
};

bool Enermy::interact(Hero* hero) {
    int damage = hero->getAtk() - def;
    if (damage > 0) {
        hp -= damage;  // 敌人掉血
    }
    if (hp <= 0) {
        std::cout << "敌人已死亡" << std::endl;
        flag = 0;
        hero->setDef(hero->getDef() + 1);
        return true;
    }
    damage = atk - hero->getDef();
    if (damage > 0) {
        hero->setHp(hero->getHp() - damage); // 英雄掉血
    }
    if (hero->getHp() <= 0) {
        std::cout << "英雄已死亡" << std::endl;
        hero->dead();
        return false;
    }
    return true;
}

// 销售商交互（本例在主循环中处理商店界面，所以这里只返回 true）
bool Salesman::interact(Hero* hero) {
    Enter(hero);
    return true;
}

bool Salesman::buyItem(Hero* hero) {
    //（未实现：此处可调用 Props 改变英雄属性）
    return true;
}
bool Salesman::sellItem(Hero* hero) {
    //（未实现：此处可处理英雄出售物品）
    return true;
}

void Salesman::print(int x,int y)
{
    putimage_alpha(x, y, img);
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
    //绘制人物属性；
    _stprintf_s(buf, _T("HP: %d"), hp);
    outtextxy(10, 610, buf);
    _stprintf_s(buf, _T("ATK: %d"), atk);
    outtextxy(10, 640, buf);
    _stprintf_s(buf, _T("DEF: %d"), def);
    outtextxy(10, 670, buf);
}