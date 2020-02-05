
#include "Engine/Graphics/DirectX.h"
#include "Engine/Graphics/XFile.h"
#include "Engine/Graphics/XFileDrawer.h"
#include "Engine/Window.h"
#include "Engine/Graphics/Drawer2D.h"
#include "Engine/Graphics/Slider.h"
#include "Engine/Graphics/Grid.h"
#include "Scene/SceneController.h"
#include <string>
#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <map>

// �ÓI���C�u����
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

int APIENTRY WinMain(HINSTANCE ,HINSTANCE, LPSTR, INT)
{
	//DirectX�V���O���g���쐬
	DXManager::CreateInstance();
	DXManager* s_DXManager = DXManager::GetInstance();

	// SceneController
	SceneController::CreateInstance();
	SceneController* s_Controller = SceneController::GetInstance();

	s_Controller->Init(SceneID::TITLE);

	if (!Window::MakeWindow(600.f,600.f,"����ۑ�F�G���W���e�X�g")) {
		MessageBox(NULL,"�E�B���h�E�쐬���s",NULL, MB_OK);
	}

	XFileDrawer Object;

	if(!Object.Load("Res/Sample01.x")){
		MessageBox(NULL, "�摜�̓ǂݍ��݂Ɏ��s1", NULL, MB_OK);
	}

	Drawer2D drawer;

	if (!drawer.CreateTexture("Res/bomb.png")) {
		MessageBox(NULL, "�摜�̓ǂݍ��݂Ɏ��s2", NULL, MB_OK);
	}

	Slider slider1(-5.f, 5.f, 0.f,Direction::LeftToRight);
	Slider slider2(-20.f, 2.5f, 0.f,Direction::RightToLeft);

	// �Ȑ��̕`�� // �l�̕ύX�ŕ`��ɉe���͂�����̂́A�z��ʂ�ɐ���ł���
	Vec3 test1(-5.f, -1.f, 0.f);
	Vec3 test2(10.f, 2.f, 0.f);
	Vec3 test3(20.f, -2.f, 0.f);

	LineDrawer Gridman(test1, test2, test3);

	while (Window::ProcessMessage())
	{

		s_DXManager->StartDraw();

		s_DXManager->Transform();

		s_DXManager->SetLighting();


		s_Controller->Update();
		s_Controller->Draw();

		// XFile�̕`��(����)
		Object.Draw(
			D3DXVECTOR3(0.f, 0.f, 0.f),
			D3DXVECTOR3(1.f, 1.f, 1.f),
			D3DXVECTOR3(20.f, 20.f, 20.f),
			"Res/Sample01.x"
		);


		// XFile�̕`��(�E��)
		Object.DrawBillbord(
			D3DXVECTOR3(5.f, 5.f, 5.f),
			D3DXVECTOR3(1.f, 1.f, 1.f),
			D3DXVECTOR3(20.f, 20.f, 20.f),
			"Res/Sample01.x"
		);


		// �|���̕`��(����)
		{
			VertexPos v{ Pos3(-5.f,-5.f,0.f),Pos2(0.f,0.f),Pos2(256.f, 256.f) };
			drawer.DrawTexture(v, "Res/bomb.png");
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
	s_Controller->Release();

	SceneController::DestroyInstance();
	DXManager::DestroyInstance();

}
