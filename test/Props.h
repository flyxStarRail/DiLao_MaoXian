#pragma once
#pragma once
#include <string>
#include <graphics.h>
class Hero;

class Product
    //:public Item
{
    bool flag;
public:
    bool getflag() const { return flag; }
    void changeflag() { flag = !flag; };//��������ͳ���
    Product() :flag(0) {};
};


class Props
    :public Product
{
protected:
    int data; // ��ֵ
    int price; // �۸�
    IMAGE* img;
    Props(int data, int price) : data(data), price(price),img(nullptr){};
public:
    virtual ~Props() {};
    int getPrice() const { return price; }
    void set_img(IMAGE* temp) { img = temp;};
    int get_data() { return data; };
    bool is_vailed(Hero* hero);
    void buy(Hero* hero);
    virtual void getInfo(char* str, int length) const = 0;
    virtual void function(class Hero& hero) = 0; // ��ƷЧ��
    IMAGE* getimage() { return img; };
};

class PotionRecover : public Props {
public:
    static std::string name;
    PotionRecover(int data, int price) : Props(data, price) {}
    void function(class Hero& hero) override; // �ָ�Ӣ������
    void getInfo(char* str, int length) const override;
};

class Weapon : public Props {
public:
    static std::string name;
    Weapon(int data, int price) : Props(data, price) {}
    void function(class Hero& hero) override; // ��߹���
    void getInfo(char* str, int length) const override;
};

class Armor : public Props {
public:
    static std::string name;
    Armor(int data, int price) : Props(data, price) {}
    void function(class Hero& hero) override; // ��߷���
    void getInfo(char* str, int length) const override;
};

