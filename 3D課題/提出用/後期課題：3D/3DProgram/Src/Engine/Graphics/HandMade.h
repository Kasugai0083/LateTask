#pragma once

#include <d3d9.h>
#include <d3dx9.h>

/**
* @brief
* 行列系の自作関数
*/

namespace HandMade {
	
	/**
	* @brief 行列を用いた座標移動
	* @out matrix_ 移動させるオブジェクトの行列
	* @in x_ オブジェクトに加えるX座標の値
	* @in y_ オブジェクトに加えるY座標の値
	* @in z_ オブジェクトに加えるZ座標の値
	*/
	void Translation(D3DXMATRIX* matrix_, float x_, float y_, float z_);
	
	/**
	* @brief ビルボード化する
	* @out out_ オブジェクトのワールド行列
	* @in in_ DirectX の View 行列
	*/
	void BillBoard(D3DXMATRIX* out_, D3DXMATRIX* in_);

	/**
	* @brief 行列を用いたオブジェクトの拡縮
	* @out matrix_ 拡縮させるオブジェクトの行列
	* @in x_ X軸の拡縮率
	* @in y_ Y軸の拡縮率
	* @in z_ Z軸の拡縮率
	*/
	void Scaling(D3DXMATRIX* matrix_, float x_, float y_, float z_);

	/**
	* @biref 行列を用いたオブジェクトの回転
	* @out matrix_ 回転させるオブジェクトの行列
	* @in radian_ 回転させる角度(度数法)
	*/
	void RotationX(D3DXMATRIX* matrix_, float radian_);
	void RotationY(D3DXMATRIX* matrix_, float radian_);
	void RotationZ(D3DXMATRIX* matrix_, float radian_);

}

