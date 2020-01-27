#include "SceneController.h"
#include "Title/TitleScene.h"
#include "GameMain/GameScene.h"
#include "Result/ResultScene.h"

//----------------------------
//初期化
void SceneController::Init(SceneID id) {

	m_SceneList.push_back(new TitleScene());
	m_SceneList.push_back(new GameScene());
	m_SceneList.push_back(new ResultScene());

	m_SceneID = id;
	m_CurrScene = m_SceneList[(int)m_SceneID];
}

//----------------------------
//更新処理
void SceneController::Update() {

	SceneID id;
	id = m_CurrScene->Control();
	ChangeScene(id);
}

void SceneController::Draw() {

	m_CurrScene->Draw();
}

void SceneController::ChangeScene(SceneID id) {

	if (id != m_SceneID) {
		m_SceneID = id;
	}
	m_CurrScene = m_SceneList[(int)m_SceneID];
}

void SceneController::Release() {

	for (auto scene : m_SceneList) {
		SceneBase* base = scene;
		delete base;
	}
	m_SceneList.clear();
}