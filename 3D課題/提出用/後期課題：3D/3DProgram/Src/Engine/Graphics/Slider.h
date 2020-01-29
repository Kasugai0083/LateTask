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

	float X;				//!< �X���C�_�[�`��ʒu(X)
	float Y;				//!< �X���C�_�[�`��ʒu(Y)
	float Z;				//!< �X���C�_�[�`��ʒu(Z)

	float MinValue;			//!< �ŏ��l
	float MaxValue;			//!< �ő�l

	float CurrentValue;		//!< ���݂̒l
	float NextValue;		//!< ���̒l
	float MoveSpeed;		//!< �ړ����x

	Direction Dir;			//!< �i�s����

	Drawer2D InsDrawer;

};

