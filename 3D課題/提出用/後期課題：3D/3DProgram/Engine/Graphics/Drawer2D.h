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

};

class Drawer2D
{
public:

	void DrawTexture(CustomVertex v_, std::string file_name_);

	//bool CreateTexture(const char* file_name_);
	bool CreateTexture(std::string file_name_);

	void DrawSlider();

private:
	void DrawSetting(CustomVertex v_, std::string file_name_);
private:
	std::map<std::string, Texture*>m_TextureList;

};