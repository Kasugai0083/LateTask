#include <math.h>
#include "XFile.h"
#include "Obj.h"

extern LPDIRECT3DDEVICE9 g_pD3DDevice;

D3DXVECTOR3 Obj::GetForward()
{
	D3DXVECTOR3 vec;
	float rad = D3DXToRadian(m_Angle.y);

	// XZ平面に対してのみベクトルを求める
	vec.x = sinf(rad);
	vec.y = 0.0f;
	vec.z = cosf(rad);

	return vec;
}

void Obj::Update()
{
	m_Angle.y += 2.0f;
}

/*
	描画
		戻り値：
			なし
		引数：
			なし
		内容：
			ワールド座標行列を作成してXFileを描画する
*/
void Obj::Draw(void)
{
	// ワールド座標行列作成 start
	D3DXMATRIX world_matrix, trans_matrix, rot_matrix, scale_matrix;
	D3DXMatrixIdentity(&world_matrix);
	D3DXMatrixTranslation(&trans_matrix, m_Pos.x, m_Pos.y, m_Pos.z);
	D3DXMatrixScaling(&scale_matrix, m_Scale.x, m_Scale.y, m_Scale.y);
	D3DXMatrixRotationY(&rot_matrix, D3DXToRadian(m_Angle.y));

	world_matrix *= scale_matrix * rot_matrix * trans_matrix;

	g_pD3DDevice->SetTransform(D3DTS_WORLD, &world_matrix);
	// ワールド座標行列作成 end

	// Zバッファを有効にする
	g_pD3DDevice->SetRenderState(D3DRS_ZENABLE, true);

	if (m_pXFile != NULL)
	{
		m_pXFile->Draw();
	}
}