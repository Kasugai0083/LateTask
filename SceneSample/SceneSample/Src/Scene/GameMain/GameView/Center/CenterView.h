#pragma once
#include "../GameViewBase.h"
#include "../../GameData.h"
#include "../../../../ID/GameViewID.h"

class CenterView : public GameViewBase{

public:
	~CenterView()override
	{
	}

private:

	void Init()override;

	GameViewID Update()override;
	
	void Draw()override;


};