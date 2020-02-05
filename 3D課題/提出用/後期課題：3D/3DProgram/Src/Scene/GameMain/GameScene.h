#pragma once
#include "../SceneBase.h"
#include "../../Engine/Graphics/Grid.h"


/**
* @brief
* ゲームメインのシーン処理
*/

namespace {
	Vec3 test1(-5.f, -1.f, 0.f);
	Vec3 test2(10.f, 2.f, 0.f);
	Vec3 test3(20.f, -2.f, 0.f);
}

class GameScene : public SceneBase
{
public:
	GameScene() : 
		Gridman(test1, test2, test3)
	{}
	~GameScene()override;
private:
	void Init()override;
	void Update()override;
	SceneID End()override;
	SceneID Control()override;
	void Draw()override;
private:
	LineDrawer Gridman;
};

