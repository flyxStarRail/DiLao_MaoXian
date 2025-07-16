#include "Props.h"
#include <iostream>
#include "Target.h"

std::string PotionRecover::name = "生命恢复药水";
std::string Weapon::name = "武器";
std::string Armor::name = "盔甲";

void Props::buy(Hero* hero) 
{ 
    hero->setGold(hero->getGold() - price); 
}
bool Props::is_vailed(Hero* hero) {
    return (hero->getGold() >= price);
}
void PotionRecover::function(Hero& hero) {
    hero.setHp(hero.getHp() + data); // 恢复生命
}
void PotionRecover::getInfo(char* str, int length) const {
    int n = snprintf(str, length, "生命恢复药水，恢复%d点生命值。", data);
    if (n < 0 || n >= length) {
        throw std::runtime_error("PotionRecover::getInfo: 说明信息超出最大长度");
    }
}
void Weapon::function(Hero& hero) {
    hero.setAtk(hero.getAtk() + data); // 增加攻击
}
void Weapon::getInfo(char* str, int length) const {
    int n = snprintf(str, length, "武器，增加%d点攻击力。", data);
    if (n < 0 || n >= length) {
        throw std::runtime_error("Weapon::getInfo: 说明信息超出最大长度");
    }
}
void Armor::function(Hero& hero) {
    hero.setDef(hero.getDef() + data); // 增加防御
}
void Armor::getInfo(char* str, int length) const {
    int n = snprintf(str, length, "盔甲，增加%d点防御力。", data);
    if (n < 0 || n >= length) {
        throw std::runtime_error("Armor::getInfo: 说明信息超出最大长度");
    }
}
