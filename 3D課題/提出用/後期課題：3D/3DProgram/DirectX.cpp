#include <Windows.h>
#include "DirectX.h"
#include <string>
#include <map>
#include "HandMade.h"

// �O���[�o���ϐ�
LPDIRECT3D9 g_pD3DInterface;	// DirectX�C���^�[�t�F�[�X
D3DPRESENT_PARAMETERS *g_pD3DPresentParam;
LPDIRECT3DDEVICE9 g_pD3DDevice;
std::map<std::string, LPDIRECT3DTEXTURE9> g_TextureList;	// �e�N�X�`�����X�g


bool InitDirectX(HWND window_handle)
{
	// �C���^�[�t�F�[�X�쐬
	g_pD3DInterface = Direct3DCreate9(D3D_SDK_VERSION);
	if (g_pD3DInterface == NULL)
	{
		// �쐬���s
		return false;
	}

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

D3DXMATRIX matProj, matView;

void Transform()
{

	static float test = 1.f;

	static const D3DXVECTOR3 TargetPos(0.f,0.f,0.f);

	test++;

	float rad = test * 3.14f / 180.f;
	float distance = 10.0f;
	D3DXVECTOR3 vec = D3DXVECTOR3(
		sinf(rad) * distance,
		0.0f,
		-cosf(rad) * distance
	);



	//�r���[���W�ϊ��p�̍s��Z�o start
	D3DXVECTOR3 camera_pos(0.f, 0.f, -5.f); // �J�����ʒu
	D3DXVECTOR3 eye_pos(0.0f, 0.0f, 0.0f);		// �����_
	D3DXVECTOR3 up_vector(0.0f, 1.0f, 0.0f);	// �J�����̌���

	camera_pos.z += vec.z;
	camera_pos.x += vec.x;

	D3DXMatrixIdentity(&matView);
	D3DXMatrixLookAtLH(&matView, 
		&camera_pos,				// �J�������W
		&eye_pos,					// �����_���W
		&up_vector);				// �J�����̏�̌����̃x�N�g��
	g_pD3DDevice->SetTransform(D3DTS_VIEW, &matView);
	//�r���[���W�ϊ��p�̍s��Z�o end

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

void StartDraw() {
	g_pD3DDevice->Clear(0L,
		NULL,
		D3DCLEAR_TARGET,
		D3DCOLOR_ARGB(255, 0, 0, 255),
		1.0f,	// Z�o�b�t�@�̏����l
		0);		// �X�e���V���o�b�t�@�̏����l

	g_pD3DDevice->BeginScene();
}

void EndDraw() {

	g_pD3DDevice->EndScene();

	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

void SetLighting() {
	D3DLIGHT9 light;
	D3DXVECTOR3 vec_direction(0, 0, 1);
	ZeroMemory(&light, sizeof(D3DLIGHT9));

	light.Type = D3DLIGHT_DIRECTIONAL;
	light.Diffuse.r = 1.f;
	light.Diffuse.g = 1.f;
	light.Diffuse.b = 1.f;

	D3DXVec3Normalize((D3DXVECTOR3*)& light.Direction, &vec_direction);
	light.Range = 200.f;
	g_pD3DDevice->SetLight(0, &light);
	g_pD3DDevice->LightEnable(0, true);
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
}