#pragma once
#include "Charactor.h"
#include "Shop.h"
#include "Props.h"
#include "Area.h"
#include "Target.h"
#include "Enter.h"
#include "Macro.h"
#include "fstream"
#pragma comment(lib, "winmm.lib")

void init_Map_List(vector<NewAreaList*>& ar_l, int& length, int& _map_num);

void load_background(IMAGE& img, int length);

void next_map(NewAreaList*& ar, vector<NewAreaList*>& ar_l, int& index, HeroMoveAttribute* hero, int*& x);

void restart(NewAreaList*& ar, vector<NewAreaList*>& ar_l, int& index, HeroMoveAttribute* hero, int*& x);
