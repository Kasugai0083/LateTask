#pragma once
#include "../SceneBase.h"

/**
* @brief
* �Q�[�����C���̃V�[������
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

