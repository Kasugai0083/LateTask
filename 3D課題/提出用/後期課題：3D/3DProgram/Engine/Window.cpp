#include "Window.h"
#include "Graphics/DirectX.h"

namespace {

	struct t_Point {
		POINT start = { 0,0 };//クリック時以外の座標を取得
		POINT end = { 0,0 };  //クリック時の座標を取得
	}pt;

	bool is_drag = false; //ドラッグ判定変数
	bool is_click = false;//ダブルクリック判定変数
};

LRESULT CALLBACK WindowProc(HWND window_handle, UINT message_id, WPARAM wparam, LPARAM lparam)
{
	int timer = 0;

	switch (message_id)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	/*
	ダブルクリックが必要になったら
	case WM_LBUTTONDBLCLK:

		if (!is_click) {
			is_click = 1;
		}
	*/

	// マウスボタンクリック開始時
	case WM_LBUTTONDOWN:  // 左

		MessageBox(NULL, "左クリック", NULL, MB_OK);

		if (++timer >= 1.f) {
			is_click = true;
			pt.end.x = pt.start.x;
			pt.end.y = pt.start.y;
		}

		break;

	case WM_RBUTTONDOWN:  // 右
		MessageBox(NULL, "右クリック", NULL, MB_OK);
		break;
	case WM_MBUTTONDOWN:  // 中
		MessageBox(NULL, "ホイールクリック", NULL, MB_OK);
		break;
		// マウスボタンクリック終了時
	case WM_LBUTTONUP:
		is_click = false;
		pt.end = { 0,0 };
		break;

		// マウスカーソル(表示or非表示)
	case WM_CREATE:
		ShowCursor(TRUE);
		break;

	case WM_RBUTTONUP:
	case WM_MBUTTONUP:
	case WM_MOUSEMOVE:

		// 更新する座標を取得
		pt.start.x = LOWORD(lparam);
		pt.start.y = HIWORD(lparam);
		break;

	case WM_SYSKEYDOWN: // システムキー押下開始時
	case WM_SYSKEYUP:   // システムキー終了時
		MessageBox(NULL, "システムキー入力", NULL, MB_OK);
		return 0;

	case WM_KEYDOWN: // キー押下開始時
	case WM_KEYUP:   // キー終了時
		MessageBox(NULL, "キー入力", NULL, MB_OK);
		return 0;
	}

	return DefWindowProc(window_handle, message_id, wparam, lparam);
}

namespace Window{

	bool MakeWindow(float x_, float y_, char* name_) {

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
			name_,												// クラス名									
			NULL												// 小さいアイコン
		};

		// 構造体の登録
		if (RegisterClassEx(&window_class) == 0)
		{
			return false;
		}

		// ウィンドウ作成
		hWnd = CreateWindow(
			name_,
			name_,
			(WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME) | WS_VISIBLE,
			0,
			0,
			x_,
			y_,
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

	bool ProcessMessage() {
		MSG msg;

		//　メッセージが０では無い間
		while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {

			TranslateMessage(&msg);
			DispatchMessage(&msg);

			if (msg.message == WM_QUIT) {
				return false;
			}
		}
		return true;
	}

}

