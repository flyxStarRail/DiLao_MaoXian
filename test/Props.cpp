#include "Props.h"
#include <iostream>
#include "Target.h"
#include "Tool.h"

std::string PotionRecover::name = "生命恢复药水";
std::string Weapon::name = "武器";
std::string Armor::name = "盔甲";


void Props::set_img(std::string str) {
    img = make_unique<IMAGE>();
    loadimage(img.get(), to_lpctstr(str), static_cast<int>(ITEMSIZE), static_cast<int>(ITEMSIZE));
};

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


string PotionRecover::getInfo() const
{
    return std::format("生命恢复药水，恢复{}点生命值。", data);
}


void Weapon::function(Hero& hero) {
    hero.setAtk(hero.getAtk() + data); // 增加攻击
}

string Weapon::getInfo() const
{
    return std::format("武器，增加{}点攻击力。", data);
}
void Armor::function(Hero& hero) {
    hero.setDef(hero.getDef() + data); // 增加防御
}

string Armor::getInfo() const
{
    return std::format("盔甲，增加{}点防御力。", data);
}
