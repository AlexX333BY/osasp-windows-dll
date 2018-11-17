#pragma once

#include <Windows.h>

__declspec(dllexport) INT64 __stdcall Min(INT64 iX, INT64 iY);
__declspec(dllexport) INT64 __stdcall Max(INT64 iX, INT64 iY);
__declspec(dllexport) LPSTR __stdcall GetCurrentProcessName();
