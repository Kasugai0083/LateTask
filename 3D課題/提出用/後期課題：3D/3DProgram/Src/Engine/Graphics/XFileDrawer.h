#pragma once

#include "DirectX.h"
#include "XFile.h"
#include <d3d9.h>
#include <d3dx9.h>

/**
* @brief
* XFile を描画するクラス
*/

class XFile;

class XFileDrawer
{
public:

	/**
	* @brief XFile を描画する
	* @param pos_ オブジェクトの座標 
	* @param scale_  オブジェクトの拡縮
	* @param angle_  オブジェクトの回転
	* @param name_  オブジェクトの名前
	*/
	void Draw(D3DXVECTOR3 pos_, D3DXVECTOR3 scale_, D3DXVECTOR3 angle_, std::string name_);

	/**
	* @brief XFile をビルボードを適用して描画する
	* @param pos_ オブジェクトの座標
	* @param scale_  オブジェクトの拡縮
	* @param angle_  オブジェクトの回転
	* @param name_  オブジェクトの名前
	*/
	void DrawBillbord(D3DXVECTOR3 pos_, D3DXVECTOR3 scale_, D3DXVECTOR3 angle_, std::string name_);

	/**
	* @brief XFile を読み込む
	* @param name_ XFile の名前を指定
	*/
	bool Load(std::string name_);

	/**
	* @brief 読み込んだ XFile を解放
	*/
	void ReleaseXFile() {
		m_pXFileList.clear();
	}

private:
	/**
	* @brief Draw() の内で使用\n
	* 移動・拡縮・回転を関数を用いて計算する
	*/
	void Trans(D3DXVECTOR3 pos_, D3DXVECTOR3 scale_, D3DXVECTOR3 angle_);
private:
	D3DXVECTOR3 m_Pos, m_Scale, m_Angle; 								//!< @brief オブジェクト情報

	D3DXMATRIX world_matrix, trans_matrix, view_matrix; 				//!< @brief 座標系の行列

	D3DXMATRIX rot_matrix_x, rot_matrix_y, rot_matrix_z, rot_matrix; 	//!< @brief 回転行列

	D3DXMATRIX scale_matrix; 											//!< @brief 拡縮行列

	std::map<std::string, XFile*> m_pXFileList; 						//!< @brief 画像情報をリスト化

};

