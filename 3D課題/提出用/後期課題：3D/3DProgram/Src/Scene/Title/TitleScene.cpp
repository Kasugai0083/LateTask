#include "TitleScene.h"



TitleScene::TitleScene()
{
}


TitleScene::~TitleScene()
{
}

void TitleScene::Init() {
	m_State = SceneState::UPDATE;
}

void TitleScene::Update() {
	static int count = 0;
	count++;
	if (count >= 20) {
		count = 0;
		m_State = SceneState::END;
	}
}

SceneID TitleScene::End() {
	m_State = SceneState::INIT;
	return SceneID::GAME;
}

SceneID TitleScene::Control() {
	switch (m_State)
	{
	case SceneState::INIT:
		break;
	case SceneState::UPDATE:
		break;
	case SceneState::END:
		return End();
	}
	return SceneID::TITLE;
}

void TitleScene::Draw() {

}