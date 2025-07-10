#include <graphics.h>
#include <vector>
#include <tchar.h>
#include <iostream>
#include "Map.h"
#include "Charactor.h"
#include "Target.h"
#include "Shop.h"

int main() {
    // ��ʼ������
    initgraph(600, 600);
    BeginBatchDraw(); // ˫�����ͼ:contentReference[oaicite:4]{index=4}

    IMAGE bgImg, heroImg;
    loadimage(&bgImg, _T("background.png"), 1800, 600);
    loadimage(&heroImg, _T("charactor.png"), 40, 40);

    // ����Ӣ�ۣ�ͼ�β��ֺ����Բ��֣�
    HeroMoveAttribute heroGfx(10, 250);    // ��ʼλ��
    Hero heroStats(10, 100, 5, 50);        // ATK=10, HP=100, DEF=5, gold=50

    // ��ʼ����ͼ���ϰ��3 ��������ÿ�����600��
    Map map;
    // ����0�ϰ�
    map.addObstacle(100, 400, 200, 450);
    map.addObstacle(300, 150, 350, 300);
    // ����1�ϰ���x ����� 600��
    map.addObstacle(650, 100, 750, 150);
    map.addObstacle(800, 300, 900, 350);
    // ����2�ϰ���x ����� 1200��
    map.addObstacle(1300, 200, 1350, 250);

    // ������˶���ṹ
    struct EnemyObj { Enermy enemy; int x, y; bool alive; };
    vector<EnemyObj> enemies;
    enemies.push_back({ Enermy(8, 20, 2),   250,   250, true });
    enemies.push_back({ Enermy(5, 15, 1),   500,   100, true });
    enemies.push_back({ Enermy(12, 30, 3),  650,   400, true });
    enemies.push_back({ Enermy(10, 25, 2),  900,   200, true });
    enemies.push_back({ Enermy(15, 40, 5),  1350,  100, true });
    enemies.push_back({ Enermy(7, 10, 1),   1600,  350, true });

    // ���˶���
    struct MerchantObj { Salesman merchant; int x, y; bool interacted; };
    MerchantObj merchant = { Salesman(), 800, 250, false };

    ShopWindow shop; // �̵����

    bool running = true;
    ExMessage msg;
    int screenX = 0;       // ���ˮƽƫ��
    bool engagedEnemy = false;
    int engagedIndex = -1;

    while (running) {
        // ����������Ϣ
        while (peekmessage(&msg)) {
            heroGfx.judge(msg, running, shop);
        }
        // �����λ���Ա���ײ��ԭ
        int oldX = heroGfx.getX() , oldY = heroGfx.getY();
        // �ƶ�Ӣ�۲�������ͼ
        heroGfx.move(screenX);

        // ���ϰ�����ײ��⣬����ײ��ԭλ��
        if (map.checkCollision(heroGfx.getX() + screenX, heroGfx.getY(), 40, 40)) {
            heroGfx.setX(oldX);
            heroGfx.setY(oldY);
            // ���ı� screenX ���ֲ�����
        }

        // �����Ƿ�����˽�����־
        engagedEnemy = false;
        engagedIndex = -1;
        // Ӣ��-���˽���
        for (int i = 0; i < enemies.size(); i++) {
            if (!enemies[i].alive) continue;
            int ex = enemies[i].x - screenX;
            int ey = enemies[i].y;
            // �򵥰�Χ����ײ���
            if (heroGfx.getX() < ex + 40 && heroGfx.getX() + 40 > ex &&
                heroGfx.getY() < ey + 40 && heroGfx.getY() + 40 > ey) {
                engagedEnemy = true;
                engagedIndex = i;
                // ս������
                heroStats.interact(&(enemies[i].enemy));
                // �������������ִ�н���Ч�����Ƴ�
                if (enemies[i].enemy.getHp() <= 0) {
                    for (int k = 0; k <= 30; k++) {
                        int redVal = 255 * (30 - k) / 30;
                        setfillcolor(RGB(redVal, 0, 0));
                        fillrectangle(ex, ey, ex + 40, ey + 40);
                        FlushBatchDraw();
                        Sleep(20);
                    }
                    enemies[i].alive = false;
                }
                break;
            }
        }
        // Ӣ��-���˽���
        int mx = merchant.x - screenX, my = merchant.y;
        if (!merchant.interacted &&
            heroGfx.getX() < mx + 40 && heroGfx.getX() + 40 > mx &&
            heroGfx.getY() < my + 40 && heroGfx.getY() + 40 > my) {
            merchant.interacted = true;
            // ���̵����
            shop.ShopEnter();
            // ʾ�����������ָ�ҩˮ +20 HP
            PotionRecover potion(20, 10);
            potion.function(heroStats);
        }

        // ���Ƴ���
        cleardevice();
        putimage(0, 0, 600, 600, &bgImg, screenX, 0, SRCCOPY);
        // �ϰ����ɫ���飩
        map.draw(screenX);
        // ���ˣ���ɫ���飩
        setfillcolor(RGB(255, 0, 0));
        for (int i = 0; i < enemies.size(); i++) {
            if (!enemies[i].alive) continue;
            int ex = enemies[i].x - screenX;
            int ey = enemies[i].y;
            if (ex >= -40 && ex <= 600) {
                fillrectangle(ex, ey, ex + 40, ey + 40);
            }
        }
        // ���ˣ���ɫ���飩
        setfillcolor(RGB(0, 0, 255));
        int drawMx = merchant.x - screenX;
        if (drawMx >= -40 && drawMx <= 600) {
            fillrectangle(drawMx, merchant.y, drawMx + 40, merchant.y + 40);
        }
        // �滻 heroGfx.put_solided();
        putimage(heroGfx.getX(), heroGfx.getY(), &heroImg);


        // ��ʾӢ�����ԣ����Ͻǣ�:contentReference[oaicite:5]{index=5}
        settextcolor(RGB(255, 255, 255));
        settextstyle(20, 0, _T("Arial"));
        TCHAR buf[50];
        _stprintf(buf, _T("HP: %d"), heroStats.getHp());
        outtextxy(10, 10, buf);
        _stprintf(buf, _T("ATK: %d"), heroStats.getAtk());
        outtextxy(10, 40, buf);
        _stprintf(buf, _T("DEF: %d"), heroStats.getDef());
        outtextxy(10, 70, buf);
        // �������˽������������Ͻ���ʾ��������
        if (engagedEnemy && engagedIndex >= 0) {
            heroGfx.setX(oldX);
            heroGfx.setY(oldY);
            Enermy& e = enemies[engagedIndex].enemy;
            _stprintf(buf, _T("EN_HP: %d"), e.getHp());
            outtextxy(400, 10, buf);
            _stprintf(buf, _T("EN_ATK: %d"), e.getAtk());
            outtextxy(400, 40, buf);
        }
        // Ӣ�۽�ң����ϣ�
        _stprintf(buf, _T("Gold: %d"), heroStats.getGold());
        outtextxy(400, 70, buf);

        FlushBatchDraw();
        Sleep(30);
    }

    EndBatchDraw();
    closegraph();
    return 0;
}
