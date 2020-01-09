#include <math.h>
#include "XFile.h"
#include "Obj.h"

extern LPDIRECT3DDEVICE9 g_pD3DDevice;

D3DXVECTOR3 Obj::GetForward()
{
	D3DXVECTOR3 vec;
	float rad = D3DXToRadian(m_Angle.y);

	// XZ���ʂɑ΂��Ă̂݃x�N�g�������߂�
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
	�`��
		�߂�l�F
			�Ȃ�
		�����F
			�Ȃ�
		���e�F
			���[���h���W�s����쐬����XFile��`�悷��
*/
void Obj::Draw(void)
{
	// ���[���h���W�s��쐬 start
	D3DXMATRIX world_matrix, trans_matrix, rot_matrix, scale_matrix;
	D3DXMatrixIdentity(&world_matrix);
	D3DXMatrixTranslation(&trans_matrix, m_Pos.x, m_Pos.y, m_Pos.z);
	D3DXMatrixScaling(&scale_matrix, m_Scale.x, m_Scale.y, m_Scale.y);
	D3DXMatrixRotationY(&rot_matrix, D3DXToRadian(m_Angle.y));

	world_matrix *= scale_matrix * rot_matrix * trans_matrix;

	g_pD3DDevice->SetTransform(D3DTS_WORLD, &world_matrix);
	// ���[���h���W�s��쐬 end

	// Z�o�b�t�@��L���ɂ���
	g_pD3DDevice->SetRenderState(D3DRS_ZENABLE, true);

	if (m_pXFile != NULL)
	{
		m_pXFile->Draw();
	}
}