#pragma once

#include "../SceneBase.h"
#include "../../Engine/Graphics/XFileDrawer.h"

/**
* @brief
* タイトルシーンの処理
*/

class TitleScene :public SceneBase
{
public:
	TitleScene();			//!< コンストラクタ
	~TitleScene()override;	//!< デストラクタ

private:
	void Init()override;	//!< シーンの初期化
	void Update()override;	//!< シーンの更新
	SceneID End()override;	//!< シーンの解放
	SceneID Control();		//!< シーンの制御
	void Draw()override;	//!< シーンの描画
private:

	Drawer2D drawer;		//!< フォント表示に使用
	XFileDrawer Object;		//!< XFileの描画に使用
};

