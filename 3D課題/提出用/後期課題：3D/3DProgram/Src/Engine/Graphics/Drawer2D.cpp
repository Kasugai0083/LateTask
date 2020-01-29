#include "Drawer2D.h"
#include "DirectX.h"
#include "HandMade.h"

void Drawer2D::DrawSetting(float x_, float y_, float z_, std::string file_name_) {
	// DirectX �̃C���X�^���X��
	DXManager* Ins_DXManager = DXManager::GetInstance();
	if (!Ins_DXManager) { return; }

	// ���[���h, �ړ�, �g�k�s���p��
	D3DXMATRIXA16 world, trans, scale;
	D3DXMatrixIdentity(&world);
	D3DXMatrixIdentity(&trans);
	D3DXMatrixIdentity(&scale);

	// �g�k
	HandMadeScaling(&scale, 0.01f, 0.01f, 0.01f);

	// �ړ�
	D3DXMatrixTranslation(&trans, x_, y_, z_);

	// �r���{�[�h��
	HandMadeBillBoard(&world, Ins_DXManager->GetViewMatrix());

	// �g�k�ƈړ��s��𔽉f
	world *= scale * trans;
	Ins_DXManager->GetStatus()->m_D3DDevice->SetTransform(D3DTS_WORLD, &world);

	// ���C�e�B���O
	Ins_DXManager->GetStatus()->m_D3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);	// RHW�Ŗ������_��LIGHT�������̂Ŗ����ɂ��Ă���

	// �J�����[�h(�̗���������`��)
	Ins_DXManager->GetStatus()->m_D3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	Ins_DXManager->GetStatus()->m_D3DDevice->SetFVF(D3DFVF_XYZ | D3DFVF_TEX1);
	Ins_DXManager->GetStatus()->m_D3DDevice->SetTexture(0, m_TextureList[file_name_]->TexutreData);

}

void Drawer2D::DrawTexture(CustomVertex v_, std::string file_name_, float tu, float tv)
{
	DXManager* Ins_DXManager = DXManager::GetInstance();
	if (!Ins_DXManager) { return; }

	DrawSetting(v_.pos.x, v_.pos.y, v_.pos.z, file_name_);

	float left_tu = 0.f;
	float right_tu = 1.f;
	float top_tv = 0.f;
	float bottom_tv = 1.f;
	
	if (m_TextureList[file_name_] != nullptr) {
		left_tu = v_.tex_pos.x / m_TextureList[file_name_]->Width;
		right_tu =(v_.tex_pos.x + tu) / m_TextureList[file_name_]->Width;
		top_tv = v_.tex_pos.y / m_TextureList[file_name_]->Height;
		bottom_tv = (v_.tex_pos.y + tv) / m_TextureList[file_name_]->Height;
	}

	CustomVertex v[] =
	{
		{ D3DXVECTOR3(v_.tex_pos.x, v_.tex_pos.y + tv, 0.0f), D3DXVECTOR2(left_tu, top_tv) },
		{ D3DXVECTOR3(v_.tex_pos.x + tu, v_.tex_pos.y + tv, 0.0f), D3DXVECTOR2(right_tu, top_tv) },
		{ D3DXVECTOR3(v_.tex_pos.x + tu, v_.tex_pos.y, 0.0f), D3DXVECTOR2(right_tu, bottom_tv) },
		{ D3DXVECTOR3(v_.tex_pos.x, v_.tex_pos.y, 0.0f), D3DXVECTOR2(left_tu, bottom_tv) },
	};


	//float half_x = m_TextureList[file_name_]->Width / 2.f;
	//float half_y = m_TextureList[file_name_]->Height / 2.f;
	//
	//CustomVertex v[4] =
	//{
	//	
	//	{D3DXVECTOR3(-half_x,half_y, 0.f),D3DXVECTOR2(left_tu, top_tv)},
	//	{D3DXVECTOR3(half_x,half_y, 0.f),D3DXVECTOR2(right_tu, top_tv)},
	//	{D3DXVECTOR3(half_x,-half_y, 0.f),D3DXVECTOR2(right_tu, bottom_tv)},
	//	{D3DXVECTOR3(-half_x,-half_y, 0.f),D3DXVECTOR2(left_tu, bottom_tv)},
	//
	//};

	Ins_DXManager->GetStatus()->m_D3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, v, sizeof(CustomVertex));
}


//void DrawSlider(Slider& slider_, std::string file_name_) 
//{
//
//	float pos_x = slider_;
//	float pos_y = slider_;
//	float tex_x = 0.0f;
//	float tex_y = 0.0f;
//	float tex_width = tex_data->Width;
//	float tex_height = tex_data->Height;
//
//	// ����̒l��䗦�Ƃ��ĎZ�o����
//	float rate = (slider.CurrentValue - slider.MinValue) / (slider.MaxValue - slider.MinValue);
//
//	tex_width *= rate;
//
//	//// �e�i�s�����ɂ�鏈������������
//	//if (slider.Dir == Direction::LeftToRight)
//	//{
//	//	// �����ɔ䗦���|���ăT�C�Y�𒲐�����
//	//	tex_width *= rate;
//	//}
//	//else if (slider.Dir == Direction::RightToLeft)
//	//{
//	//	// �ŏ� => �ő�̕�����X���̍ŏ� => �ő傪�t�Ȃ̂Ŕ��]������
//	//	ReverseMove(rate, tex_width, pos_x, tex_x, tex_width);
//	//}
//	//else if (slider.Dir == Direction::UpToDown)
//	//{
//	//	// �c���ɔ䗦���|���ăT�C�Y�𒲐�����
//	//	tex_height *= rate;
//	//}
//	//else if (slider.Dir == Direction::DownToUp)
//	//{
//	//	// �ŏ� => �ő�̕�����Y���̍ŏ� => �ő傪�t�Ȃ̂Ŕ��]������
//	//	ReverseMove(rate, tex_height, pos_y, tex_y, tex_height);
//	//}
//
//	DrawUVMappingTexture(
//		pos_x,
//		pos_y,
//		tex_data,
//		tex_x,
//		tex_y,
//		tex_width,
//		tex_height
//	);
//}

bool Drawer2D::CreateTexture(std::string file_name_)
{
	Size size;
	D3DXIMAGE_INFO info;

	m_TextureList[file_name_] = new Texture;

	DXManager* Ins_DXManager = DXManager::GetInstance();

	if (Ins_DXManager == nullptr) { return false; }

	// 2�̗ݏ悶��Ȃ��P�[�X��z�肵�Č��̃T�C�Y���擾����D3DXCreateTextureFromFileEx�Ŏg��
	D3DXGetImageInfoFromFileA(file_name_.c_str(), &info);

	if (FAILED(D3DXCreateTextureFromFileExA(Ins_DXManager->GetStatus()->m_D3DDevice,
		file_name_.c_str(),
		info.Width,
		info.Height,
		1,
		0,
		D3DFMT_UNKNOWN,
		D3DPOOL_MANAGED,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		0x0000ff00,
		nullptr,
		nullptr,
		&m_TextureList[file_name_]->TexutreData)))
	{
		return false;
	}
	else
	{
		// �e�N�X�`���T�C�Y�̎擾
		D3DSURFACE_DESC desc;

		if (FAILED(m_TextureList[file_name_]->TexutreData->GetLevelDesc(0, &desc)))
		{
			m_TextureList[file_name_]->TexutreData->Release();
			return false;
		}
		m_TextureList[file_name_]->Width = desc.Width;
		m_TextureList[file_name_]->Height = desc.Height;
	}

	return true;
}
