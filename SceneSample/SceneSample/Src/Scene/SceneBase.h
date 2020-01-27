#pragma once

#include "../ID/SceneID.h"

//=============================
// シーン基底クラス
//=============================

class SceneBase {

public:

	SceneBase() {
		m_State = SceneState::INIT;
	}

	/*
		初期化処理
	*/
	virtual void Init() = 0;

	/*
		更新処理
	*/
	virtual void Update() = 0;

	/*
		終了処理
	*/
	virtual SceneID End() {
		return SceneID::UNKNOWN;
	};

	/*
		描画処理
	*/
	virtual void Draw(){
	};

	/*
		状短繊維処理

	戻り値：
		ScneID型
	
	概要：
		シーン終了後に次のシーンIDを返す
	*/
	virtual SceneID Control() {
		return SceneID::UNKNOWN;
	}

	/*
		デストラクタ（純仮想）
	*/
	virtual ~SceneBase()
	{
	}

protected:
	SceneState m_State; // 自身の状態ID


};