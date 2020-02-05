#include "ResultScene.h"


ResultScene::~ResultScene()
{
}

void ResultScene::Init() {
	if (!drawer.CreateTexture("Res/bomb.png")) {
		MessageBox(NULL, "画像の読み込みに失敗2", NULL, MB_OK);
	}
	m_State = SceneState::UPDATE;
}

void ResultScene::Update() {

	slider1.Update();
	slider2.Update();

	static int count = 0;
	count++;

	if (count >= 120) {
		count = 0;
		m_State = SceneState::END;
	}
}

SceneID ResultScene::End() {
	m_State = SceneState::INIT;
	return SceneID::TITLE;
}

SceneID ResultScene::Control() {
	switch (m_State)
	{
	case SceneState::INIT:
		Init();
		break;
	case SceneState::UPDATE:
		Update();
		break;
	case SceneState::END:
		return End();
	}
	return SceneID::RESULT;
}

void ResultScene::Draw() {
	{
		VertexPos v{ Pos3(-5.f,-5.f,0.f),Pos2(0.f,0.f),Pos2(256.f, 256.f) };
		// ここでバグが発生中
		drawer.DrawTexture(v, "Res/bomb.png");
	}

	slider1.DrawSlider("Res/Slider01.png");
	slider2.DrawSlider("Res/Slider01.png");

}