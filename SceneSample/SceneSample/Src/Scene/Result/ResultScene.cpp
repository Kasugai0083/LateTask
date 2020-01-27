#include "ResultScene.h"
#include "../../Lib/Input.h"
#include "../../Lib/Graphics.h"
//------------------------------
//初期化処理
void ResultScene::Init() {

	m_State = SceneState::UPDATE;
}

//-------------------------------
//更新処理
void ResultScene::Update() {

	if (GetKeyDown(VK_ESCAPE)) {
		m_State = SceneState::END;
	}
}

//-------------------------------
//終了処理
SceneID ResultScene::End() {

	m_State = SceneState::INIT;
	return SceneID::TITLE;
}

//-------------------------------
//状態遷移
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

//------------------------------
//描画処理
void ResultScene::Draw() {

	Texture room;
	Graphic::CreateTexture("Res/game_over.png", &room);
	Graphic::DrawTexture(0, 0, &room);
}