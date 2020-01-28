#pragma once

#include "..//..//Utility/Size.h"
#include <d3d9.h>
#include <d3dx9.h>
#include <string>
#include <map>

struct Texture{
	LPDIRECT3DTEXTURE9 TexutreData;	//!< �e�N�X�`���f�[�^
	int Width;						//!< ����
	int Height;						//!< �c��
};

struct CustomVertex {

	D3DXVECTOR3 pos;
	D3DXVECTOR2 tex_pos;

	//float X;			// X���W
	//float Y;			// Y���W
	//float Z;			// Z���W	
	//
	//float TextureX;		// �e�N�X�`�����WX
	//float TexrureY;		// �e�N�X�`�����WY
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