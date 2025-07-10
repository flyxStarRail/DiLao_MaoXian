#pragma once
#include <iostream>
#include "Props.h"
using namespace std;
class Hero;
class Target {
public:
    virtual bool interact(Hero* hero) = 0; // 纯虚交互
};

// NPC（基类，无特殊行为）
class NPC : public Target {
public:
    bool interact(Hero* hero) override {
        return true;
    }
};

class Person : public Target {
protected:
    int atk, def, hp;
public:
    Person(int atk, int hp, int def) : atk(atk), hp(hp), def(def) {}
    virtual ~Person() {}
    // 虚拟交互由子类实现
    int getAtk() const { return atk; }
    int getDef() const { return def; }
    int getHp() const { return hp; }
    void setHp(int hp) { this->hp = hp; }
    void setAtk(int atk) { this->atk = atk; }
    void setDef(int def) { this->def = def; }
};

// 英雄类
class Hero : public Person {
protected:
    int SellItemID[10] = { 0 };
    int gold;
public:
    Hero(int atk, int hp, int def = 0, int gold = 0)
        : Person(atk, hp, def), gold(gold) {
    }
    bool interact(Target* target) {
        return target->interact(this);
    }
    bool interact(Hero* other) {
        cout << "Hello" << endl;
        return true;
    }
    int getGold() const { return gold; }
    void setGold(int g) { gold = g; }
};

// 敌人类
class Enermy : public Person {
public:
    Enermy(int atk, int hp, int def = 0) : Person(atk, hp, def) {}
    bool interact(Hero* hero) override;
};

// 商人类
class Salesman : public NPC {
protected:
    Props* itemList[10];
    int itemCount[10] = { 0 };
public:
    bool interact(Hero* hero) override;
    bool buyItem(Hero* hero);
    bool sellItem(Hero* hero);
};

