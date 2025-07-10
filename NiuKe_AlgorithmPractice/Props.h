#pragma once
#pragma once
#include <string>
#include <graphics.h>
class Hero;

class Props {
protected:
    int data; // 数值
    int price; // 价格
    static IMAGE* img;
    Props(int data, int price) : data(data), price(price) {}
public:
    virtual ~Props() {}
    int getPrice() const { return price; }
    virtual void getInfo() const = 0;
    virtual void function(class Hero& hero) = 0; // 物品效果
};

class PotionRecover : public Props {
public:
    static std::string name;
    PotionRecover(int data, int price) : Props(data, price) {}
    void function(class Hero& hero) override; // 恢复英雄生命
    void getInfo() const override;
};

class Weapon : public Props {
public:
    static std::string name;
    Weapon(int data, int price) : Props(data, price) {}
    void function(class Hero& hero) override; // 提高攻击
    void getInfo() const override;
};

class Armor : public Props {
public:
    static std::string name;
    Armor(int data, int price) : Props(data, price) {}
    void function(class Hero& hero) override; // 提高防御
    void getInfo() const override;
};

class SellITEM {
private:
    static int price[10];
    static IMAGE* itemCount[10];
public:
    static int getPrice(int id);
    static void setItem(int id, Props* item);
    static void init();
};


