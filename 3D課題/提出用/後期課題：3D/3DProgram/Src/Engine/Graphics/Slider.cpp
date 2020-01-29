#include "Slider.h"
#include <math.h>
#include <Windows.h>
#include <string>


void Slider::UpdateNextSliderValue(bool plus_) {
	// �l���X�V����
	if (plus_) {
		NextValue = MaxValue;
	}
	else {
		NextValue = MinValue;
	}

	// ���̒l�ƐV�����l�̍����o���āA���x���Z�o����
	float distance = fabsf(CurrentValue - NextValue);

	// �ړ��ɂ�����t���[����
	float moev_frame = 60.0f;
	MoveSpeed = distance / moev_frame;
}

void Slider::UpdateSliderCurrentValue() {
	// NextValue��CurrentValue�ɍ�file_name_�������MoveSpeed�ŉ��Z����
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
	// �䗦����`��J�n�ʒu�����炷
	out_pos = (out_pos + size) - (size * rate);

	// �T�C�Y���䗦�ŕύX����
	out_size *= rate;

	// �e�N�X�`���̍��W���䗦�̕��������炷
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

	// ����̒l��䗦�Ƃ��ĎZ�o����
	float rate = (CurrentValue - MinValue) / (MaxValue - MinValue);

	if (Dir == Direction::LeftToRight) {
		tex_width *= rate;
	}
	else if (Dir == Direction::RightToLeft) {
		//tex_width *= rate;
		ReverseMove(rate, tex_width, pos_x, tex_x, tex_width);
	}


	//// �e�i�s�����ɂ�鏈������������
	//if (slider.Dir == Direction::LeftToRight)
	//{
	//	// �����ɔ䗦���|���ăT�C�Y�𒲐�����
	//	tex_width *= rate;
	//}
	//else if (slider.Dir == Direction::RightToLeft)
	//{
	//	// �ŏ� => �ő�̕�����X���̍ŏ� => �ő傪�t�Ȃ̂Ŕ��]������
	//	ReverseMove(rate, tex_width, pos_x, tex_x, tex_width);
	//}
	//else if (slider.Dir == Direction::UpToDown)
	//{
	//	// �c���ɔ䗦���|���ăT�C�Y�𒲐�����
	//	tex_height *= rate;
	//}
	//else if (slider.Dir == Direction::DownToUp)
	//{
	//	// �ŏ� => �ő�̕�����Y���̍ŏ� => �ő傪�t�Ȃ̂Ŕ��]������
	//	ReverseMove(rate, tex_height, pos_y, tex_y, tex_height);
	//}

	CustomVertex a{ D3DXVECTOR3(pos_x, pos_y, pos_z), D3DXVECTOR2(tex_x,tex_y) };

	InsDrawer.DrawTexture(a, file_name_, tex_width, tex_height);

}
