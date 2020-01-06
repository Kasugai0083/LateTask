#include "XFile.h"
#include "Drawer.h"

extern LPDIRECT3DDEVICE9 g_pD3DDevice;

/*
	描画
		戻り値：
			なし
		引数：
			なし
		内容：
			ワールド座標行列を作成してXFileを描画する
*/
void Drawer::Draw(void)
{
	// ワールド座標行列作成 start
	D3DXMATRIX world_matrix, trans_matrix, rot_matrix, scale_matrix;
	D3DXMatrixIdentity(&world_matrix);
	D3DXMatrixTranslation(&trans_matrix, m_Pos.x, m_Pos.y, m_Pos.z);
	D3DXMatrixScaling(&scale_matrix, m_Scale.x, m_Scale.y, m_Scale.y);
	// ワールド座標行列作成 end

	//回転行列を追加
	D3DXMATRIX rot_matrix_x, rot_matrix_y, rot_matrix_z;

	D3DXMatrixIdentity(&rot_matrix);
	D3DXMatrixIdentity(&rot_matrix_x);
	D3DXMatrixIdentity(&rot_matrix_y);
	D3DXMatrixIdentity(&rot_matrix_z);

	D3DXMatrixRotationX(&rot_matrix_x, D3DXToRadian(m_Angle.x));
	D3DXMatrixRotationY(&rot_matrix_y, D3DXToRadian(m_Angle.y));
	D3DXMatrixRotationZ(&rot_matrix_z, D3DXToRadian(m_Angle.z));

	rot_matrix = rot_matrix_x * rot_matrix_y * rot_matrix_z;

	world_matrix *= scale_matrix  * rot_matrix * trans_matrix;
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &world_matrix);


	if (m_pXFile != NULL)
	{
		m_pXFile->Draw();
	}
}

void Drawer::Update() {


	//AngleのY軸を毎フレーム0.1f増加させる
	m_Angle.y += 0.1f;
	//ScaleのYを毎フレーム0.1f増減させる
	//最大2.0f,最小0.5を繰り返す
	if (PlusSwitch == true) {
		m_Scale.y += 0.1f;
	}
	else {
		m_Scale.y -= 0.1f;
	}

	if (m_Scale.y >= 2.0f) {
		PlusSwitch = false;
	}
	else if (m_Scale.y <= 0.5f) {
		PlusSwitch = true;
	}

}