#include "Window.h"
#include "Graphics/DirectX.h"

LRESULT CALLBACK WindowProc(HWND window_handle, UINT message_id, WPARAM wparam, LPARAM lparam)
{
	switch (message_id)
	{
	case WM_CLOSE:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(window_handle, message_id, wparam, lparam);
		break;
	}

	return 0;
}

bool MakeWindow() {

	DXManager* Ins_DXManager = DXManager::GetInstance();

	HWND hWnd;
	WNDCLASSEX window_class = {
		sizeof(WNDCLASSEX),									// 構造体のサイズ
		CS_HREDRAW | CS_VREDRAW,							// クラスのスタイル
		WindowProc,											// ウィンドウプロシージャ
		0,													// 補助メモリ
		0,													// 補助メモリ
		GetModuleHandle(nullptr),							// このプログラムのインスタンスハンドル
		LoadIcon(NULL, MAKEINTRESOURCE(IDI_APPLICATION)),	// アイコン画像
		LoadCursor(NULL, IDC_ARROW),						// カーソル画像
		NULL,												// 背景ブラシ(背景色)
		NULL,												// メニュー名
		TEXT("First3DProgram"),								// クラス名									
		NULL												// 小さいアイコン
	};

	// 構造体の登録
	if (RegisterClassEx(&window_class) == 0)
	{
		return false;
	}

	// ウィンドウ作成
	hWnd = CreateWindow(
		TEXT("First3DProgram"),
		TEXT("First3DProgram"),
		(WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME) | WS_VISIBLE,
		400,
		10,
		400,
		400,
		NULL,
		NULL,
		GetModuleHandle(nullptr),
		NULL);

	if (hWnd == NULL)
	{
		return false;
	}

	if (!Ins_DXManager->InitDirectX(hWnd))
	{
		return false;
	}

	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);

	return true;
}