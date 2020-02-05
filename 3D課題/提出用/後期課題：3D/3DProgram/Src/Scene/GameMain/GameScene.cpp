#include "GameScene.h"


GameScene::~GameScene()
{
}


void GameScene::Init()
{
	// ÉVÅ[ÉìëJà⁄
	m_State = SceneState::UPDATE;
}

void GameScene::Update() {
	Gridman.UpdateLineManager();

	static int count = 0;
	if (Device::KeyPress('A')) {
		m_State = SceneState::END;
	}
}

SceneID GameScene::End() {
	m_State = SceneState::INIT;
	return SceneID::RESULT;
}

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

void GameScene::Draw() {
	Gridman.DrawLine();

}

