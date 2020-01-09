#include "XFile.h"
#include "Drawer.h"

extern LPDIRECT3DDEVICE9 g_pD3DDevice;

/*
	�`��
		�߂�l�F
			�Ȃ�
		�����F
			�Ȃ�
		���e�F
			���[���h���W�s����쐬����XFile��`�悷��
*/
void Drawer::Draw(void)
{
	// ���[���h���W�s��쐬 start
	D3DXMATRIX world_matrix, trans_matrix, rot_matrix, scale_matrix;
	D3DXMatrixIdentity(&world_matrix);
	D3DXMatrixTranslation(&trans_matrix, m_Pos.x, m_Pos.y, m_Pos.z);
	D3DXMatrixScaling(&scale_matrix, m_Scale.x, m_Scale.y, m_Scale.y);
	world_matrix *= scale_matrix * trans_matrix;
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &world_matrix);
	// ���[���h���W�s��쐬 end

	if (m_pXFile != NULL)
	{
		m_pXFile->Draw();
	}
}