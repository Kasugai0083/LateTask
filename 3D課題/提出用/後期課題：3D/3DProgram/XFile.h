#pragma once

#include "DirectX.h"
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
	{
	}

	~XFile();

	bool Load(std::string file_name);
	void Draw();

	void SetXFileList(std::string file_name_) {
		
		m_pXFileList[file_name_] = new XFile();
		Load(file_name_);

	}

	XFile* GetXFileList(std::string string_) {
		return m_pXFileList[string_];
	}

private:
	// Material
	DWORD m_MaterialNum;
	D3DMATERIAL9* m_pMeshMaterialList;

	// Mesh
	LPD3DXMESH m_pMesh;

	// Texture
	LPDIRECT3DTEXTURE9* m_pTextureList;
	std::map<std::string, LPDIRECT3DTEXTURE9> m_TextureList;
	std::map<int, std::string> m_TextureNameList;

	// XFile
	std::map<std::string, XFile*> m_pXFileList;

};

