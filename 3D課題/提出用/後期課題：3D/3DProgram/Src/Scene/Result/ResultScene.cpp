#include "ResultScene.h"



ResultScene::ResultScene()
{
}


ResultScene::~ResultScene()
{
}

void ResultScene::Init() {
	m_State = SceneState::UPDATE;
}

void ResultScene::Update() {
	static int count = 0;
	count++;
	if (count >= 20) {
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
		break;
	case SceneState::UPDATE:
		break;
	case SceneState::END:
		return End();
	}
	return SceneID::RESULT;
}

void ResultScene::Draw() {

}