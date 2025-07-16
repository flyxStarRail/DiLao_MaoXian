#include "Props.h"
#include <iostream>
#include "Target.h"

std::string PotionRecover::name = "�����ָ�ҩˮ";
std::string Weapon::name = "����";
std::string Armor::name = "����";

void Props::buy(Hero* hero) 
{ 
    hero->setGold(hero->getGold() - price); 
}
bool Props::is_vailed(Hero* hero) {
    return (hero->getGold() >= price);
}
void PotionRecover::function(Hero& hero) {
    hero.setHp(hero.getHp() + data); // �ָ�����
}
void PotionRecover::getInfo(char* str, int length) const {
    int n = snprintf(str, length, "�����ָ�ҩˮ���ָ�%d������ֵ��", data);
    if (n < 0 || n >= length) {
        throw std::runtime_error("PotionRecover::getInfo: ˵����Ϣ������󳤶�");
    }
}
void Weapon::function(Hero& hero) {
    hero.setAtk(hero.getAtk() + data); // ���ӹ���
}
void Weapon::getInfo(char* str, int length) const {
    int n = snprintf(str, length, "����������%d�㹥������", data);
    if (n < 0 || n >= length) {
        throw std::runtime_error("Weapon::getInfo: ˵����Ϣ������󳤶�");
    }
}
void Armor::function(Hero& hero) {
    hero.setDef(hero.getDef() + data); // ���ӷ���
}
void Armor::getInfo(char* str, int length) const {
    int n = snprintf(str, length, "���ף�����%d���������", data);
    if (n < 0 || n >= length) {
        throw std::runtime_error("Armor::getInfo: ˵����Ϣ������󳤶�");
    }
}
