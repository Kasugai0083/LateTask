#pragma once

#include "DirectX.h"
#include <d3d9.h>
#include <d3dx9.h>

class XFile;

class Drawer
{
public:
	Drawer(D3DXVECTOR3 pos_, D3DXVECTOR3 scale_, D3DXVECTOR3 angle_, XFile* xfile_) :
		m_Pos(pos_),
		m_Scale(scale_),
		m_Angle(angle_),
		m_pXFile(xfile_)
	{
		Ins_DXManager = DXManager::GetInstance();
		Ins_DXManager->SendStatus(m_DXStatus);
	}

	void Draw();

private:
	D3DXVECTOR3 m_Pos, m_Scale, m_Angle;

	DXManager* Ins_DXManager;
	DXStatus m_DXStatus;

	XFile* m_pXFile;
};

