#pragma once

#include <string>
#include <d3d9.h>
#include <d3dx9.h>
#include <map>

class XFile
{
public:
	XFile() :
		m_MaterialNum(0),
		m_pMesh(NULL),
		m_pMeshMaterialList(NULL),
		m_pTextureList(NULL)
	{}

	~XFile();

	bool Load(std::string file_name);
	void Draw();

private:
	DWORD m_MaterialNum;
	LPD3DXMESH m_pMesh;
	D3DMATERIAL9* m_pMeshMaterialList;
	LPDIRECT3DTEXTURE9* m_pTextureList;
	std::map<int, std::string> m_TextureNameList;
};

