
#include "Engine/Graphics/DirectX.h"
#include "Engine/Graphics/XFile.h"
#include "Engine/Graphics/XFileDrawer.h"
#include "Engine/Window.h"
#include "Engine/Graphics/Drawer2D.h"
#include "Engine/Graphics/Slider.h"
#include "Engine/Graphics/Grid.h"

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

	XFileDrawer Object;

	if(!Object.Load("Res/Sample01.x")){
		MessageBox(NULL, "画像の読み込みに失敗1", NULL, MB_OK);
	}

	Drawer2D drawer;

	if (!drawer.CreateTexture("Res/bomb.png")) {
		MessageBox(NULL, "画像の読み込みに失敗2", NULL, MB_OK);
	}

	Slider slider1(-5.f, 5.f, 0.f,Direction::LeftToRight);
	Slider slider2(-20.f, 2.5f, 0.f,Direction::RightToLeft);

	// 曲線の描画
	Vec3 test(0.f, 0.f, 0.f);
	Vec3 test2(5.f, 5.f, 5.f);

	LineDrawer Gridman;
	Gridman.InitLine(test, test2);

	while (Window::ProcessMessage())
	{

		s_DXManager->StartDraw();

		s_DXManager->Transform();

		s_DXManager->SetLighting();


		// XFileの描画(正面)
		Object.Draw(
			D3DXVECTOR3(0.f, 0.f, 0.f),
			D3DXVECTOR3(1.f, 1.f, 1.f),
			D3DXVECTOR3(20.f, 20.f, 20.f),
			"Res/Sample01.x"
		);


		// XFileの描画(右上)
		Object.DrawBillbord(
			D3DXVECTOR3(5.f, 5.f, 5.f),
			D3DXVECTOR3(1.f, 1.f, 1.f),
			D3DXVECTOR3(20.f, 20.f, 20.f),
			"Res/Sample01.x"
		);


		// 板ポリの描画(左下)
		{
			CustomVertex v{ D3DXVECTOR3(-5.f,-5.f,0.f),D3DXVECTOR2(0.f,0.f) };
			drawer.DrawTexture(v, "Res/bomb.png",256.f, 256.f);
		}

		slider1.Update();
		slider2.Update();

		slider1.DrawSlider("Res/Slider01.png");
		slider2.DrawSlider("Res/Slider01.png");

		Gridman.UpdateLineManager();
		Gridman.DrawLine();

		s_DXManager->EndDraw();
		
	}

	Object.ReleaseXFile();

	DXManager::DestroyInstance();

}
