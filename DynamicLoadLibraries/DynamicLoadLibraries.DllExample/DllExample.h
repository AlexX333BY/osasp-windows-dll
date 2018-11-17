#pragma once

#include <Windows.h>

__declspec(dllexport) int Min(int x, int y);
__declspec(dllexport) int Max(int x, int y);
__declspec(dllexport) LPTSTR GetCurrentProcessName();
