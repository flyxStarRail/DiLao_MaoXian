#pragma once
#include <iostream>
#include <fstream>
#include <format>
#include "Props.h"
#include "Charactor.h"

using namespace std;

class Hero;

class Block
{
protected:
    bool flag;
public:
    Block(bool f) :flag(f) {};
    virtual ~Block() {};
    void change_flag() { flag = !flag; };
    bool getflag() { return flag; };
    virtual bool interact(Hero* hero) = 0;
    //virtual bool interactor() = 0;
    virtual void print(int x, int y) = 0;
    virtual void restart() { if (!flag) { flag = 1; } };
#ifdef MAP_EXPORT
    virtual void out(int x, int y, int index, int map_index, ofstream& fout) = 0;
#endif // MAP_EXPORT
};

typedef Block Target;

class Person  {
protected:
    int atk, def, hp;
public:
    Person(int atk, int hp, int def) : atk(atk), hp(hp), def(def) {}
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
    bool interact_lock = false;
    HeroMoveAttribute* attr;
public:
    Hero(int atk, int hp, int def = 0, int gold = 0)
        : Person(atk, hp, def), gold(gold){
    }
    bool interact(Target* target) {
        if (interact_lock == true) return false;
        lock_interact();
        return target->interact(this);
    }
    void lock_interact(){ interact_lock = true; }
    void release_interact() { interact_lock = false; };
    void dead() { is_dead = true; };
    bool get_is_dead() { return is_dead; };
    void link_attr(HeroMoveAttribute* temp) { attr = temp; };
    void clearattr() { attr->attrclear(); };
    int getGold() const { return gold; }
    void setGold(int g) { gold = g; }
    HeroMoveAttribute* getattr() { return attr; };
    void print();
    bool win(int end);
};

// 敌人类
class Enermy : public Person,virtual public Block 
{
protected:
    int full_hp;
    static unique_ptr<IMAGE> img;
public:
    Enermy(int atk, int hp, int def = 0) : Person(atk, hp, def),Block(0), full_hp(hp){};
    ~Enermy() { }
    void print(int x, int y);
    static void img_init();
    bool interact(Hero* hero) override;
    void restart();
#ifdef MAP_EXPORT
    void out(int x, int y, int index, int map_index, ofstream& fout);
#endif // MAP_EXPORT
    
};

// 商人类
class Salesman : virtual public Block
{
protected:
    Shop* shop;
    static unique_ptr<IMAGE> img;
public:
    ~Salesman(){}
    void Enter(Hero* hero)
    {
        shop->ShopEnter(hero);
    };
    void link(Shop* temp) { shop = temp; };
    bool interact(Hero* hero) override;
    bool buyItem(Hero* hero);
    bool sellItem(Hero* hero);
    void print(int,int);
    void restart();
    Salesman() :Block(0),shop(nullptr){};
    void static img_init();
#ifdef MAP_EXPORT
    void out(int x, int y, int index, int map_index, ofstream& fout) {};
#endif // MAP_EXPORT
};
