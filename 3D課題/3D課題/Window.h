#pragma once

#include <Windows.h>
#include <string>
#include "Size.h"


#define WINDOW_CLASS_NAME TEXT("Window")	//!< ウィンドウクラス名


class Window {
public:

	Window()
	{
		m_hWnd = nullptr;
	}

	bool MakeWindow(Size size, const char* title);
	
	HWND GetWindowHandle(){ return m_hWnd; }

private:

	HWND m_hWnd;

};


