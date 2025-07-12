#pragma once
#include <iostream>
#include "Props.h"
#include "Charactor.h"

using namespace std;

class Hero;


//class Target {
//public:
//    virtual bool interact(Hero* hero) = 0; // 纯虚交互
//};


class Block
{
protected:
    bool flag;
public:
    Block(bool f) :flag(f) {};
    void change_flag() { flag = !flag; };
    bool getflag() { return flag; };
    virtual bool interact(Hero* hero) = 0;
    //virtual bool interactor() = 0;
    virtual void print(int x, int y) = 0;
};

typedef Block Target;

// NPC（基类，无特殊行为）
//class NPC :virtual public Block {
//public:
//    bool interact(Hero* hero) override {
//        return true;
//    }
//};

class Person  {
protected:
    int atk, def, hp;
public:
    Person(int atk, int hp, int def) : atk(atk), hp(hp), def(def) {}
    //virtual ~Person() {}
    // 虚拟交互由子类实现
    int getAtk() const { return atk; }
    int getDef() const { return def; }
    int getHp() const { return hp; }
    void setHp(int hp) { this->hp = hp; }
    void setAtk(int atk) { this->atk = atk; }
    void setDef(int def) { this->def = def; }
};

// 英雄类
class Hero : 
    public Person 
{
protected:
    int SellItemID[10] = { 0 };
    int gold;
    bool is_dead = false;
    HeroMoveAttribute* attr;
    //SellITEM* sold;
public:
    Hero(int atk, int hp, int def = 0, int gold = 0)
        : Person(atk, hp, def), gold(gold){
    }
    bool interact(Target* target) {
        return target->interact(this);
    }
    void dead() { is_dead = true; };
    //bool interact(Hero* other) {
    //    //cout << "Hello" << endl;
    //    return true;
    //}
    bool get_is_dead() { return is_dead; };
    void link_attr(HeroMoveAttribute* temp) { attr = temp; };
    void clearattr() { attr->attrclear(); };
    int getGold() const { return gold; }
    void setGold(int g) { gold = g; }
    HeroMoveAttribute* getattr() { return attr; };
    void print();
};

// 敌人类
class Enermy : public Person,virtual public Block 
{
protected:
    static IMAGE* img;
public:
    Enermy(int atk, int hp, int def = 0) : Person(atk, hp, def),Block(0) {};
    void print(int x, int y);
    static void img_init();
    bool interact(Hero* hero) override;
};

// 商人类
class Salesman : virtual public Block
{
protected:
    //Props* itemList[10];
    Shop* shop;
    static IMAGE* img;
    //int itemCount[10] = { 0 };
public:
    void Enter(Hero* hero)
    {
        shop->ShopEnter(hero);
    };
    void link(Shop* temp) { shop = temp; };
    bool interact(Hero* hero) override;
    bool buyItem(Hero* hero);
    bool sellItem(Hero* hero);
    void print(int,int);
    Salesman() :Block(0){};
    void static img_init();
};
