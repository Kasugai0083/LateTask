#pragma once
#include "../SceneBase.h"
#include "../GameMain/GameView/GameViewBase.h"

class GameScene :public SceneBase {

public:

	GameScene();

	~GameScene()override;

private:
	
	void Init()override;

	void Update()override;

	void ChangeView(GameViewID view_id);

	SceneID End()override;
	
	SceneID Control()override;

	void Draw()override;

private:
	std::vector<GameViewBase*> m_ViewList;
	GameViewBase* m_CurrView;
	GameViewID m_ViewID;
	GameData* m_Enemy;///ここは適当
};