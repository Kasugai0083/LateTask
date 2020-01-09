#include "Drawer.h"
#include "XFile.h"

extern LPDIRECT3DDEVICE9 g_pD3DDevice;

void Drawer::Draw()
{
	D3DXMATRIX world_matrix, trans_matrix, rot_matrix, scale_matrix;

	D3DXMatrixIdentity(&world_matrix);
	D3DXMatrixTranslation(&trans_matrix, m_Pos.x, m_Pos.y, m_Pos.z);
	D3DXMatrixScaling(&scale_matrix, m_Scale.x, m_Scale.y, m_Scale.z);
	world_matrix *= scale_matrix * trans_matrix;
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &world_matrix);

	if(m_pXFile != NULL)
	{
		m_pXFile->Draw();
	}

}

