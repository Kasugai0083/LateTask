#pragma once

#include "DirectX.h"
#include "XFile.h"
#include <d3d9.h>
#include <d3dx9.h>

class XFile;

class Drawer
{
public:

	void DrawXFile(D3DXVECTOR3 pos_, D3DXVECTOR3 scale_, D3DXVECTOR3 angle_, std::string name_);
	void DrawBillbord(D3DXVECTOR3 pos_, D3DXVECTOR3 scale_, D3DXVECTOR3 angle_, std::string name_);

	bool LoadXFile(std::string name_);

	void ReleaseXFile() {
		m_pXFileList.clear();
	}
private:
	void Trans(D3DXVECTOR3 pos_, D3DXVECTOR3 scale_, D3DXVECTOR3 angle_, std::string name_);
private:
	// オブジェクト情報
	D3DXVECTOR3 m_Pos, m_Scale, m_Angle;

	// 行列
	D3DXMATRIX world_matrix, trans_matrix, rot_matrix, scale_matrix;
	D3DXMATRIX rot_matrix_x, rot_matrix_y, rot_matrix_z;

	D3DXMATRIX view_matrix;

	// 画像情報をリスト化
	std::map<std::string, XFile*> m_pXFileList;
};

