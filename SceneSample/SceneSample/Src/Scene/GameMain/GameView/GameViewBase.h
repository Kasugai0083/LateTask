#pragma once

#include "../../../ID/GameViewID.h"
#include "../GameData.h"
#include <vector>

class GameViewBase {

public:

	void Regist(GameData* game) {

		m_GameDatas.push_back(game);
	}

	virtual void Init() = 0;

	virtual GameViewID Update() = 0;

	virtual void Draw(){}

	virtual ~GameViewBase()
	{
	}

protected:
	std::vector<GameData*> m_GameDatas;
};