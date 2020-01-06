#pragma comment (lib, "dxguid.lib")
#pragma comment (lib, "dsound.lib")
#pragma comment (lib, "winmm.lib")

#include <tchar.h>
#include <dsound.h>
#include <mmsystem.h>
#include "Window.h"

LRESULT CALLBACK WindowProc(HWND window_handle_, UINT message_id_, WPARAM wparam_, LPARAM lparam_) 
{
	switch(message_id_)
	{
	case WM_CLOSE:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(window_handle_, message_id_, wparam_, lparam_);
		break;
	}
	return 0;
}

bool Window::MakeWindow(Size size_, const char* title_) 
{
	WNDCLASSEX window_class = 
	{
		sizeof(WNDCLASSEXA),			// 構造体のサイズ
		CS_HREDRAW | CS_VREDRAW,		// クラスのスタイル
		WindowProc,						// ウィンドウプロシージャ
		0,								// 補助メモリ
		0,								// 補助メモリ
		GetModuleHandle(nullptr),		// このプログラムのインスタンスハンドル
		LoadIcon(NULL, IDI_APPLICATION),// アイコン画像
		LoadCursor(NULL, IDC_ARROW),	// カーソル画像
		NULL,							// 背景ブラシ(背景色)
		NULL,							// メニュー名
		WINDOW_CLASS_NAME,				// クラス名									
		NULL							// 小さいアイコン
	};

	// 構造体の登録
	if(RegisterClassEx(&window_class) == 0)
	{
		return 0;
	}

	// ウィンドウ作成
	m_hWnd = CreateWindowA(
		WINDOW_CLASS_NAME,
		title_,
		(WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME) | WS_VISIBLE,
		CW_USEDEFAULT,
		0,
		size_.Width,
		size_.Height,
		NULL,
		NULL,
		GetModuleHandle(nullptr),
		NULL
	);

	RECT window_rect;
	RECT client_rect;

	GetWindowRect(m_hWnd, &window_rect);
	GetClientRect(m_hWnd, &client_rect);

	int frame_size_x = (window_rect.right - window_rect.left) - (client_rect.right - client_rect.left);
	int frame_size_y = (window_rect.bottom - window_rect.top) - (client_rect.bottom - client_rect.top);

	SetWindowPos(m_hWnd, NULL, CW_USEDEFAULT, CW_USEDEFAULT, frame_size_x + size_.Width, frame_size_y + size_.Height, SWP_NOMOVE);

	ShowWindow(m_hWnd, SW_SHOW);
	UpdateWindow(m_hWnd);

	return m_hWnd;

}