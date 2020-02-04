#pragma once

#include "Drawer2D.h"
#include <string>

/**
* @brief
* スライダーを管理・描画するクラス
*/

/**
* @enum 方向を決定する列挙子
*/
enum class Direction {
	LeftToRight,
	RightToLeft
};

class Slider {
public:
	
	/**
	* @brief コンストラクタ
	* @param x_ スライダーのX座標
	* @param y_ スライダーのY座標
	* @param z_ スライダーのZ座標
	* @param dir_ スライダーの方向
	*/
	Slider(float x_, float y_, float z_,Direction dir_) :
		count(0),
		X(x_),
		Y(y_),
		Z(z_),
		MinValue(0.f),
		MaxValue(100.f),
		CurrentValue(0.f),
		NextValue(100.f),
		MoveSpeed(0.f),
		Dir(dir_)
	{}

	/**
	* @brief スライダーの更新\n
	* スライダーのステータスを参照して増減を決定する
	*/
	void Update();

	/**
	* @brief スライダーを描画する
	*/
	void DrawSlider(std::string file_name_);

private:
	/**
	* @brief Update() 内で使用される関数
	*/
	void UpdateNextSliderValue(bool plus_);
	void UpdateSliderCurrentValue();

private:
	int count;				//!< @brief 経過フレームを保存

	float X;				//!< @brief スライダー描画位置(X)
	float Y;				//!< @brief スライダー描画位置(Y)
	float Z;				//!< @brief スライダー描画位置(Z)

	float MinValue;			//!< @brief 最小値
	float MaxValue;			//!< @brief 最大値

	float CurrentValue;		//!< @brief 現在の値
	float NextValue;		//!< @brief 次の値
	float MoveSpeed;		//!< @brief 移動速度

	Direction Dir;			//!< @brief 進行方向

	Drawer2D InsDrawer;		//!< @brief 描画用の関数を呼び出す

};

