#include "Slider.h"
#include "DirectX.h"
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
	out_pos = 0.f;

	// サイズも比率で変更する
	out_size *= rate;

	// テクスチャの座標も比率の分だけずらす
	out_tex_pos += (1.0f - rate) * size;
}

void Slider::DrawSlider(std::string file_name_)
{

	if (!InsDrawer.CreateTexture(file_name_)) {
		MessageBox(NULL, "画像の読み込みに失敗2", NULL, MB_OK);
	}

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
		ReverseMove(rate, tex_width, pos_x, tex_x, tex_width);
	}

	VertexPos a{ Pos3(pos_x, pos_y, pos_z), Pos2(tex_x,tex_y),Pos2(tex_width, tex_height) };

	InsDrawer.DrawTexture(a, file_name_);

}
