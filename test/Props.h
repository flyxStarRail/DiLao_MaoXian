#pragma once
#include <string>
#include <graphics.h>
#include <iostream>
#include "Macro.h"


class Hero;

using namespace std;

class Product
{
    bool flag;
public:
    bool getflag() const { return flag; }
    void changeflag() { flag = !flag; };//操作购买和出售
    Product() :flag(0) {};
};


class Props
    :public Product
{
    
protected:
    int data; // 数值
    int price; // 价格
    unique_ptr<IMAGE> img;
    Props(int data, int price) : data(data), price(price),img(nullptr){};
public:
    virtual ~Props() {};
    int getPrice() const { return price; }
    void set_img(std::string str);
    int get_data() { return data; };
    bool is_vailed(Hero* hero);
    void buy(Hero* hero);
    //virtual void getInfo(char* str, int length) const = 0;
    virtual void function(class Hero& hero) = 0; // 物品效果
    virtual string getInfo() const = 0;
    IMAGE* getimage() { return img.get(); };
};

class PotionRecover : public Props {
public:
    static std::string name;
    PotionRecover(int data, int price) : Props(data, price) {}
    void function(class Hero& hero) override; // 恢复英雄生命
    string getInfo() const override;
    //void getInfo(char* str, int length) const override;
};

class Weapon : public Props {
public:
    static std::string name;
    Weapon(int data, int price) : Props(data, price) {}
    void function(class Hero& hero) override; // 提高攻击
    //void getInfo(char* str, int length) const override;
    string getInfo() const override;
};

class Armor : public Props {
public:
    static std::string name;
    Armor(int data, int price) : Props(data, price) {}
    void function(class Hero& hero) override; // 提高防御
    string getInfo() const override;
    //void getInfo(char* str, int length) const override;
};