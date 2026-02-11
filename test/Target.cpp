#include "Target.h"
#include <graphics.h>
// 英雄与敌人交互战斗逻辑（英雄先攻，再敌人反击）
void Enermy::img_init()
{
    loadimage(img.get(), _T("img\\zombie.png"), static_cast<int>(BLOCKSIZE * K), static_cast<int>(BLOCKSIZE * K), false);
}
void  Enermy::print(int x, int y){
    putimage_alpha(x, y, img.get());
    fillrectangle(x + 5*K, y, x + 30*K, y + 5*K);
    setfillcolor(RED);
    setlinestyle(PS_NULL,1);
    fillrectangle(x + 6*K, y+1*K, x + 30*K*hp/full_hp, y + 5*K);
    setlinestyle(0, K);
};
#ifdef MAP_EXPORT
void Enermy::out(int x, int y, int index, int map_index, ofstream& fout)
{
    fout << (int)1 << ' ' << x << ' ' << y << ' ' << index << ' ' << map_index << ' ' << atk << ' ' << hp << endl;
    //printf("ar[%d]->add_Enermy(%d,%d,%d);\n", map_index, x, y, index);
}
#endif // MAP_EXPORT


void Enermy::restart()
{
    flag = 1;
    hp = full_hp;
}

bool Enermy::interact(Hero* hero) {
    int damage = hero->getAtk() - def;
    if (damage > 0) {
        hp -= damage;  // 敌人掉血
    }
    if (hp <= 0) {
        //std::cout << "敌人已死亡" << std::endl;
        flag = 0;
        hero->setDef(hero->getDef() + 1);
        SellItem::add(rand() % 10);
        return true;
    }
    damage = atk - hero->getDef();
    if (damage > 0) {
        hero->setHp(hero->getHp() - damage); // 英雄掉血
    }
    if (hero->getHp() <= 0) {
        //std::cout << "英雄已死亡" << std::endl;
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
    putimage_alpha(x, y, img.get());
}
void Salesman::restart()
{
    shop->restart();
}
void Salesman::img_init()
{
    loadimage(img.get(), _T("img\\saleman.png"), BLOCKSIZE * K, BLOCKSIZE * K);
}

void Hero::print()
{
    settextstyle(20*K, 0, _T("Arial"));
    TCHAR buf[50];
    settextcolor(RGB(255, 255, 255));
    //绘制人物属性；
    _stprintf_s(buf, _T("HP: %d"), hp);
    outtextxy(10*K, 610*K, buf);
    _stprintf_s(buf, _T("ATK: %d"), atk);
    outtextxy(10*K, 640*K, buf);
    _stprintf_s(buf, _T("DEF: %d"), def);
    outtextxy(10*K, 670*K, buf);
}
bool Hero::win(int end)
{
    return attr->win(end);
}