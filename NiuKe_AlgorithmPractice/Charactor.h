#pragma once
#pragma once
#include <graphics.h>
#include "Shop.h"

// Basic movement attributes (position, speed)
class CharactorMoveAttribute {
protected:
    int x, y;
    bool isSpeed; // speed key pressed
    int step;     // step length
public:
    CharactorMoveAttribute(int x = 0, int y = 0);
};

// Hero movement and state (image, direction)
class HeroMoveAttribute : public CharactorMoveAttribute {
protected:
    bool isLeft, isRight, isUp, isDown;
    IMAGE img;   // Hero image (40¡Á40)
public:
    HeroMoveAttribute(int x, int y);
    // Move hero and scroll the view (screen_x) if needed
    void move(int& screen_x);
    // Handle keyboard input (movement keys and exit; no shop key)
    void judge(ExMessage& msg, bool& running, ShopWindow& shop);
    // Draw hero with alpha transparency
    void put_solided();
    int getX() const { return x; }
    int getY() const { return y; }
    void setX(int newX) { x = newX; }
    void setY(int newY) { y = newY; }
};

// Unused enemy movement class (placeholder)
class EnermyMoveAttribute {
public:
    EnermyMoveAttribute();
};

// Draw IMAGE with alpha transparency
void putimage_alpha(int x, int y, IMAGE* img);

