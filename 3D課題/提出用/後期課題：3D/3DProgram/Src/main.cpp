
#include "Engine/Graphics/DirectX.h"
#include "Engine/Graphics/XFile.h"
#include "Engine/Graphics/XFileDrawer.h"
#include "Engine/Device.h"
#include "Engine/Graphics/Drawer2D.h"
#include "Engine/Graphics/Slider.h"
#include "Engine/Graphics/Grid.h"
#include "Scene/SceneController.h"
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


	// SceneController
	SceneController::CreateInstance();
	SceneController* s_Controller = SceneController::GetInstance();


	if (!Device::MakeWindow(600.f,600.f,"後期課題：エンジンテスト")) {
		MessageBox(NULL,"ウィンドウ作成失敗",NULL, MB_OK);
	}
	s_Controller->Init(SceneID::TITLE);



	while (Device::ProcessMessage())
	{

		Device::KeyUpdate();

		s_DXManager->StartDraw();

		s_DXManager->Transform();

		s_DXManager->SetLighting();

		Size font_size{ 32.f,32.f };
		s_DXManager->CreateFontDevice(font_size);

		// シーン制御
		s_Controller->Update();
		s_Controller->Draw();

		s_DXManager->EndDraw();
		
	}


	s_Controller->Release();

	SceneController::DestroyInstance();
	DXManager::DestroyInstance();

}
