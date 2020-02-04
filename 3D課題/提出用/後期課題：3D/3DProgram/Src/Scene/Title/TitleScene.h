#pragma once

#include "../SceneBase.h"

class TitleScene :public SceneBase
{
public:
	TitleScene();
	~TitleScene()override;

private:
	void Init()override;
	void Update()override;
	SceneID End()override;
	SceneID Control();
	void Draw()override;
};

