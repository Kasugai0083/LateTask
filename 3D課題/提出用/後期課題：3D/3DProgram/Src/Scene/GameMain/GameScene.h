#pragma once
#include "../SceneBase.h"

/**
* @brief
* ゲームメインのシーン処理
*/

class GameScene : public SceneBase
{
public:
	GameScene();
	~GameScene()override;
private:
	void Init()override;
	void Update()override;
	SceneID End()override;
	SceneID Control()override;
	void Draw()override;
};

