#include "Props.h"
#include <iostream>
#include "Target.h"

std::string PotionRecover::name = "�����ָ�ҩˮ";
std::string Weapon::name = "����";
std::string Armor::name = "����";

void PotionRecover::function(Hero& hero) {
    hero.setHp(hero.getHp() + data); // �ָ�����
}
void PotionRecover::getInfo() const {
    std::cout << "�����ָ�ҩˮ���ָ�" << data << "������ֵ��" << std::endl;
}
void Weapon::function(Hero& hero) {
    hero.setAtk(hero.getAtk() + data); // ���ӹ���
}
void Weapon::getInfo() const {
    std::cout << "����������" << data << "�㹥������" << std::endl;
}
void Armor::function(Hero& hero) {
    hero.setDef(hero.getDef() + data); // ���ӷ���
}
void Armor::getInfo() const {
    std::cout << "���ף�����" << data << "���������" << std::endl;
}

int SellITEM::getPrice(int id) {
    return price[id];
}
int SellITEM::price[10];
