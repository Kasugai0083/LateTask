#include "XFile.h"
#include <map>

extern std::map<std::string, LPDIRECT3DTEXTURE9> g_TextureList;
extern LPDIRECT3DDEVICE9 g_pD3DDevice;
std::map<std::string, XFile *>g_pXFileList;	// �ǂݍ���XFile�̃��X�g

/*
	XFile�ǂݍ���
		�߂�l�F
			�ǂݍ��݌��ʁF
				�����F
					true
				���s�F
					false
		�����F
			std::string file_name�F
				�t�@�C����
		���e�F
			XFile�̓ǂݍ��݂��s��
*/
bool XFile::Load(std::string file_name)
{
	// XFile�f�[�^���i�[���鉼�o�b�t�@
	LPD3DXBUFFER p_material_buffer = NULL;

	// �@�DXFile�̓ǂݍ��� start
	if (FAILED(D3DXLoadMeshFromXA(
		file_name.c_str(),
		D3DXMESH_SYSTEMMEM,
		g_pD3DDevice,
		NULL,
		&p_material_buffer,
		NULL,
		&m_MaterialNum,
		&m_pMesh) ) )
	{
		return false;
	}
	// �@�DXFile�̓ǂݍ��� end

	// �A.�}�e���A�����̃R�s�[ start
	// �ǂݍ��܂ꂽXFile�̃}�e���A������D3DMATERIAL9��p�ӂ���
	m_pMeshMaterialList = new D3DMATERIAL9[m_MaterialNum];

	// ���b�V���Ɏg�p����Ă���e�N�X�`���p�̔z���p�ӂ���
	m_pTextureList = new LPDIRECT3DTEXTURE9[m_MaterialNum];

	// �o�b�t�@�̐擪�|�C���^��D3DXMATERIAL�ɃL���X�g���Ď擾
	D3DXMATERIAL *pmat_list = (D3DXMATERIAL*)p_material_buffer->GetBufferPointer();

	// �e���b�V���̃}�e���A�������擾����
	for (DWORD i = 0; i < m_MaterialNum; i++)
	{
		// �}�e���A���擾
		m_pMeshMaterialList[i] = pmat_list[i].MatD3D;
		m_pTextureList[i] = NULL;

		// �}�e���A���Őݒ肳��Ă���e�N�X�`���ǂݍ���
		if (pmat_list[i].pTextureFilename != NULL)
		{
			std::string file_name = pmat_list[i].pTextureFilename;
			LPDIRECT3DTEXTURE9 texture = NULL;
			if (g_TextureList[file_name] == NULL)
			{
				D3DXCreateTextureFromFileA(g_pD3DDevice,
											file_name.c_str(),
											&g_TextureList[file_name]);
			}

			m_pTextureList[i] = g_TextureList[file_name];
			m_TextureNameList[i] = file_name;
		}
	}

	// �}�e���A���̃R�s�[���I������̂Ńo�b�t�@���������
	p_material_buffer->Release();
	// �A.�}�e���A�����̃R�s�[ end

	return true;
}

XFile::~XFile(void)
{
	// �}�e���A�����X�g�̉��
	if (m_pMeshMaterialList != NULL)
	{
		delete[] (m_pMeshMaterialList);
		m_pMeshMaterialList = NULL;
	}

	// �e�N�X�`�����X�g�̉��
	if (m_pTextureList != NULL)
	{
		for (int i = 0; i < m_MaterialNum; i++)
		{
			if (m_pTextureList[i] != NULL &&
				g_TextureList[m_TextureNameList[i]] != NULL)
			{
				// �e�N�X�`���̉��
				g_TextureList[m_TextureNameList[i]]->Release();
				m_pTextureList[i] = NULL;
			}
		}

		delete[] (m_pTextureList);
		m_pTextureList = NULL;
	}

	// �e�N�X�`���t�@�C�������X�g�̏�����
	m_TextureNameList.clear();
}

void XFile::Draw(void)
{
	for (DWORD i = 0; i < m_MaterialNum; i++)
	{
		// �}�e���A���̐ݒ�
		g_pD3DDevice->SetMaterial(&m_pMeshMaterialList[i]);
		// �e�N�X�`���̐ݒ�
		g_pD3DDevice->SetTexture(0, m_pTextureList[i]);
		// ���b�V����`��
		m_pMesh->DrawSubset(i);
	}
}
