#pragma once

#include "../SceneBase.h"
#include "../../Engine/Graphics/Slider.h"

/**
* @brief
* リザルトシーンの処理
*/
class ResultScene :public SceneBase
{
public:
	//!< コンストラクタ
	ResultScene() : 
		slider1(-5.f, 5.f, 0.f, Direction::LeftToRight),
		slider2(-20.f, 2.5f, 0.f, Direction::RightToLeft)
	{}
	~ResultScene()override;		//!< デストラクタ
private:
	void Init()override;		//!< シーンの初期化
	void Update()override;		//!< シーンの更新
	SceneID End()override;		//!< シーンの解放
	SceneID Control()override;	//!< シーンの制御
	void Draw()override;		//!< シーンの描画
private:
	Drawer2D drawer;			//!< フォント表示に使用
	
	//!< スライダーの描画に使用
	Slider slider1;				
	Slider slider2;				 

};

