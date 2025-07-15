#pragma once
#include <graphics.h>
class Enter
{
public:
	static void enter();
	static int judge(int x, int y);
	static void draw();
};

class Win
{
public:
	static void enter();
	static void draw();
	static int judge(int x,int y);
	static void Animate();
};

class Failed
{
public:
	static void draw();
};