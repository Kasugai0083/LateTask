
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

	while (Window::ProcessMessage())
	{

		s_DXManager->StartDraw();

		s_DXManager->Transform();

		s_DXManager->SetLighting();

		// �V�[������
		s_Controller->Update();
		s_Controller->Draw();

		s_DXManager->EndDraw();
		
	}


	s_Controller->Release();

	SceneController::DestroyInstance();
	DXManager::DestroyInstance();

}
