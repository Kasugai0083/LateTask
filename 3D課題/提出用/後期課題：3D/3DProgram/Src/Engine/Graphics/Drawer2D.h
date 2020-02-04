#pragma once

#include "..//..//Utility/Vec2.h"
#include "..//..//Utility/Vec3.h"
#include "..//..//Utility/Size.h"
#include <d3d9.h>
#include <d3dx9.h>
#include <string>
#include <map>
#include <vector>

/**
* @brief
* 2Dポリゴン用の画像を保存・描画するクラス
*/

class LineDesc;


/**
* Texture のデータとサイズを管理する構造体
*/
struct Texture{
	LPDIRECT3DTEXTURE9 TexutreData;		//!< テクスチャデータ
	float Width;						//!< 横幅
	float Height;						//!< 縦幅
};

/**
* @brief ポリゴン描画に必要な頂点情報
* @param pos 座標
* @param tex_pos テクスチャ座標
*/
struct CustomVertex {

	D3DXVECTOR3 pos;
	D3DXVECTOR2 tex_pos;

};

/**
* @brief ポリゴン描画に必要な頂点情報
* @param pos 座標
* @param tex_pos_start テクスチャ座標開始点
* @param tex_pos_end テクスチャ座標終了点
*/
struct VertexPos {

	Pos3 pos;
	Pos2 tex_pos_start, tex_pos_end;

};

class Drawer2D
{
public:

	/**
	* @brief テクスチャを貼り付けたポリゴンを描画する
	* @param v_ ポリゴンの頂点情報 と テクスチャの座標情報
	* @param file_name_ m_TextureList の要素
	*/
	void DrawTexture(VertexPos v_, std::string file_name_);

	/**
	* @brief m_TextureList にテクスチャ情報を入力
	* @param file_name_ 要素番号を指定
	*/
	bool CreateTexture(std::string file_name_);

	/**
	* @brief 曲線の描画
	* @param 曲線の頂点情報
	*/
	void DrawLine(std::vector<LineDesc> desc_list);

	Texture* GetTexture(std::string file_name_) { return m_TextureList[file_name_]; }

private:

	void DrawSetting(float x_, float y_, float z_, std::string file_name_); //!< @brief DirectXのデバイス や 行列情報の初期化

private:

	std::map<std::string, Texture*>m_TextureList; //!< @brief 画像情報を保管

};