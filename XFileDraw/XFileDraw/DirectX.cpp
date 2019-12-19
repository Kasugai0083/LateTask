#include <Windows.h>
#include "DirectX.h"
#include <string>
#include <map>

// �O���[�o���ϐ�
LPDIRECT3D9 g_pD3DInterface;								// DirectX�C���^�[�t�F�[�X
D3DPRESENT_PARAMETERS *g_pD3DPresentParam;					// �v���[���g�p�����[�^
LPDIRECT3DDEVICE9 g_pD3DDevice;								// �f�o�C�X
std::map<std::string, LPDIRECT3DTEXTURE9> g_TextureList;	// �e�N�X�`�����X�g

/*
	DirectX�̏�����
		�߂�l�F
			����������
				�����F
					true
				���s�F
					false
		�����F
			HWND window_handle�F
				�E�B���h�E�n���h��
		���e�F
			DirectX�̏��������s��
*/
bool InitDirectX(HWND window_handle)
{
	// �C���^�[�t�F�[�X�쐬
	g_pD3DInterface = Direct3DCreate9(D3D_SDK_VERSION);
	if (g_pD3DInterface == NULL)
	{
		// �쐬���s
		return false;
	}

	// �v���[���g�p�����[�^�ݒ�
	g_pD3DPresentParam = new D3DPRESENT_PARAMETERS;
	if (g_pD3DPresentParam == NULL)
	{
		return false;
	}
	ZeroMemory(g_pD3DPresentParam, sizeof(D3DPRESENT_PARAMETERS));

	// �o�b�N�o�b�t�@�̐� => 1
	g_pD3DPresentParam->BackBufferCount = 1;
	// �o�b�N�o�b�t�@�̃t�H�[�}�b�g => D3DFMT_UNKNOWN(�t�H�[�}�b�g��m��܂���)
	g_pD3DPresentParam->BackBufferFormat = D3DFMT_UNKNOWN;
	// �E�B���h�E���[�h�ݒ� => �萔�Ő؂�ւ�
	g_pD3DPresentParam->Windowed = true;

	// �X���b�v�G�t�F�N�g�ݒ� => �f�B�X�v���C�h���C�o�ˑ�
	// �X���b�v�G�t�F�N�g => �o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�ւ̐؂�ւ����@
	g_pD3DPresentParam->SwapEffect = D3DSWAPEFFECT_DISCARD;

	//�f�v�X�ƃX�e���V���o�b�t�@�̗L���ݒ�
	g_pD3DPresentParam->EnableAutoDepthStencil = true;
	//�f�v�X�ƃX�e���V���o�b�t�@�̃t�H�[�}�b�g�ݒ�
	g_pD3DPresentParam->AutoDepthStencilFormat = D3DFMT_D16;

	// DirectDevice�̍쐬
	if (FAILED(g_pD3DInterface->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		window_handle,
		D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED,
		g_pD3DPresentParam,
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
	view_port.Width = g_pD3DPresentParam->BackBufferWidth;
	// �r���[�|�[�g�̍���
	view_port.Height = g_pD3DPresentParam->BackBufferHeight;
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

/*
	���W�ϊ��ݒ�
		�߂�l�F
			�Ȃ�
		�����F
			�Ȃ�
		���e�F
			�r���[���W�A�v���W�F�N�V�������W�ϊ����s��
*/
void Transform(void)
{
	D3DXMATRIX matProj;

	////�r���[���W�ϊ��p�̍s��Z�o start
	//D3DXVECTOR3 camera_pos(0.0f, 0.0f, -10.0f); // �J�����ʒu
	//D3DXVECTOR3 eye_pos(0.0f, 0.0f, 0.0f);		// �����_
	//D3DXVECTOR3 up_vector(0.0f, 1.0f, 0.0f);	// �J�����̌���

	//D3DXMatrixIdentity(&matView);
	//D3DXMatrixLookAtLH(&matView, 
	//	&camera_pos,				// �J�������W
	//	&eye_pos,					// �����_���W
	//	&up_vector);				// �J�����̏�̌����̃x�N�g��
	//g_pD3DDevice->SetTransform(D3DTS_VIEW, &matView);
	////�r���[���W�ϊ��p�̍s��Z�o end

	//�ˉe���W�ϊ��p�̍s��Z�o start
	D3DVIEWPORT9 vp;
	g_pD3DDevice->GetViewport(&vp);
	float aspect = (float)vp.Width / (float)vp.Height;

	D3DXMatrixPerspectiveFovLH(
		&matProj,
		D3DXToRadian(60),	// ��p
		aspect,				// �A�X�y�N�g��
		0.1f,				// near
		500.0f);			// far
	g_pD3DDevice->SetTransform(D3DTS_PROJECTION, &matProj);
	//�ˉe���W�ϊ��p�̍s��Z�o end
}


/*
	�`��J�n
		�߂�l�F
			�Ȃ�
		�����F
			�Ȃ�
		���e�F
			�`����n�߂邽�߂̏������s��
*/
void StartDraw(void)
{
	// �F�Ń����_�����O�^�[�Q�b�g���N���A
	g_pD3DDevice->Clear(0, 
		NULL,
		//�N���A����o�b�t�@�̐ݒ�
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		//�N���A�J���[
		D3DCOLOR_XRGB(0, 0, 255),
		//�f�v�X�o�b�t�@�̏����l
		1.0f,
		//�X�e���V���o�b�t�@�̏����l
		0);
	
	g_pD3DDevice->BeginScene();
}

/*
	�`��I��
		�߂�l�F
			�Ȃ�
		�����F
			�Ȃ�
		���e�F
			�`��I���̂��߂̏������s��
*/
void EndDraw(void)
{
	g_pD3DDevice->EndScene();
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

/*
	���C�g�̐ݒ�
		�߂�l�F
			�Ȃ�
		�����F
			�Ȃ�
		���e�F
			3D��ԂŎg�p���郉�C�g�̐ݒ���s��
*/
void SetLighting(void)
{
	D3DLIGHT9 light;
	D3DXVECTOR3 vec_direction(0, 0, 1);
	ZeroMemory(&light, sizeof(D3DLIGHT9));
	light.Type = D3DLIGHT_DIRECTIONAL;
	light.Diffuse.r = 1.0f;
	light.Diffuse.g = 1.0f;
	light.Diffuse.b = 1.0f;
	D3DXVec3Normalize((D3DXVECTOR3*)&light.Direction, &vec_direction);
	light.Range = 200.0f;
	g_pD3DDevice->SetLight(0, &light);
	g_pD3DDevice->LightEnable(0, true);
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
}