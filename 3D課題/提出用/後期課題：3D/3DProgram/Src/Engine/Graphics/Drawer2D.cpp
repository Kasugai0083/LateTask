#include "Drawer2D.h"
#include "DirectX.h"
#include "HandMade.h"

void Drawer2D::DrawSetting(CustomVertex v_, std::string file_name_) {

	DXManager* Ins_DXManager = DXManager::GetInstance();
	if (!Ins_DXManager) { return; }

	D3DXMATRIXA16 world, trans, scale;
	D3DXMatrixIdentity(&world);
	D3DXMatrixIdentity(&trans);
	D3DXMatrixIdentity(&scale);

	HandMadeScaling(&scale, 0.01f, 0.01f, 0.01f);

	D3DXMatrixTranslation(&trans, v_.pos.x, v_.pos.y, v_.pos.z);

	HandMadeBillBoard(&world, Ins_DXManager->GetViewMatrix());

	world *= scale * trans;

	Ins_DXManager->GetStatus()->m_D3DDevice->SetTransform(D3DTS_WORLD, &world);

	// 頂点構造の指定
	Ins_DXManager->GetStatus()->m_D3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);	// RHWで無い頂点はLIGHTが効くので無効にしておく

	Ins_DXManager->GetStatus()->m_D3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	Ins_DXManager->GetStatus()->m_D3DDevice->SetFVF(D3DFVF_XYZ | D3DFVF_TEX1);

	Ins_DXManager->GetStatus()->m_D3DDevice->SetTexture(0, m_TextureList[file_name_]->TexutreData);

}

void Drawer2D::DrawTexture(CustomVertex v_, std::string file_name_)
{
	DXManager* Ins_DXManager = DXManager::GetInstance();
	if (!Ins_DXManager) { return; }

	DrawSetting(v_, file_name_);

	float left_tu = 0.f;
	float right_tu = 1.f;
	float top_tv = 0.f;
	float bottom_tv = 1.f;
	
	if (m_TextureList[file_name_] != nullptr) {
		left_tu = v_.tex_pos.x / m_TextureList[file_name_]->Width;
		right_tu =(v_.tex_pos.x + m_TextureList[file_name_]->Width ) / m_TextureList[file_name_]->Width;
		top_tv = v_.tex_pos.y / m_TextureList[file_name_]->Height;
		bottom_tv = (v_.tex_pos.y + m_TextureList[file_name_]->Height) / m_TextureList[file_name_]->Height;
	}

	float half_x = m_TextureList[file_name_]->Width / 2.f;
	float half_y = m_TextureList[file_name_]->Height / 2.f;

	CustomVertex v[4] =
	{
		
		{D3DXVECTOR3(-half_x,half_y, 0.f),D3DXVECTOR2(left_tu, top_tv)},
		{D3DXVECTOR3(half_x,half_y, 0.f),D3DXVECTOR2(right_tu, top_tv)},
		{D3DXVECTOR3(half_x,-half_y, 0.f),D3DXVECTOR2(right_tu, bottom_tv)},
		{D3DXVECTOR3(-half_x,-half_y, 0.f),D3DXVECTOR2(left_tu, bottom_tv)},

	};

	Ins_DXManager->GetStatus()->m_D3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, v, sizeof(CustomVertex));
}


bool Drawer2D::CreateTexture(std::string file_name_)
{
	Size size;
	D3DXIMAGE_INFO info;

	m_TextureList[file_name_] = new Texture;

	DXManager* Ins_DXManager = DXManager::GetInstance();

	if (Ins_DXManager == nullptr) { return false; }

	// 2の累乗じゃないケースを想定して元のサイズを取得してD3DXCreateTextureFromFileExで使う
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
		// テクスチャサイズの取得
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
