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
		file_name.c_str(),		//�t�@�C����
		D3DXMESH_SYSTEMMEM,		//�Œ�łn�j
		g_pD3DDevice,			//DirectX�O���t�B�b�N�f�o�C�X
		NULL,					//����͎g��Ȃ�
		&p_material_buffer,		//material_buffer�𒼐ڗ��p���Ă��ǂ�
		NULL,					//����͎g��Ȃ�
		&m_MaterialNum,			//out �}�e���A���̐�
		&m_pMesh) ) )			//out ���b�V���f�[�^
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

//�f�X�g���N�^
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

	//���b�V���̉��
	//m_pMeshMaterialList
	if (m_pMesh != nullptr) {
		delete[](m_pMesh);
		m_pMesh = nullptr;
	}

	// �e�N�X�`���t�@�C�������X�g�̏�����
	m_TextureNameList.clear();
}

void XFile::Draw(void)
{

	//D3DXMATRIX world;
	//D3DXMATRIX translate;
	//D3DXMATRIX scale;
	//D3DXMATRIX rot_x;
	//D3DXMATRIX rot_y;
	//D3DXMATRIX rot_z;
	//D3DXMATRIX rot;

	//m_X += 0.00f;
	//m_Y += 0.00f;
	//m_Z += 0.0f;

	//m_Scale = 1.0f;

	////�P�ʍs��
	//D3DXMatrixIdentity(&world);
	//D3DXMatrixIdentity(&translate);
	//D3DXMatrixIdentity(&scale);
	//D3DXMatrixIdentity(&rot_x);
	//D3DXMatrixIdentity(&rot_y);
	//D3DXMatrixIdentity(&rot_z);
	//D3DXMatrixIdentity(&rot);

	////�ړ��s��쐬
	//D3DXMatrixTranslation(&translate, m_X, m_Y, m_Z);

	////�g�k�s��쐬
	//D3DXMatrixScaling(&scale, m_Scale, m_Scale, m_Scale);

	////��]�s��쐬
	//D3DXMatrixRotationX(&rot_x, D3DXToRadian(30.0f));
	//D3DXMatrixRotationY(&rot_y, D3DXToRadian(60.0f));
	//D3DXMatrixRotationZ(&rot_z, D3DXToRadian(45.0f));
	//rot = rot_x * rot_y * rot_z;

	////���[���h�s��쐬
	//world *= scale * rot * translate;

	////���[���h�s��ݒ�
	//g_pD3DDevice->SetTransform(D3DTS_WORLD, &world);

	//XFile�`�掞�̂݃f�v�X�o�b�t�@��ON�ɂ���
	g_pD3DDevice->SetRenderState(D3DRS_ZENABLE, true);

	for (DWORD i = 0; i < m_MaterialNum; i++)
	{
		// �}�e���A���̐ݒ�
		g_pD3DDevice->SetMaterial(&m_pMeshMaterialList[i]);
		// �e�N�X�`���̐ݒ�
		g_pD3DDevice->SetTexture(0, m_pTextureList[i]);
		// ���b�V����`��
		m_pMesh->DrawSubset(i);

	}
	// �}�e���A���̐ݒ�͎���SetMaterial�܂ň����p�����
	g_pD3DDevice->SetMaterial(NULL);


	g_pD3DDevice->SetRenderState(D3DRS_ZENABLE, false);

}


void XFile::Update() {
}