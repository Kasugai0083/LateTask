
#include "Engine/Graphics/DirectX.h"
#include "Engine/Graphics/XFile.h"
#include "Engine/Graphics/Drawer.h"
#include "Engine/Window.h"
#include <string>
#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <map>

// 静的ライブラリ
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

//extern LPDIRECT3D9 g_pD3DInterface;	// DirectXインターフェース
//extern D3DPRESENT_PARAMETERS *g_pD3DPresentParam;
//extern LPDIRECT3DDEVICE9 g_pD3DDevice;
//extern std::map<std::string, XFile*>g_pXFileList;




int APIENTRY WinMain(HINSTANCE ,HINSTANCE, LPSTR, INT)
{


	//DirectXシングルトン作成
	DXManager::CreateInstance();
	DXManager* s_DXManager = DXManager::GetInstance();

	if (!MakeWindow()) {
		MessageBox(NULL,"ウィンドウ作成失敗",NULL, MB_OK);
	}

	XFile obj;

	std::map<std::string, XFile*>g_pXFileList;
	
	g_pXFileList["Res/Sample01.x"] = new XFile();
	g_pXFileList["Res/Sample01.x"]->Load("Res/Sample01.x");
	
	Drawer obj1(
		D3DXVECTOR3(0.f, 0.f, 0.f),
		D3DXVECTOR3(1.f, 1.f, 1.f),
		D3DXVECTOR3(0.f, 50.f, 0.f),
		g_pXFileList["Res/Sample01.x"]
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
		}
		else {

			s_DXManager->StartDraw();

			s_DXManager->Transform();

			s_DXManager->SetLighting();

			obj1.Draw();

			s_DXManager->EndDraw();

		}
	}

	delete g_pXFileList["Res/Sample01.x"];

	DXManager::DestroyInstance();

}
