#include <graphics.h>
#include <vector>
#include <tchar.h>
#include <iostream>
#include "Map.h"
#include "Charactor.h"
#include "Target.h"
#include "Shop.h"

int main() {
    // 初始化窗口
    initgraph(600, 600);
    BeginBatchDraw(); // 双缓冲绘图:contentReference[oaicite:4]{index=4}

    IMAGE bgImg, heroImg;
    loadimage(&bgImg, _T("background.png"), 1800, 600);
    loadimage(&heroImg, _T("charactor.png"), 40, 40);

    // 创建英雄（图形部分和属性部分）
    HeroMoveAttribute heroGfx(10, 250);    // 初始位置
    Hero heroStats(10, 100, 5, 50);        // ATK=10, HP=100, DEF=5, gold=50

    // 初始化地图和障碍物（3 个场景，每个宽度600）
    Map map;
    // 场景0障碍
    map.addObstacle(100, 400, 200, 450);
    map.addObstacle(300, 150, 350, 300);
    // 场景1障碍（x 坐标加 600）
    map.addObstacle(650, 100, 750, 150);
    map.addObstacle(800, 300, 900, 350);
    // 场景2障碍（x 坐标加 1200）
    map.addObstacle(1300, 200, 1350, 250);

    // 定义敌人对象结构
    struct EnemyObj { Enermy enemy; int x, y; bool alive; };
    vector<EnemyObj> enemies;
    enemies.push_back({ Enermy(8, 20, 2),   250,   250, true });
    enemies.push_back({ Enermy(5, 15, 1),   500,   100, true });
    enemies.push_back({ Enermy(12, 30, 3),  650,   400, true });
    enemies.push_back({ Enermy(10, 25, 2),  900,   200, true });
    enemies.push_back({ Enermy(15, 40, 5),  1350,  100, true });
    enemies.push_back({ Enermy(7, 10, 1),   1600,  350, true });

    // 商人对象
    struct MerchantObj { Salesman merchant; int x, y; bool interacted; };
    MerchantObj merchant = { Salesman(), 800, 250, false };

    ShopWindow shop; // 商店界面

    bool running = true;
    ExMessage msg;
    int screenX = 0;       // 相机水平偏移
    bool engagedEnemy = false;
    int engagedIndex = -1;

    while (running) {
        // 处理输入消息
        while (peekmessage(&msg)) {
            heroGfx.judge(msg, running, shop);
        }
        // 保存旧位置以便碰撞后还原
        int oldX = heroGfx.getX() , oldY = heroGfx.getY();
        // 移动英雄并滚动视图
        heroGfx.move(screenX);

        // 与障碍物碰撞检测，若碰撞则还原位置
        if (map.checkCollision(heroGfx.getX() + screenX, heroGfx.getY(), 40, 40)) {
            heroGfx.setX(oldX);
            heroGfx.setY(oldY);
            // 不改变 screenX 保持不滚动
        }

        // 重置是否与敌人交互标志
        engagedEnemy = false;
        engagedIndex = -1;
        // 英雄-敌人交互
        for (int i = 0; i < enemies.size(); i++) {
            if (!enemies[i].alive) continue;
            int ex = enemies[i].x - screenX;
            int ey = enemies[i].y;
            // 简单包围盒碰撞检测
            if (heroGfx.getX() < ex + 40 && heroGfx.getX() + 40 > ex &&
                heroGfx.getY() < ey + 40 && heroGfx.getY() + 40 > ey) {
                engagedEnemy = true;
                engagedIndex = i;
                // 战斗交互
                heroStats.interact(&(enemies[i].enemy));
                // 如果敌人已死，执行渐隐效果再移除
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
        // 英雄-商人交互
        int mx = merchant.x - screenX, my = merchant.y;
        if (!merchant.interacted &&
            heroGfx.getX() < mx + 40 && heroGfx.getX() + 40 > mx &&
            heroGfx.getY() < my + 40 && heroGfx.getY() + 40 > my) {
            merchant.interacted = true;
            // 打开商店界面
            shop.ShopEnter();
            // 示例购买：生命恢复药水 +20 HP
            PotionRecover potion(20, 10);
            potion.function(heroStats);
        }

        // 绘制场景
        cleardevice();
        putimage(0, 0, 600, 600, &bgImg, screenX, 0, SRCCOPY);
        // 障碍物（棕色方块）
        map.draw(screenX);
        // 敌人（红色方块）
        setfillcolor(RGB(255, 0, 0));
        for (int i = 0; i < enemies.size(); i++) {
            if (!enemies[i].alive) continue;
            int ex = enemies[i].x - screenX;
            int ey = enemies[i].y;
            if (ex >= -40 && ex <= 600) {
                fillrectangle(ex, ey, ex + 40, ey + 40);
            }
        }
        // 商人（蓝色方块）
        setfillcolor(RGB(0, 0, 255));
        int drawMx = merchant.x - screenX;
        if (drawMx >= -40 && drawMx <= 600) {
            fillrectangle(drawMx, merchant.y, drawMx + 40, merchant.y + 40);
        }
        // 替换 heroGfx.put_solided();
        putimage(heroGfx.getX(), heroGfx.getY(), &heroImg);


        // 显示英雄属性（左上角）:contentReference[oaicite:5]{index=5}
        settextcolor(RGB(255, 255, 255));
        settextstyle(20, 0, _T("Arial"));
        TCHAR buf[50];
        _stprintf(buf, _T("HP: %d"), heroStats.getHp());
        outtextxy(10, 10, buf);
        _stprintf(buf, _T("ATK: %d"), heroStats.getAtk());
        outtextxy(10, 40, buf);
        _stprintf(buf, _T("DEF: %d"), heroStats.getDef());
        outtextxy(10, 70, buf);
        // 如果与敌人交互，则在右上角显示敌人属性
        if (engagedEnemy && engagedIndex >= 0) {
            heroGfx.setX(oldX);
            heroGfx.setY(oldY);
            Enermy& e = enemies[engagedIndex].enemy;
            _stprintf(buf, _T("EN_HP: %d"), e.getHp());
            outtextxy(400, 10, buf);
            _stprintf(buf, _T("EN_ATK: %d"), e.getAtk());
            outtextxy(400, 40, buf);
        }
        // 英雄金币（右上）
        _stprintf(buf, _T("Gold: %d"), heroStats.getGold());
        outtextxy(400, 70, buf);

        FlushBatchDraw();
        Sleep(30);
    }

    EndBatchDraw();
    closegraph();
    return 0;
}
