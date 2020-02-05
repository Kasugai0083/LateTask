#pragma once
#include "../SceneBase.h"
#include "../../Engine/Graphics/Grid.h"


/**
* @brief
* ゲームメインのシーン処理
*/

//!< 曲線の通過点を指定
namespace {
	Vec3 start(-5.f, -1.f, 0.f);
	Vec3 center(10.f, 2.f, 0.f);
	Vec3 end(20.f, -2.f, 0.f);
}

class GameScene : public SceneBase
{
public:
	//!< コンストラクタ
	GameScene() : 
		Gridman(start, center, end)
	{}
	~GameScene()override;		//!< デストラクタ
private:
	void Init()override;		//!< シーンの初期化
	void Update()override;		//!< シーンの更新
	SceneID End()override;		//!< シーンの解放
	SceneID Control()override;	//!< シーンの制御
	void Draw()override;		//!< シーンの描画
private:
	Drawer2D drawer;			//!< フォント表示に使用
	LineDrawer Gridman;			//!< XFileの描画に使用
};

