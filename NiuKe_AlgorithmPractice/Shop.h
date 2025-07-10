#pragma once
#include <graphics.h>
#pragma comment(lib, "MSIMG32.LIB")
#include <iostream>
#include <string>
#include <vector>
#define ITEMSIZE 80
#define FONTSIZE 40
#define SIZE 600

class Item {
protected:
    IMAGE* img;
    std::string name;
public:
    Item() {};
    Item(LPCSTR& path);
};

class Product : public Item {
    bool flag;
    int price;
public:
    bool getflag() const { return flag; }
    void changeflag() { flag = !flag; }
    Product() : flag(0) {}
};

class ShopWindow {
public:
    int ShopEnter();
    int BUY_Enter();
    int SELL_Enter();
    void add_product(Product*);
    void buyoperation(int x, int y);
    void selloperation(int x, int y);
    void product_draw(bool product_flag);
protected:
    std::vector<Product*> p;
};


