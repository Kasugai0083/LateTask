#pragma once

#include "../SceneBase.h"

class ResultScene :public SceneBase
{
public:
	ResultScene();
	~ResultScene()override;
private:
	void Init()override;
	void Update()override;
	SceneID End()override;
	SceneID Control()override;
	void Draw()override;
};

