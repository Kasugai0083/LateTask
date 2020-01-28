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
	}

	void Draw();

private:
	// オブジェクト情報
	D3DXVECTOR3 m_Pos, m_Scale, m_Angle;

	// 画像情報
	XFile* m_pXFile;
};

