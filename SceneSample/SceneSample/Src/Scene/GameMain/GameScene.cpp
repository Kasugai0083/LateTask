#include "GameScene.h"
#include "../../Lib/Graphics.h"
#include "../../Lib/Input.h"
#include "GameView/Center/CenterView.h"
#include "GameView/Right/RightView.h"
#include "GameView/Left/LeftView.h"
//-----------------------------
//コンストラクタ
GameScene::GameScene() {

	m_Enemy = new GameData(
		"Res/pose_heart_hand_idol_woman.png",
		GameViewID::CENTER
	);

	m_ViewList.push_back(new CenterView);
	m_ViewList.push_back(new RightView);
	m_ViewList.push_back(new LeftView);

	if (m_Enemy->GetGameViewID() == GameViewID::CENTER) {
			m_ViewList[(int)GameViewID::CENTER]->Regist(m_Enemy);
	}

	m_ViewID = GameViewID::CENTER;
	m_CurrView = m_ViewList[(int)m_ViewID];
}

//-----------------------------
//初期化処理
void GameScene::Init() {

	m_CurrView->Init();

	//次の状態にステップ
	m_State = SceneState::UPDATE;
}
//-----------------------------
//更新処理
void GameScene::Update() {

	if (GetKeyDown(RETURN_KEY)) {
		m_State = SceneState::END;
	}

	GameViewID view_id = m_CurrView->Update();
	ChangeView(view_id);
}

//------------------------------
//視点切り替え
void GameScene::ChangeView(GameViewID view_id) {

	if (view_id != m_ViewID) {
		m_ViewID = view_id;
	}
	m_CurrView = m_ViewList[(int)m_ViewID];
	m_CurrView->Init();
}

//------------------------------
//終了処理
SceneID GameScene::End() {

	m_State = SceneState::INIT;
	return SceneID::RESULT;
}
//------------------------------
//状態遷移
SceneID GameScene::Control() {

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
	return SceneID::GAME;
}

//-----------------------------
//描画処理
void GameScene::Draw() {

	m_CurrView->Draw();
}

//-----------------------------
//デストラクタ
GameScene::~GameScene() {

	for (auto view : m_ViewList) {

		GameViewBase* base = view;
		delete base;
	}
	m_ViewList.clear();

	delete m_Enemy;
}