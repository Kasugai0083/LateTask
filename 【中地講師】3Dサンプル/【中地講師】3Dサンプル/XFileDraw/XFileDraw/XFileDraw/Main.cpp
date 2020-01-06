#include <windows.h>
#include <map>
#include "DirectX.h"
#include "XFile.h"
#include "Drawer.h"
#include "Camera.h"

extern LPDIRECT3D9 g_pD3DInterface;	// DirectXインターフェース
extern D3DPRESENT_PARAMETERS *g_pD3DPresentParam;
extern LPDIRECT3DDEVICE9 g_pD3DDevice;
extern std::map<std::string, XFile *>g_pXFileList;


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
		TEXT("XFileDraw"),				// クラス名									
		NULL							// 小さいアイコン
	};

	// 構造体の登録
	if (RegisterClassEx(&window_class) == 0)
	{
		return false;
	}

	// ウィンドウ作成
	hWnd = CreateWindow(
		TEXT("XFileDraw"),
		TEXT("XFileDraw"),
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

	if (InitDirectX(hWnd) == false)
	{
		return false;
	}

	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);

	// 読み込みファイル名リスト
	std::string file_name_list[] =
	{
		"Witchwait.X",
		"Sample02.x",
	};

	// XFile読み込み
	for (int i = 0; i <2; i++)
	{
		g_pXFileList[file_name_list[i]] = new XFile();
		g_pXFileList[file_name_list[i]]->Load(file_name_list[i]);
	}

	// XFileオブジェクト作成
	Drawer obj1(
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(1.0f, 1.0f, 1.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		g_pXFileList["Witchwait.X"]);

	Drawer obj2(
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(0.01f, 0.01f, 0.01f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		g_pXFileList["Sample02.x"]);

	//カメラ作成　位置を入力
	//Vector CPos, Gaze;
	//CPos.m_X = 0.0f;
	//CPos.m_Y = 0.0f;
	//CPos.m_Z = -150.0f;

	//Gaze.m_X = 0.0f;
	//Gaze.m_Y = 0.0f;
	//Gaze.m_Z = 0.0f;
	//Camera camera(CPos, Gaze);

	Vec2 vec2(0.0f, 0.0f, 0.0f);

	Camera camera(
		Vector2(0.0f, 0.0f, -150.0f),
		Vector2(0.0f, 0.0f, 0.0f)
	);

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
		} else {
			//カメラのアップデート
			camera.Update();

			// 描画開始
			StartDraw();

			// 座標変換		
			Transform();

			// ライティング設定
			SetLighting();

			// オブジェクト描画
			obj1.Draw();
			//obj2.Draw();
			
			//オブジェクトのアップデート
			obj1.Update();

			// 描画終了
			EndDraw();
		}
	}

	for (int i = 0; i < 2; i++)
	{
		delete(g_pXFileList[file_name_list[i]]);
	}
	return 0;
}

