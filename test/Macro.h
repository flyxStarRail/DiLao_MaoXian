#pragma once
#pragma  warning( disable: 4244)

constexpr int SCREEN_WIDTH = 1600;
constexpr int SCREEN_HEIGHT = 900;
constexpr int AREASIZE = 600;
constexpr int BLOCKSIZE = 40;
constexpr double K = static_cast<double>(SCREEN_HEIGHT) / AREASIZE / 7 * 6;
constexpr int DRAW_HEIGHT = SCREEN_HEIGHT / 7 * 6;
constexpr int DRAW_WIDTH = AREASIZE * (SCREEN_WIDTH / DRAW_HEIGHT);
constexpr int SELLITEM_SIZE = 10;
constexpr double ITEMSIZE = 80 * K;
constexpr int FONTSIZE = static_cast<int> (BLOCKSIZE * K);
constexpr double MYSIZE = 600 * K;
//#define MYSIZE  600 * K
constexpr int MAP_NUM = 2;
constexpr int SCREENSIZE = static_cast<int>(600 * K);


//对以下解注释以解锁MapEditor
#define DEBUG
#ifdef DEBUG
#define ERASOR
#define MAP_EXPORT
#endif // DEBUG

//用来存放宏定义
