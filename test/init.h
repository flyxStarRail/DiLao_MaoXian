#pragma once
#include "Charactor.h"
#include "Shop.h"
#include "Props.h"
#include "Area.h"
#include "Target.h"
#include "Enter.h"
#pragma comment(lib, "winmm.lib")

#define MAP_NUM 2

void init_Map_List(NewAreaList* ar_l[MAP_NUM]);

void load_background(IMAGE& img, int length);

void next_map(NewAreaList*& ar, NewAreaList* ar_l[], int& index, HeroMoveAttribute* hero, int*& x);

void restart(NewAreaList*& ar, NewAreaList* ar_l[], int& index, HeroMoveAttribute* hero, int*& x);
