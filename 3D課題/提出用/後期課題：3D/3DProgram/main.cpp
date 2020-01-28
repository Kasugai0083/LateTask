
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

int APIENTRY WinMain(HINSTANCE ,HINSTANCE, LPSTR, INT)
{
	//DirectXシングルトン作成
	DXManager::CreateInstance();
	DXManager* s_DXManager = DXManager::GetInstance();

	if (!Window::MakeWindow(600.f,600.f,"後期課題：エンジンテスト")) {
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

	while (Window::ProcessMessage())
	{

		s_DXManager->StartDraw();

		s_DXManager->Transform();

		s_DXManager->SetLighting();

		obj1.Draw();

		s_DXManager->EndDraw();
		
	}

	delete g_pXFileList["Res/Sample01.x"];

	DXManager::DestroyInstance();

}
