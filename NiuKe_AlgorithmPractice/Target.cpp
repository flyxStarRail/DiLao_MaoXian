#include "Target.h"

// Ӣ������˽���ս���߼���Ӣ���ȹ����ٵ��˷�����
bool Enermy::interact(Hero* hero) {
    int damage = hero->getAtk() - def;
    if (damage > 0) {
        hp -= damage;  // ���˵�Ѫ
    }
    if (hp <= 0) {
        std::cout << "����������" << std::endl;
        return true;
    }
    damage = atk - hero->getDef();
    if (damage > 0) {
        hero->setHp(hero->getHp() - damage); // Ӣ�۵�Ѫ
    }
    if (hero->getHp() <= 0) {
        std::cout << "Ӣ��������" << std::endl;
        return false;
    }
    return true;
}

// �����̽�������������ѭ���д����̵���棬��������ֻ���� true��
bool Salesman::interact(Hero* hero) {
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
