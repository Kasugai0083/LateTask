#include "DirectGraphics.h"

// �ÓI���C�u����
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

// �O���[�o���ϐ�
static TEXTURE_DATA g_TextureList[MAX_TEXTURE_NUM];

static LPDIRECT3D9 g_pD3DInterface;	// DirectX�C���^�[�t�F�[�X
static LPDIRECT3DDEVICE9 g_pD3DDevice;
static D3DXMATRIX g_MatView;

bool InitDirectGraphics(HWND window_handle)
{
	D3DPRESENT_PARAMETERS present_param;

	// �C���^�[�t�F�[�X�쐬
	g_pD3DInterface = Direct3DCreate9(D3D_SDK_VERSION);
	if (g_pD3DInterface == NULL)
	{
		// �쐬���s
		return false;
	}

	ZeroMemory(&present_param, sizeof(D3DPRESENT_PARAMETERS));

	// �o�b�N�o�b�t�@�̐� => 1
	present_param.BackBufferCount = 1;
	// �o�b�N�o�b�t�@�̃t�H�[�}�b�g => D3DFMT_UNKNOWN(�t�H�[�}�b�g��m��܂���)
	present_param.BackBufferFormat = D3DFMT_UNKNOWN;
	// �E�B���h�E���[�h�ݒ� => �萔�Ő؂�ւ�
	present_param.Windowed = true;

	// �X���b�v�G�t�F�N�g�ݒ� => �f�B�X�v���C�h���C�o�ˑ�
	// �X���b�v�G�t�F�N�g => �o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�ւ̐؂�ւ����@
	present_param.SwapEffect = D3DSWAPEFFECT_DISCARD;

	// DirectDevice�̍쐬
	if (FAILED(g_pD3DInterface->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		window_handle,
		D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED,
		&present_param,
		&g_pD3DDevice)))
	{
		return false;
	}

	// �r���[�|�[�g�p�����[�^
	D3DVIEWPORT9 view_port;

	// �r���[�|�[�g�̍�����W
	view_port.X = 0;
	view_port.Y = 0;
	// �r���[�|�[�g�̕�
	view_port.Width = present_param.BackBufferWidth;
	// �r���[�|�[�g�̍���
	view_port.Height = present_param.BackBufferHeight;
	// �r���[�|�[�g�[�x�ݒ�
	view_port.MinZ = 0.0f;
	view_port.MaxZ = 1.0f;

	// �r���[�|�[�g�ݒ�
	if (FAILED(g_pD3DDevice->SetViewport(&view_port)))
	{
		return false;
	}

	return true;
}

const LPDIRECT3DDEVICE9 GetD3DDevice()
{
	return g_pD3DDevice;
}

int LoadTexture(const char *file_name, int use_id)
{
	int select_id = -1;

	if (use_id < 0 || use_id >= MAX_TEXTURE_NUM)
	{
		use_id = -1;
	}

	if (use_id == -1)
	{
		for (int i = 0; i < MAX_TEXTURE_NUM; i++)
		{
			if (g_TextureList[i].m_pTexture == NULL)
			{
				select_id = i;
				break;
			}
		}
	}else {
		if (g_TextureList[use_id].m_pTexture != NULL)
		{
			ReleaseTexture(use_id);
		}

		select_id = use_id;
	}

	if (select_id == -1)
	{
		return -1;
	}
	D3DXIMAGE_INFO info;
	// 2�̊K�悶��Ȃ��̂Ō��̃T�C�Y���擾����D3DXCreateTextureFromFileEx�Ŏg��
	D3DXGetImageInfoFromFile(file_name, &info);

	if (FAILED( D3DXCreateTextureFromFileEx(g_pD3DDevice,
										file_name,
										info.Width,
										info.Height,
										1,
										0,
										D3DFMT_UNKNOWN,
										D3DPOOL_MANAGED,
										D3DX_DEFAULT,
										D3DX_DEFAULT,
										0x0000ff00,
										NULL,
										NULL,
										&g_TextureList[select_id].m_pTexture)))
	{
		return -1;
	} else {
		// �e�N�X�`���T�C�Y�̎擾
		D3DSURFACE_DESC desc;

		if( FAILED( g_TextureList[select_id].m_pTexture->GetLevelDesc( 0, &desc ) ))
		{
			g_TextureList[select_id].m_pTexture->Release();
			g_TextureList[select_id].m_pTexture = NULL;
			return -1;
		}
		g_TextureList[select_id].m_Width = desc.Width;
		g_TextureList[select_id].m_Height = desc.Height;
	}

	return select_id;
}

bool IsUseTexture(int texture_id)
{
	if (g_TextureList[texture_id].m_pTexture != NULL)
	{
		return true;
	}

	return false;
}

void InverseViewMatrix(D3DXMATRIX *out)
{
	D3DXMatrixInverse(out, NULL, &g_MatView);
}

void Transform(const D3DXVECTOR3 *camera_pos, const D3DXVECTOR3 *eye_pos)
{
	D3DXMATRIX matProj;

	// �@�D�J�����̃r���[�s����쐬����
	//�r���[���W�ϊ��p�̍s��Z�o
	// �J�����̌���
	D3DXVECTOR3 up_vector(0.0f, 1.0f, 0.0f);

	D3DXMatrixIdentity(&g_MatView);
	D3DXMatrixLookAtLH(&g_MatView, 
		camera_pos,	// �J�������W
		eye_pos,	// �����_���W
		&up_vector);// �J�����̏�̌����̃x�N�g��
	g_pD3DDevice->SetTransform(D3DTS_VIEW, &g_MatView);

	//�ˉe���W�ϊ��p�̍s��Z�o
	D3DVIEWPORT9 vp;
	g_pD3DDevice->GetViewport(&vp);
	float aspect = (float)vp.Width / (float)vp.Height;

	D3DXMatrixPerspectiveFovLH(
		&matProj,
		D3DXToRadian(45),	// ��p
		aspect,				// �A�X�y�N�g��
		0.1f,				// near
		500.0f);			// far
	g_pD3DDevice->SetTransform(D3DTS_PROJECTION, &matProj);
}

const TEXTURE_DATA *GetTextureData(int texture_id)
{
	return &g_TextureList[texture_id];
}
void DrawTexture(TEXTURE_DATA rect_data[4], int texture_id)
{

}

void ReleaseTexture(int texture_id)
{
	if (texture_id < 0 ||
		texture_id >= MAX_TEXTURE_NUM)
	{
		return;
	}

	if (g_TextureList[texture_id].m_pTexture != NULL)
	{
		g_TextureList[texture_id].m_pTexture->Release();
		g_TextureList[texture_id].m_pTexture = NULL;
	}
}

void DrawStart()
{
	g_pD3DDevice->Clear(0L,
		NULL,
		D3DCLEAR_TARGET,			// ����������o�b�t�@�̎��
		D3DCOLOR_ARGB(255, 255, 255, 255),// �t���[���o�b�t�@�̏������F
		1.0f,						// Z�o�b�t�@�̏����l
		0);							// �X�e���V���o�b�t�@�̏����l

	g_pD3DDevice->BeginScene();
}

void DrawEnd()
{
	g_pD3DDevice->EndScene();

	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}


void ReleaseDirectGraphics()
{
	for (int i = 0; i < MAX_TEXTURE_NUM; i++)
	{
		ReleaseTexture(i);
	}

	g_pD3DDevice->Release();
	g_pD3DInterface->Release();
}
