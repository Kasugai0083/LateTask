#include "XFile.h"
#include <map>

extern std::map<std::string, LPDIRECT3DTEXTURE9> g_TextureList;
extern LPDIRECT3DDEVICE9 g_pD3DDevice;
std::map<std::string, XFile*>g_pXFileList;

bool XFile::Load(std::string file_name)
{

	LPD3DXBUFFER p_material_buffer = NULL;

	if (FAILED(D3DXLoadMeshFromXA(
		file_name.c_str(),
		D3DXMESH_SYSTEMMEM,
		g_pD3DDevice,
		NULL,
		&p_material_buffer,
		NULL,
		&m_MaterialNum,
		&m_pMesh
	)))
	{
		return false;
	}

	m_pMeshMaterialList = new D3DMATERIAL9[m_MaterialNum];

	m_pTextureList = new LPDIRECT3DTEXTURE9[m_MaterialNum];

	D3DXMATERIAL* pmat_list = (D3DXMATERIAL*)p_material_buffer->GetBufferPointer();

	for (DWORD i = 0; i < m_MaterialNum; i++)
	{
		m_pMeshMaterialList[i] = pmat_list[i].MatD3D;
		m_pTextureList[i] = NULL;

		if(pmat_list[i].pTextureFilename != NULL)
		{
			file_name = pmat_list[i].pTextureFilename;
			LPDIRECT3DTEXTURE9 texture = NULL;
			if(g_TextureList[file_name] == NULL)
			{
				D3DXCreateTextureFromFileA(g_pD3DDevice,
											file_name.c_str(),
											&g_TextureList[file_name]);
			}

			m_pTextureList[i] = g_TextureList[file_name];
			m_TextureNameList[i] = file_name;

		}
	}
	p_material_buffer->Release();

	return true;
}


XFile::~XFile()
{

	if(m_pMeshMaterialList != NULL)
	{
		delete[](m_pMeshMaterialList);
		m_pMeshMaterialList = NULL;
	}

	if (m_pTextureList != NULL) 
	{
		for(int i = 0; i < m_MaterialNum; i++)
		{
			if(m_pTextureList[i] != NULL &&
				g_TextureList[m_TextureNameList[i]] != NULL)
			{
			
			}
		}
	}

}
