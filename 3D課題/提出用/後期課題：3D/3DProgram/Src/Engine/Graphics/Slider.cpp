#include "Slider.h"
#include <math.h>
#include <Windows.h>
#include <string>


void Slider::UpdateNextSliderValue(bool plus_) {
	// 値を更新する
	if (plus_) {
		NextValue = MaxValue;
	}
	else {
		NextValue = MinValue;
	}

	// 今の値と新しい値の差を出して、速度を算出する
	float distance = fabsf(CurrentValue - NextValue);

	// 移動にかかるフレーム数
	float moev_frame = 60.0f;
	MoveSpeed = distance / moev_frame;
}

void Slider::UpdateSliderCurrentValue() {
	// NextValueとCurrentValueに差file_name_があればMoveSpeedで演算する
	if (CurrentValue <= NextValue)
	{
		CurrentValue = min(CurrentValue + MoveSpeed, NextValue);
	}
	else
	{
		CurrentValue = max(CurrentValue - MoveSpeed, NextValue);
	}
}

void Slider::Update() {

	count++;
	UpdateSliderCurrentValue();

	if (count % 120 == 0)
	{
		UpdateNextSliderValue(true);
	}
	else if (count % 60 == 0)
	{
		UpdateNextSliderValue(false);
	}

}

void ReverseMove(float rate, float size, float& out_pos, float& out_tex_pos, float& out_size)
{
	// 比率から描画開始位置をずらす
	out_pos = (out_pos + size) - (size * rate);

	// サイズも比率で変更する
	out_size *= rate;

	// テクスチャの座標も比率の分だけずらす
	out_tex_pos += (1.0f - rate) * size;
}

void Slider::DrawSlider(std::string file_name_)
{

	InsDrawer.CreateTexture(file_name_);

	float pos_x = X;
	float pos_y = Y;
	float pos_z = Z;
	float tex_x = 0.0f;
	float tex_y = 0.0f;
	float tex_width = InsDrawer.GetTexture(file_name_)->Width;
	float tex_height = InsDrawer.GetTexture(file_name_)->Height;

	// 現状の値を比率として算出する
	float rate = (CurrentValue - MinValue) / (MaxValue - MinValue);

	if (Dir == Direction::LeftToRight) {
		tex_width *= rate;
	}
	else if (Dir == Direction::RightToLeft) {
		//tex_width *= rate;
		ReverseMove(rate, tex_width, pos_x, tex_x, tex_width);
	}


	//// 各進行方向による処理を実装する
	//if (slider.Dir == Direction::LeftToRight)
	//{
	//	// 横幅に比率を掛けてサイズを調整する
	//	tex_width *= rate;
	//}
	//else if (slider.Dir == Direction::RightToLeft)
	//{
	//	// 最小 => 最大の方向とX軸の最小 => 最大が逆なので反転させる
	//	ReverseMove(rate, tex_width, pos_x, tex_x, tex_width);
	//}
	//else if (slider.Dir == Direction::UpToDown)
	//{
	//	// 縦幅に比率を掛けてサイズを調整する
	//	tex_height *= rate;
	//}
	//else if (slider.Dir == Direction::DownToUp)
	//{
	//	// 最小 => 最大の方向とY軸の最小 => 最大が逆なので反転させる
	//	ReverseMove(rate, tex_height, pos_y, tex_y, tex_height);
	//}

	CustomVertex a{ D3DXVECTOR3(pos_x, pos_y, pos_z), D3DXVECTOR2(tex_x,tex_y) };

	InsDrawer.DrawTexture(a, file_name_, tex_width, tex_height);

}
