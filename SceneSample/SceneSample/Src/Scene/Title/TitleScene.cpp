#include "TitleScene.h"
#include "../../Lib/Input.h"
#include "../../Lib/Graphics.h"

//------------------------
//初期化処理
void TitleScene::Init() {

	m_State = SceneState::UPDATE;
}

//------------------------
//更新処理
void TitleScene::Update() {

	if (GetKeyDown(RETURN_KEY)) {
		m_State = SceneState::END;
	}
}

//------------------------
//終了処理
SceneID TitleScene::End() {

	m_State = SceneState::INIT;
	return SceneID::GAME;
}

//-------------------------
//状態遷移
SceneID TitleScene::Control() {

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
	return SceneID::TITLE;
}

//------------------------
//描画処理
void TitleScene::Draw() {

	Texture tex;
	Graphic::CreateTexture("Res/title01_notUI.png", &tex);
	
	Graphic::DrawTexture(0, 0, &tex);
}
