#pragma once
#include <string>
#include <Windows.h>

// 1. string(GBK) → wstring(Unicode)
std::wstring to_wstr(const std::string& s);

// 2. string 直接转 LPCTSTR（你最常用）
LPCTSTR to_lpctstr(const std::string& s);
