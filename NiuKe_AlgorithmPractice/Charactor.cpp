#include "Charactor.h"

// Draw image with alpha transparency
void putimage_alpha(int x, int y, IMAGE* img) {
    int w = img->getwidth();
    int h = img->getheight();
    AlphaBlend(GetImageHDC(NULL), x, y, w, h, GetImageHDC(img),
        0, 0, w, h, { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA });
}

// Hero constructor: set position and load image
HeroMoveAttribute::HeroMoveAttribute(int x, int y) : CharactorMoveAttribute(x, y) {
    isDown = isLeft = isRight = isUp = isSpeed = false;
    loadimage(&img, _T("charactor.png"), 40, 40, false);
}

// Move hero and scroll the view (screen_x)
void HeroMoveAttribute::move(int& screen_x) {
    step = isSpeed ? 10 : 5;
    if (isLeft) {
        x -= (step - 5);
        screen_x -= 5;
    }
    if (isRight) {
        x += (step - 5);
        screen_x += 5;
    }
    if (isUp) {
        y -= step;
    }
    if (isDown) {
        y += step;
    }
    // Clamp hero position and camera
    if (x > 500) x = 500;
    if (x < 10)  x = 10;
    if (y > 450) y = 450;
    if (y < 10)  y = 10;
    if (screen_x < 0) screen_x = 0;
    if (screen_x > 1200) screen_x = 1200; // 3 scenes ¡Á 600¿í
}

// Handle key events: movement (WASD/¼ýÍ·), speed, exit
void HeroMoveAttribute::judge(ExMessage& msg, bool& running, ShopWindow& shop) {
    if (msg.message == WM_KEYDOWN) {
        switch (msg.vkcode) {
        case 'W': case VK_UP:    isUp = true;    break;
        case 'S': case VK_DOWN:  isDown = true;  break;
        case 'A': case VK_LEFT:  isLeft = true;  break;
        case 'D': case VK_RIGHT: isRight = true; break;
        case 'H':               isSpeed = true; break;
        case VK_ESCAPE: running = false;         break;
        }
    }
    if (msg.message == WM_KEYUP) {
        switch (msg.vkcode) {
        case 'W': case VK_UP:    isUp = false;    break;
        case 'S': case VK_DOWN:  isDown = false;  break;
        case 'A': case VK_LEFT:  isLeft = false;  break;
        case 'D': case VK_RIGHT: isRight = false; break;
        case 'H':               isSpeed = false; break;
        }
    }
}

// Draw hero with transparency
void HeroMoveAttribute::put_solided() {
    putimage_alpha(x, y, &img);
}

// Constructor
CharactorMoveAttribute::CharactorMoveAttribute(int x, int y) {
    this->x = x;
    this->y = y;
    step = 5;
}

// Enemy constructor (unused)
EnermyMoveAttribute::EnermyMoveAttribute() {}
