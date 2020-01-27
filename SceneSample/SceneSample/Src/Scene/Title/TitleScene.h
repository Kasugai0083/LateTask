#pragma once
#include "../SceneBase.h"

//=================================
//　タイトルシーンクラス
//=================================

class TitleScene :public SceneBase {

public:

	~TitleScene()override
	{
	}

private:
	
	void Init()override;

	void Update()override;

	SceneID End()override;

	SceneID Control();

	void Draw()override;
};