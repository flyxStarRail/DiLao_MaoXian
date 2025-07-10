#include "Shop.h"
#include <graphics.h>

// Add a product to the shop
void ShopWindow::add_product(Product* temp) {
    if (!temp) temp = new Product;
    p.push_back(temp);
}

int getoperation(int x, int y) {
    if (x > SIZE / 2 - FONTSIZE * 2 && x < SIZE / 2 + FONTSIZE * 2) {
        if (y > 120 && y < 120 + FONTSIZE) return 1; // BUY
        if (y > 220 && y < 220 + FONTSIZE) return 2; // SELL
        if (y > 320 && y < 320 + FONTSIZE) return 0; // EXIT
    }
    return 4;
}

void ShopWindow::buyoperation(int x, int y) {
    int index = 1, index_c = 1;
    int item_x1, item_y1, item_x2, item_y2;
    for (int i = 0; i < min((int)p.size(), 10); i++) {
        if (!p[i]->getflag()) {
            item_x1 = SIZE / 2 - ITEMSIZE * 0.5 - 300 + 100 * index;
            item_y1 = 100 * index_c;
            item_x2 = item_x1 + ITEMSIZE;
            item_y2 = item_y1 + ITEMSIZE;
            if (x > item_x1 && x < item_x2 && y > item_y1 && y < item_y2) {
                p[i]->changeflag();
                std::cout << "购买物品编号：" << i << std::endl;
                return;
            }
            index++;
            if (index == 6) {
                index = 1;
                index_c++;
            }
        }
    }
}

void ShopWindow::selloperation(int x, int y) {
    int index = 1, index_c = 1;
    int item_x1, item_y1, item_x2, item_y2;
    for (int i = 0; i < min((int)p.size(), 10); i++) {
        if (p[i]->getflag()) {
            item_x1 = SIZE / 2 - ITEMSIZE * 0.5 - 300 + 100 * index;
            item_y1 = 100 * index_c;
            item_x2 = item_x1 + ITEMSIZE;
            item_y2 = item_y1 + ITEMSIZE;
            if (x > item_x1 && x < item_x2 && y > item_y1 && y < item_y2) {
                p[i]->changeflag();
                std::cout << "出售物品编号：" << i << std::endl;
                return;
            }
            index++;
            if (index == 6) {
                index = 1;
                index_c++;
            }
        }
    }
}

void ShopWindow::product_draw(bool product_flag) {
    cleardevice();
    int index = 1, index_c = 1;
    for (int i = 0; i < min((int)p.size(), 10); i++) {
        if (p[i]->getflag() == product_flag) {
            setfillcolor(RGB(128, 128, 128));
            fillrectangle(SIZE / 2 - ITEMSIZE * 0.5 - 300 + 100 * index,
                100 * index_c,
                SIZE / 2 - ITEMSIZE * 0.5 - 300 + 100 * index + 80,
                100 * index_c + ITEMSIZE);
            index++;
            if (index == 6) {
                index = 1;
                index_c++;
            }
        }
    }
    settextstyle(40, 40, "Courier");
    outtextxy(SIZE / 2 - FONTSIZE * 2, 320, "EXIT");
    FlushBatchDraw();
}

int ShopWindow::ShopEnter() {
    int x = 0, y = 0;
    bool running = true;
    ExMessage msg;
    while (running) {
        while (peekmessage(&msg)) {
            if (msg.message == WM_LBUTTONDOWN) {
                x = msg.x; y = msg.y;
                int flag = getoperation(x, y);
                switch (flag) {
                case 0: return 0;
                case 1: BUY_Enter(); break;
                case 2: SELL_Enter(); break;
                default: break;
                }
            }
        }
        cleardevice();
        settextstyle(40, 40, "Courier");
        outtextxy(SIZE / 2 - FONTSIZE * 2, 20, "SHOP");
        outtextxy(SIZE / 2 - FONTSIZE * 1.5, 120, "BUY");
        outtextxy(SIZE / 2 - FONTSIZE * 2, 220, "SELL");
        outtextxy(SIZE / 2 - FONTSIZE * 2, 320, "EXIT");
        FlushBatchDraw();
    }
    return 0;
}

int ShopWindow::SELL_Enter() {
    int x = 0, y = 0;
    bool running = true;
    ExMessage msg;
    FlushBatchDraw();
    while (running) {
        while (peekmessage(&msg)) {
            if (msg.message == WM_LBUTTONDOWN) {
                x = msg.x; y = msg.y;
                selloperation(x, y);
                int flag = getoperation(x, y);
                if (flag == 0) return 0;
            }
        }
        product_draw(1);
    }
    return 0;
}

int ShopWindow::BUY_Enter() {
    int x = 0, y = 0;
    bool running = true;
    ExMessage msg;
    FlushBatchDraw();
    while (running) {
        while (peekmessage(&msg)) {
            if (msg.message == WM_LBUTTONDOWN) {
                x = msg.x; y = msg.y;
                buyoperation(x, y);
                int flag = getoperation(x, y);
                if (flag == 0) return 0;
            }
        }
        product_draw(0);
        settextstyle(40, 40, "Courier");
        outtextxy(SIZE / 2 - FONTSIZE * 2, 320, "EXIT");
        FlushBatchDraw();
    }
    return 0;
}

Item::Item(LPCSTR& temp) {
    // (未实现加载图像)
}
