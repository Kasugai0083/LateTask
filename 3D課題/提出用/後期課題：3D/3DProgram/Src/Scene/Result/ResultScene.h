#pragma once

#include "../SceneBase.h"
#include "../SceneController.h"
#include "../../Engine/Graphics/Drawer2D.h"
#include "../../Engine/Graphics/Slider.h"

class ResultScene :public SceneBase
{
public:
	ResultScene() : 
		slider1(-5.f, 5.f, 0.f, Direction::LeftToRight),
		slider2(-20.f, 2.5f, 0.f, Direction::RightToLeft)
	{
		if (!drawer.CreateTexture("Res/bomb.png")) {
			MessageBox(NULL, "‰æ‘œ‚Ì“Ç‚İ‚İ‚É¸”s2", NULL, MB_OK);
		}

	}
	~ResultScene()override;
private:
	void Init()override;
	void Update()override;
	SceneID End()override;
	SceneID Control()override;
	void Draw()override;
private:
	Drawer2D drawer;

	Slider slider1;
	Slider slider2;

};

