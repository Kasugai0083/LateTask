#pragma once
#include "../GameViewBase.h"

class LeftView : public GameViewBase{

public:

	~LeftView()override
	{
	}

private:

	void Init()override;

	GameViewID Update()override;

	void Draw()override;
};