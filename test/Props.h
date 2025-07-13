#pragma once
#pragma once
#include <string>
#include <graphics.h>
class Hero;

//class Item
//{
//    //�������ڴ����Ʒ�Ļ������ԣ�ͼƬ����δװ�أ�
//    //����
//protected:
//    //IMAGE* display_img;
//    std::string name;
//public:
//    Item() {};
//    Item(LPCSTR&);
//};


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
    Props(int data, int price) : data(data), price(price) {};
public:
    virtual ~Props() {};
    int getPrice() const { return price; }
    void set_img(IMAGE* temp) { img = temp;};
    int get_data() { return data; };
    virtual void getInfo() const = 0;
    virtual void function(class Hero& hero) = 0; // ��ƷЧ��
    IMAGE* getimage() { return img; };
};

class PotionRecover : public Props {
public:
    static std::string name;
    PotionRecover(int data, int price) : Props(data, price) {}
    void function(class Hero& hero) override; // �ָ�Ӣ������
    void getInfo() const override;
};

class Weapon : public Props {
public:
    static std::string name;
    Weapon(int data, int price) : Props(data, price) {}
    void function(class Hero& hero) override; // ��߹���
    void getInfo() const override;
};

class Armor : public Props {
public:
    static std::string name;
    Armor(int data, int price) : Props(data, price) {}
    void function(class Hero& hero) override; // ��߷���
    void getInfo() const override;
};

class SellITEM {
private:
    static int price[10];
    static IMAGE* itemCount[10];
    //vector<Props*> coll;
public:
    static int getPrice(int id);
    static void setItem(int id, Props* item);
    static void init();
};


