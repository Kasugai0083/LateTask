#include "Drawer2D.h"
#include "DirectX.h"
#include "HandMade.h"
#include "Grid.h"
#include <vector>

void Drawer2D::DrawSetting(float x_, float y_, float z_, std::string file_name_ = "JohnDo") {
	// DirectX のインスタンス化
	DXManager* Ins_DXManager = DXManager::GetInstance();
	if (!Ins_DXManager) { return; }

	// ワールド, 移動, 拡縮行列を用意
	D3DXMATRIXA16 world, trans, scale, rot;
	D3DXMatrixIdentity(&world);
	D3DXMatrixIdentity(&trans);
	D3DXMatrixIdentity(&scale);
	D3DXMatrixIdentity(&rot);

	// 拡縮
	HandMadeScaling(&scale, 0.01f, 0.01f, 0.01f);

	// 移動
	D3DXMatrixTranslation(&trans, x_, y_, z_);

	// ビルボード化
	HandMadeBillBoard(&world, Ins_DXManager->GetViewMatrix());

	// 拡縮と移動行列を反映
	world *= scale * trans * rot;
	Ins_DXManager->GetStatus()->m_D3DDevice->SetTransform(D3DTS_WORLD, &world);

	// ライティング
	Ins_DXManager->GetStatus()->m_D3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);	// RHWで無い頂点はLIGHTが効くので無効にしておく

	// カルモード(板の裏っかわも描画)
	Ins_DXManager->GetStatus()->m_D3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	Ins_DXManager->GetStatus()->m_D3DDevice->SetFVF(D3DFVF_XYZ | D3DFVF_TEX1);
	
	if (file_name_ != "JohnDo") {
		Ins_DXManager->GetStatus()->m_D3DDevice->SetTexture(0, m_TextureList[file_name_]->TexutreData);
	}

}

void Drawer2D::DrawTexture(VertexPos v_, std::string file_name_)
{
	DXManager* Ins_DXManager = DXManager::GetInstance();
	if (!Ins_DXManager) { return; }

	DrawSetting(v_.pos.X, v_.pos.Y, v_.pos.Z, file_name_);

	float left_tu = 0.f;
	float right_tu = 1.f;
	float top_tv = 0.f;
	float bottom_tv = 1.f;
	
	if (m_TextureList[file_name_] != nullptr) {
		left_tu = v_.tex_pos_start.X / m_TextureList[file_name_]->Width;
		right_tu =(v_.tex_pos_start.X + v_.tex_pos_end.X) / m_TextureList[file_name_]->Width;
		top_tv = v_.tex_pos_start.Y / m_TextureList[file_name_]->Height;
		bottom_tv = (v_.tex_pos_start.Y + v_.tex_pos_end.Y) / m_TextureList[file_name_]->Height;
	}

	CustomVertex v[] =
	{
		{ D3DXVECTOR3(v_.tex_pos_start.X, v_.tex_pos_start.Y + v_.tex_pos_end.Y, 0.0f), D3DXVECTOR2(left_tu, top_tv) },		// 左上
		{ D3DXVECTOR3(v_.tex_pos_start.X + v_.tex_pos_end.X, v_.tex_pos_start.Y + v_.tex_pos_end.Y, 0.0f), D3DXVECTOR2(right_tu, top_tv) }, // 右上
		{ D3DXVECTOR3(v_.tex_pos_start.X + v_.tex_pos_end.X, v_.tex_pos_start.Y, 0.0f), D3DXVECTOR2(right_tu, bottom_tv) },	// 右下
		{ D3DXVECTOR3(v_.tex_pos_start.X, v_.tex_pos_start.Y, 0.0f), D3DXVECTOR2(left_tu, bottom_tv) },
	};

	Ins_DXManager->GetStatus()->m_D3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, v, sizeof(CustomVertex));
}

// 曲線の描画現在調整中
void Drawer2D::DrawLine(std::vector<LineDesc> desc_list)
{
	// DirectX のインスタンス化
	DXManager* Ins_DXManager = DXManager::GetInstance();
	if (!Ins_DXManager) { return; }

	DrawSetting(desc_list[0].m_Pos.X, desc_list[0].m_Pos.Y, desc_list[0].m_Pos.Z);

	struct LineVertex
	{
		float x;
		float y;
		float z;

		float w;

		DWORD color;
	};

	std::vector<LineVertex> vertex_list;

	for (int i = 0; i < (int)desc_list.size(); i++)
	{
		float tu = 0.0f;
		float tv = 0.0f;

		DWORD color = D3DCOLOR_ARGB((int)(255 * desc_list[i].m_Alpha), 255, 255, 255);
		LineVertex new_vertex =
		{
			desc_list[i].m_Pos.X,
			desc_list[i].m_Pos.Y,
			desc_list[0].m_Pos.Z,
			1.0f,
			color
		};

		vertex_list.push_back(new_vertex);
	}

	Ins_DXManager->GetStatus()->m_D3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, vertex_list.size() - 2, &vertex_list[0], sizeof(LineVertex));
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
