#pragma once

#include "..//..//Utility/Size.h"
#include <d3d9.h>
#include <d3dx9.h>
#include <string>
#include <map>

struct Texture{
	LPDIRECT3DTEXTURE9 TexutreData;	//!< テクスチャデータ
	int Width;						//!< 横幅
	int Height;						//!< 縦幅
};

struct CustomVertex {

	D3DXVECTOR3 pos;
	D3DXVECTOR2 tex_pos;

	//float X;			// X座標
	//float Y;			// Y座標
	//float Z;			// Z座標	
	//
	//float TextureX;		// テクスチャ座標X
	//float TexrureY;		// テクスチャ座標Y
};

class Drawer2D
{
public:

	void DrawTexture(float x, float y, float z, std::string file_name_);

	//bool CreateTexture(const char* file_name_);
	bool CreateTexture(std::string file_name_);

private:

	std::map<std::string, Texture*>m_TextureList;

};