#pragma once
#include "../GameViewBase.h"

class RightView : public GameViewBase{

public:

	~RightView()override
	{
	}

private:

	void Init()override;

	GameViewID Update()override;

	void Draw()override;

};