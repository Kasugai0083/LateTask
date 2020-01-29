#pragma once

#include "Drawer2D.h"
#include <string>

class Slider {
public:
	
	Slider(float x_, float y_, float z_):
		X(x_),
		Y(y_),
		Z(z_),
		MinValue(0.f),
		MaxValue(100.f),
		CurrentValue(0.f),
		NextValue(100.f),
		MoveSpeed(0.f)
	{}

	void UpdateNextSliderValue(bool plus_);
	void UpdateSliderCurrentValue();

	void DrawSlider(std::string file_name_);

private:

	void ReverseMove();

private:
	// 左上原点
	float X;				//!< スライダー描画位置(X)
	float Y;				//!< スライダー描画位置(Y)
	float Z;				//!< スライダー描画位置(Z)

	float MinValue;			//!< 最小値
	float MaxValue;			//!< 最大値

	float CurrentValue;		//!< 現在の値
	float NextValue;		//!< 次の値
	float MoveSpeed;		//!< 移動速度

	Drawer2D InsDrawer;

	// 今回は進行方向を考慮しないので一旦排除
	// Direction Dir;			//!< 進行方向
};

