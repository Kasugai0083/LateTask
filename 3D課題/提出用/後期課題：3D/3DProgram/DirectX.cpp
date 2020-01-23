#include <Windows.h>
#include "DirectX.h"
#include "HandMade.h"

bool DXManager::InitDirectX(HWND window_handle)
{
	// �C���^�[�t�F�[�X�쐬
	m_DXStatus.m_D3DInterface = Direct3DCreate9(D3D_SDK_VERSION);
	if (m_DXStatus.m_D3DInterface == NULL)
	{
		// �쐬���s
		return false;
	}
	
	m_DXStatus.m_pD3DPresentParam = new D3DPRESENT_PARAMETERS;
	if (m_DXStatus.m_pD3DPresentParam == NULL)
	{
		return false;
	}
	ZeroMemory(m_DXStatus.m_pD3DPresentParam, sizeof(D3DPRESENT_PARAMETERS));

	// �o�b�N�o�b�t�@�̐� => 1
	m_DXStatus.m_pD3DPresentParam->BackBufferCount = 1;
	// �o�b�N�o�b�t�@�̃t�H�[�}�b�g => D3DFMT_UNKNOWN(�t�H�[�}�b�g��m��܂���)
	m_DXStatus.m_pD3DPresentParam->BackBufferFormat = D3DFMT_UNKNOWN;
	// �E�B���h�E���[�h�ݒ� => �萔�Ő؂�ւ�
	m_DXStatus.m_pD3DPresentParam->Windowed = true;

	// �X���b�v�G�t�F�N�g�ݒ� => �f�B�X�v���C�h���C�o�ˑ�
	// �X���b�v�G�t�F�N�g => �o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�ւ̐؂�ւ����@
	m_DXStatus.m_pD3DPresentParam->SwapEffect = D3DSWAPEFFECT_DISCARD;

	// DirectDevice�̍쐬
	if (FAILED(m_DXStatus.m_D3DInterface->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		window_handle,
		D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED,
		m_DXStatus.m_pD3DPresentParam,
		&m_DXStatus.m_D3DDevice)))
	{
		return false;
	}

	// �r���[�|�[�g�p�����[�^
	D3DVIEWPORT9 view_port;

	// �r���[�|�[�g�̍�����W
	view_port.X = 0;
	view_port.Y = 0;
	// �r���[�|�[�g�̕�
	view_port.Width = m_DXStatus.m_pD3DPresentParam->BackBufferWidth;
	// �r���[�|�[�g�̍���
	view_port.Height = m_DXStatus.m_pD3DPresentParam->BackBufferHeight;
	// �r���[�|�[�g�[�x�ݒ�
	view_port.MinZ = 0.0f;
	view_port.MaxZ = 1.0f;

	// �r���[�|�[�g�ݒ�
	if (FAILED(m_DXStatus.m_D3DDevice->SetViewport(&view_port)))
	{
		return false;
	}

	return true;
}

D3DXMATRIX matProj, matView;

void DXManager::Transform()
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
	m_DXStatus.m_D3DDevice->SetTransform(D3DTS_VIEW, &matView);
	//�r���[���W�ϊ��p�̍s��Z�o end

	//�ˉe���W�ϊ��p�̍s��Z�o start
	D3DVIEWPORT9 vp;
	m_DXStatus.m_D3DDevice->GetViewport(&vp);
	float aspect = (float)vp.Width / (float)vp.Height;

	D3DXMatrixPerspectiveFovLH(
		&matProj,
		D3DXToRadian(60),	// ��p
		aspect,				// �A�X�y�N�g��
		0.1f,				// near
		500.0f);			// far
	m_DXStatus.m_D3DDevice->SetTransform(D3DTS_PROJECTION, &matProj);
	//�ˉe���W�ϊ��p�̍s��Z�o end
}

void DXManager::StartDraw() {
	m_DXStatus.m_D3DDevice->Clear(0L,
		NULL,
		D3DCLEAR_TARGET,
		D3DCOLOR_ARGB(255, 0, 0, 255),
		1.0f,	// Z�o�b�t�@�̏����l
		0);		// �X�e���V���o�b�t�@�̏����l

	m_DXStatus.m_D3DDevice->BeginScene();
}

void DXManager::EndDraw() {

	m_DXStatus.m_D3DDevice->EndScene();

	m_DXStatus.m_D3DDevice->Present(NULL, NULL, NULL, NULL);
}

void DXManager::SetLighting() {
	D3DLIGHT9 light;
	D3DXVECTOR3 vec_direction(0, 0, 1);
	ZeroMemory(&light, sizeof(D3DLIGHT9));

	light.Type = D3DLIGHT_DIRECTIONAL;
	light.Diffuse.r = 1.f;
	light.Diffuse.g = 1.f;
	light.Diffuse.b = 1.f;

	D3DXVec3Normalize((D3DXVECTOR3*)& light.Direction, &vec_direction);
	light.Range = 200.f;
	m_DXStatus.m_D3DDevice->SetLight(0, &light);
	m_DXStatus.m_D3DDevice->LightEnable(0, true);
	m_DXStatus.m_D3DDevice->SetRenderState(D3DRS_LIGHTING, true);
}

//void DXManager::SendStatus(DXStatus* status_)
//{
//	if (m_DXStatus.m_D3DDevice == nullptr) { return; }
//	*status_ = m_DXStatus;
//}