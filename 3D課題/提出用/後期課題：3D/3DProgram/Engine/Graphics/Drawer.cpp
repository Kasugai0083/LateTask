#include "Drawer.h"
#include "XFile.h"
#include "HandMade.h"

void Drawer::Trans(D3DXVECTOR3 pos_, D3DXVECTOR3 scale_, D3DXVECTOR3 angle_, std::string name_) {

	D3DXMatrixIdentity(&world_matrix);
	D3DXMatrixIdentity(&rot_matrix);
	D3DXMatrixIdentity(&view_matrix);

	HandMadeTranslation(&trans_matrix, pos_.x, pos_.y, pos_.z);
	HandMadeScaling(&scale_matrix, scale_.x, scale_.y, scale_.z);

	HandMadeRotationX(&rot_matrix_x, D3DXToRadian(angle_.x));
	HandMadeRotationY(&rot_matrix_y, D3DXToRadian(angle_.y));
	HandMadeRotationZ(&rot_matrix_z, D3DXToRadian(angle_.z));

	rot_matrix *= rot_matrix_x * rot_matrix_y * rot_matrix_z;

}

void Drawer::DrawXFile(D3DXVECTOR3 pos_, D3DXVECTOR3 scale_, D3DXVECTOR3 angle_, std::string name_)
{

	DXManager* Ins_DXManager = DXManager::GetInstance();

	if (!Ins_DXManager) { return; }

	Trans(pos_,scale_,angle_, name_);

	world_matrix *= scale_matrix * trans_matrix * rot_matrix * view_matrix;

	Ins_DXManager->GetStatus()->m_D3DDevice->SetTransform(D3DTS_WORLD, &world_matrix);

	if (m_pXFileList[name_]) { m_pXFileList[name_]->Draw(); }

}

void Drawer::DrawBillbord(D3DXVECTOR3 pos_, D3DXVECTOR3 scale_, D3DXVECTOR3 angle_, std::string name_)
{
	DXManager* Ins_DXManager = DXManager::GetInstance();

	if (!Ins_DXManager) { return; }

	Trans(pos_, scale_, angle_, name_);

	HandMadeBillBoard(&view_matrix, Ins_DXManager->GetViewMatrix());

	world_matrix *= scale_matrix * trans_matrix * rot_matrix * view_matrix;

	Ins_DXManager->GetStatus()->m_D3DDevice->SetTransform(D3DTS_WORLD, &world_matrix);

	if (m_pXFileList[name_]) { m_pXFileList[name_]->Draw(); }

}

bool Drawer::LoadXFile(std::string name_) {
	m_pXFileList[name_] = new XFile;
	m_pXFileList[name_]->Load(name_);

	if (m_pXFileList[name_]) { return true; }
	
	return false;
}