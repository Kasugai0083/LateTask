#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include "DirectX.h"
#include <vector>

// 静的ライブラリ
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

extern LPDIRECT3D9 g_pD3DInterface;	// DirectXインターフェース
extern D3DPRESENT_PARAMETERS* g_pD3DPresentParam;
extern LPDIRECT3DDEVICE9 g_pD3DDevice;

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


int APIENTRY WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR     lpCmpLine,
	INT       nCmdShow)
{
	HWND hWnd;
	WNDCLASSEX window_class = {
		sizeof(WNDCLASSEX),				// 構造体のサイズ
		CS_HREDRAW | CS_VREDRAW,		// クラスのスタイル
		WindowProc,						// ウィンドウプロシージャ
		0,								// 補助メモリ
		0,								// 補助メモリ
		hInstance,						// このプログラムのインスタンスハンドル
		LoadIcon(NULL, MAKEINTRESOURCE(IDI_APPLICATION)),// アイコン画像
		LoadCursor(NULL, IDC_ARROW),	// カーソル画像
		NULL,							// 背景ブラシ(背景色)
		NULL,							// メニュー名
		TEXT("First3DProgram"),			// クラス名									
		NULL							// 小さいアイコン
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
		hInstance,
		NULL);

	if (hWnd == NULL)
	{
		return false;
	}

	//DirectXの初期化
	if (InitDirectX(hWnd) == false)
	{
		return false;
	}

	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);

	while (true)
	{
		bool message_ret = false;
		MSG msg;

		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				break;
			}
			else {
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else {

			//座標変換
			Transform();

			//描画
			//Draw();

			D3DXVECTOR3 pos1(0.f, 0.f, 0.f);
			D3DXVECTOR3 pos2(3.f, 0.f, 0.f);

			std::vector<Vec3> Lines;

			Vec3 v1(1.f,1.f,0.f);
			Vec3 v2(10.f,1.f,0.f);
			Vec3 v3(10.f,10.f,0.f);
			Vec3 v4(10.f,-10.f,0.f);

			Lines.push_back(v1);
			Lines.push_back(v2);
			//Lines.push_back(v3);
			//Lines.push_back(v4);

			DWORD color = D3DCOLOR_ARGB(255, 255, 255, 255);

			DrawLine(Lines, color);
			//DrawLine(pos1, pos2);

		}
	}
}
