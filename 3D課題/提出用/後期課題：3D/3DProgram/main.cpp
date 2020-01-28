
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

	Drawer Object;

	if(!Object.LoadXFile("Res/Sample01.x")){
		MessageBox(NULL, "画像の読み込みに失敗", NULL, MB_OK);
	}


	while (Window::ProcessMessage())
	{

		s_DXManager->StartDraw();

		s_DXManager->Transform();

		s_DXManager->SetLighting();

		Object.DrawXFile(
			D3DXVECTOR3(0.f, 0.f, 0.f),
			D3DXVECTOR3(1.f, 1.f, 1.f),
			D3DXVECTOR3(20.f, 20.f, 20.f),
			"Res/Sample01.x"
		);

		Object.DrawBillbord(
			D3DXVECTOR3(5.f, 5.f, 5.f),
			D3DXVECTOR3(1.f, 1.f, 1.f),
			D3DXVECTOR3(20.f, 20.f, 20.f),
			"Res/Sample01.x"
		);

		s_DXManager->EndDraw();
		
	}

	Object.ReleaseXFile();

	DXManager::DestroyInstance();

}
