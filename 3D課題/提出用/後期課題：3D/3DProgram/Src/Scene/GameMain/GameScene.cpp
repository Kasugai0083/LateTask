#include "GameScene.h"



GameScene::GameScene()
{
}
GameScene::~GameScene()
{
}


void GameScene::Init()
{
	m_State = SceneState::UPDATE;
}

void GameScene::Update() {
	static int count = 0;
	count++;
	if (count >= 20) {
		count = 0;
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

}

