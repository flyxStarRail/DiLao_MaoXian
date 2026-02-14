#pragma once
#include <string>
#include <graphics.h>
#include <Windows.h>

//此头文件用作一些工具的封装

// 1. string(GBK) → wstring(Unicode)
std::wstring to_wstr(const std::string& s);

// 2. string 直接转 LPCTSTR（你最常用）
LPCTSTR to_lpctstr(const std::string& s);

//函数用来显示透明图像
void putimage_alpha(int x, int y, IMAGE* img);