#pragma once

#include "GameData.h"
#include "../../Lib/Graphics.h"
#include "../../Utility/Vec.h"
#include "../../ID/GameViewID.h"
#include <string>

struct  GameData
{

	GameData(const char* file_name, GameViewID id) {
		Tex = new Texture();
		Graphic::CreateTexture(file_name, Tex);
		ID = id;
	}

	GameViewID GetGameViewID() {
		return ID;
	}

	GameViewID ID;
	Vec2 Pos;
	Texture* Tex;
	std::string Name;
};