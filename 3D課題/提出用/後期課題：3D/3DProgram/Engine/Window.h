#pragma once

#include <windows.h>

LRESULT CALLBACK WindowProc(HWND window_handle, UINT message_id, WPARAM wparam, LPARAM lparam);

bool MakeWindow();