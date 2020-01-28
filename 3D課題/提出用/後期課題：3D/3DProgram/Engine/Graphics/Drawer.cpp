#include "Drawer.h"
#include "XFile.h"
#include "HandMade.h"

extern D3DXMATRIX matView;

void Drawer::Draw()
{

	DXManager* Ins_DXManager = DXManager::GetInstance();

	if (!Ins_DXManager) { return; }

	D3DXMatrixIdentity(&world_matrix);
	D3DXMatrixIdentity(&rot_matrix);
	D3DXMatrixIdentity(&view_matrix);
	
	HandMadeTranslation(&trans_matrix, m_Pos.x, m_Pos.y, m_Pos.z);
	HandMadeScaling(&scale_matrix, m_Scale.x, m_Scale.y, m_Scale.z);

	HandMadeRotationX(&rot_matrix_x, D3DXToRadian(m_Angle.x));
	HandMadeRotationY(&rot_matrix_y, D3DXToRadian(m_Angle.y));
	HandMadeRotationZ(&rot_matrix_z, D3DXToRadian(m_Angle.z));

	rot_matrix *= rot_matrix_x * rot_matrix_y * rot_matrix_z;

#if 1
	HandMadeBillBoard(&view_matrix, &matView);
#endif

	world_matrix *= scale_matrix * trans_matrix * rot_matrix * view_matrix;

	Ins_DXManager->GetStatus()->m_D3DDevice->SetTransform(D3DTS_WORLD, &world_matrix);

	if (m_pXFile) { m_pXFile->Draw(); }

}

void Drawer::SetStatus(D3DXVECTOR3 pos_, D3DXVECTOR3 scale_, D3DXVECTOR3 angle_, std::string name_) {
	m_Pos = pos_;
	m_Scale = scale_;
	m_Angle = angle_;
	m_pXFile = m_pXFileList[name_];
}

bool Drawer::LoadXFile(std::string name_) {
	m_pXFileList[name_] = new XFile;
	m_pXFileList[name_]->Load(name_);

	if (m_pXFileList[name_]) { return true; }
	
	return false;
}