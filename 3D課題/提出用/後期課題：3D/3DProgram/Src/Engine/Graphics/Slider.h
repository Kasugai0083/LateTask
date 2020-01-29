#pragma once

#include "Drawer2D.h"
#include <string>

enum class Direction {
	LeftToRight,
	RightToLeft
};

class Slider {
public:
	


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

	void Update();

	void DrawSlider(std::string file_name_);

private:

	void UpdateNextSliderValue(bool plus_);
	void UpdateSliderCurrentValue();

private:
	int count;

	float X;				//!< スライダー描画位置(X)
	float Y;				//!< スライダー描画位置(Y)
	float Z;				//!< スライダー描画位置(Z)

	float MinValue;			//!< 最小値
	float MaxValue;			//!< 最大値

	float CurrentValue;		//!< 現在の値
	float NextValue;		//!< 次の値
	float MoveSpeed;		//!< 移動速度

	Direction Dir;			//!< 進行方向

	Drawer2D InsDrawer;

};

