#include "Drawer.h"
#include "XFile.h"
#include "HandMade.h"

extern D3DXMATRIX matView;


void Drawer::Draw()
{

	DXManager* Ins_DXManager = DXManager::GetInstance();

	if (!Ins_DXManager) { return; }

	D3DXMATRIX world_matrix, trans_matrix, rot_matrix, scale_matrix;
	D3DXMATRIX rot_matrix_x, rot_matrix_y, rot_matrix_z;

	D3DXMATRIX view_matrix;

	D3DXMatrixIdentity(&world_matrix);
	D3DXMatrixIdentity(&rot_matrix);
	D3DXMatrixIdentity(&view_matrix);
	
	HandMadeTranslation(&trans_matrix, m_Pos.x, m_Pos.y, m_Pos.z);
	HandMadeScaling(&scale_matrix, m_Scale.x, m_Scale.y, m_Scale.z);

	HandMadeRotationX(&rot_matrix_x, D3DXToRadian(30.f));
	HandMadeRotationY(&rot_matrix_y, D3DXToRadian(30.f));
	HandMadeRotationZ(&rot_matrix_z, D3DXToRadian(30.f));

	rot_matrix *= rot_matrix_x * rot_matrix_y * rot_matrix_z;

#if 1
	HandMadeBillBoard(&view_matrix, &matView);
#endif

	world_matrix *= scale_matrix * trans_matrix * rot_matrix * view_matrix;

	Ins_DXManager->GetStatus()->m_D3DDevice->SetTransform(D3DTS_WORLD, &world_matrix);

	if(m_pXFile != NULL)
	{
		m_pXFile->Draw();
	}

}

