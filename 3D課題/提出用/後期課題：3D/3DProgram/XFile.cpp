#include "XFile.h"
#include <map>

std::map<std::string, XFile*>g_pXFileList;

bool XFile::Load(std::string file_name)
{

	LPD3DXBUFFER p_material_buffer = NULL;

	/*
		file_name のデータを LoadMeshFromXA で出力
		
		p_material_buffer,
		m_MaterialNum,
		m_pMesh,

		に値を入力
	*/
	if (FAILED(D3DXLoadMeshFromXA(
		file_name.c_str(),
		D3DXMESH_SYSTEMMEM,
		m_DXStatus.m_D3DDevice,
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
			std::string file_name = pmat_list[i].pTextureFilename;
			LPDIRECT3DTEXTURE9 texture = NULL;
			if(m_TextureList[file_name] == NULL)
			{
				D3DXCreateTextureFromFileA(m_DXStatus.m_D3DDevice,
											file_name.c_str(),
											&m_TextureList[file_name]);
			}

			m_pTextureList[i] = m_TextureList[file_name];
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
				m_TextureList[m_TextureNameList[i]] != NULL)
			{
				m_TextureList[m_TextureNameList[i]]->Release();
				m_pTextureList[i] = NULL;
			}
		}

		delete[](m_pTextureList);
		m_pTextureList = NULL;

	}

	m_TextureNameList.clear();
}

void XFile::Draw()
{
	for(DWORD i = 0; i < m_MaterialNum; i++)
	{
		m_DXStatus.m_D3DDevice->SetMaterial(&m_pMeshMaterialList[i]);

		m_DXStatus.m_D3DDevice->SetTexture(0, m_pTextureList[i]);

		m_pMesh->DrawSubset(i);
	}

}