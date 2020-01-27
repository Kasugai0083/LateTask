#pragma once

#include <windows.h>

LRESULT CALLBACK WndProc(HWND hWnd, UINT mes, WPARAM wParam, LPARAM lParam);

HWND MakeWindow(float width, float height);