#include "Target.h"

// 英雄与敌人交互战斗逻辑（英雄先攻，再敌人反击）
bool Enermy::interact(Hero* hero) {
    int damage = hero->getAtk() - def;
    if (damage > 0) {
        hp -= damage;  // 敌人掉血
    }
    if (hp <= 0) {
        std::cout << "敌人已死亡" << std::endl;
        return true;
    }
    damage = atk - hero->getDef();
    if (damage > 0) {
        hero->setHp(hero->getHp() - damage); // 英雄掉血
    }
    if (hero->getHp() <= 0) {
        std::cout << "英雄已死亡" << std::endl;
        return false;
    }
    return true;
}

// 销售商交互（本例在主循环中处理商店界面，所以这里只返回 true）
bool Salesman::interact(Hero* hero) {
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
