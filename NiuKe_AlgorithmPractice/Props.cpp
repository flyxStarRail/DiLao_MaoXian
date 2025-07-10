#include "Props.h"
#include <iostream>
#include "Target.h"

std::string PotionRecover::name = "生命恢复药水";
std::string Weapon::name = "武器";
std::string Armor::name = "盔甲";

void PotionRecover::function(Hero& hero) {
    hero.setHp(hero.getHp() + data); // 恢复生命
}
void PotionRecover::getInfo() const {
    std::cout << "生命恢复药水，恢复" << data << "点生命值。" << std::endl;
}
void Weapon::function(Hero& hero) {
    hero.setAtk(hero.getAtk() + data); // 增加攻击
}
void Weapon::getInfo() const {
    std::cout << "武器，增加" << data << "点攻击力。" << std::endl;
}
void Armor::function(Hero& hero) {
    hero.setDef(hero.getDef() + data); // 增加防御
}
void Armor::getInfo() const {
    std::cout << "盔甲，增加" << data << "点防御力。" << std::endl;
}

int SellITEM::getPrice(int id) {
    return price[id];
}
int SellITEM::price[10];
