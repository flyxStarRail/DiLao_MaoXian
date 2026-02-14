#pragma once
#include "Tool.h"

// 1. string(GBK) → wstring(Unicode)
std::wstring to_wstr(const std::string& s) {
    int len = MultiByteToWideChar(CP_ACP, 0,
        s.c_str(), (int)s.size(), nullptr, 0);
    std::wstring res(len, 0);
    MultiByteToWideChar(CP_ACP, 0,
        s.c_str(), (int)s.size(), &res[0], len);
    return res;
}

// 2. string 直接转 LPCTSTR（你最常用）
LPCTSTR to_lpctstr(const std::string& s) {
    static std::wstring cache;
    cache = to_wstr(s);
    return cache.c_str();
}

void putimage_alpha(int x, int y, IMAGE* img)
{
 
    int w = img->getwidth();
    int h = img->getheight();
    AlphaBlend(GetImageHDC(NULL), x, y, w, h, GetImageHDC(img), 0, 0, w, h, { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA });
}
