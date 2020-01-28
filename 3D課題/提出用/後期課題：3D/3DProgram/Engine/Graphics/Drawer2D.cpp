#include "Drawer2D.h"
#include "DirectX.h"
#include "HandMade.h"

void Drawer2D::DrawTexture(float x, float y,float z, std::string file_name_)
{
	DXManager* Ins_DXManager = DXManager::GetInstance();
	if (!Ins_DXManager) { return; }

	D3DXMATRIXA16 world, trans, scale;
	D3DXMatrixIdentity(&world);
	D3DXMatrixIdentity(&trans);
	D3DXMatrixIdentity(&scale);

	HandMadeScaling(&scale,0.01f,0.01f,0.01f);

	D3DXMatrixTranslation(&trans, -5.f, -5.f, 0.f);

	HandMadeBillBoard(&world, Ins_DXManager->GetViewMatrix());

	world *= scale * trans;

	Ins_DXManager->GetStatus()->m_D3DDevice->SetTransform(D3DTS_WORLD, &world);

	float left_tu = 0.f;
	float right_tu = 1.f;
	float top_tv = 0.f;
	float bottom_tv = 1.f;
	
	if (m_TextureList[file_name_] != nullptr) {
		left_tu = x / m_TextureList[file_name_]->Width;
		right_tu =( x + m_TextureList[file_name_]->Width ) / m_TextureList[file_name_]->Width;
		top_tv = y / m_TextureList[file_name_]->Height;
		bottom_tv = (y + m_TextureList[file_name_]->Height) / m_TextureList[file_name_]->Height;
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

	// 頂点構造の指定
	Ins_DXManager->GetStatus()->m_D3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);	// RHWで無い頂点はLIGHTが効くので無効にしておく

	Ins_DXManager->GetStatus()->m_D3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	Ins_DXManager->GetStatus()->m_D3DDevice->SetFVF(D3DFVF_XYZ | D3DFVF_TEX1);

	Ins_DXManager->GetStatus()->m_D3DDevice->SetTexture(0, m_TextureList[file_name_]->TexutreData);

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
