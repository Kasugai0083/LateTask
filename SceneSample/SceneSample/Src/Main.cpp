#include "Lib/Engine.h"
#include "Lib/Window.h"
#include "Lib/Input.h"
#include "Lib/Graphics.h"
#include "Scene/SceneController.h"


int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	Engine::InitEngine(1920, 1080, "C++でシーンを作ろう");
	auto controller = SceneController::GetInstance();
	controller->Init(SceneID::TITLE);
	
	while (ProcessMessage()) {

		UpdateInput();
		controller->Update();
		Graphic::DrawStart();
		controller->Draw();
		Graphic::DrawEnd();

	}
	controller->Release();
	return 0;
}