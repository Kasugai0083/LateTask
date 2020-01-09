#include <Windows.h>
#include "DirectX.h"
#include <string>
#include <map>

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
		D3DXToRadian(100),	// ��p
		aspect,				// �A�X�y�N�g��
		0.1f,				// near
		500.0f);			// far
	g_pD3DDevice->SetTransform(D3DTS_PROJECTION, &matProj);
	//�ˉe���W�ϊ��p�̍s��Z�o end
}



void HandMadeTranslation(D3DXMATRIX* matrix_, float x_, float y_, float z_) {
	D3DXMatrixIdentity(matrix_);

	matrix_->_41 += x_;
	matrix_->_42 += y_;
	matrix_->_43 += z_;

}
void HandMadeBillBoard(D3DXMATRIX* matrix_) {
	D3DXMatrixIdentity(matrix_);

	matrix_->_41 = 0.f;
	matrix_->_42 = 0.f;
	matrix_->_43 = 0.f;

}

void HandMadeScaling(D3DXMATRIX* matrix_, float x_, float y_, float z_) {
	D3DXMatrixIdentity(matrix_);

	matrix_->_11 = x_;
	matrix_->_22 = y_;
	matrix_->_33 = z_;
	
}

void HandMadeRotationX(D3DXMATRIX* matrix_, float radian_) {
	D3DXMatrixIdentity(matrix_);

	matrix_->_22 = cosf(radian_);
	matrix_->_23 = sinf(radian_);
	matrix_->_32 = -sinf(radian_);
	matrix_->_33 = cosf(radian_);

}

void HandMadeRotationY(D3DXMATRIX* matrix_, float radian_) {
	D3DXMatrixIdentity(matrix_);

	matrix_->_11 = cosf(radian_);
	matrix_->_13 = -sinf(radian_);
	matrix_->_31 = sinf(radian_);
	matrix_->_33 = cosf(radian_);

}
void HandMadeRotationZ(D3DXMATRIX* matrix_, float radian_) {
	D3DXMatrixIdentity(matrix_);

	matrix_->_11 = cosf(radian_);
	matrix_->_12 = sinf(radian_);
	matrix_->_21 = -sinf(radian_);
	matrix_->_22 = cosf(radian_);

}

void HandMadeMultiply(D3DXMATRIX* matrix_, D3DXMATRIX* matrix2_, D3DXMATRIX* matrix3_) {

	*matrix_ = (*matrix2_) * (*matrix3_);

}

void InverseViewMatrix(D3DXMATRIX* out)
{
	D3DXMatrixInverse(out, NULL, &matView);
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

void DrawBillBoard() 
{


	//���C�e�B���O�𖳌��ɂ���B
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	VERTEX v[4];

	// �O�p�`��`��
	// �|���S���̃��[�J�����W�̈ʒu���w�� start
	v[0].color = D3DCOLOR_ARGB(255, 255, 255, 255);
	v[1].color = D3DCOLOR_ARGB(255, 255, 255, 255);
	v[2].color = D3DCOLOR_ARGB(255, 255, 255, 255);
	v[0].pos.x = 0.0f; v[0].pos.y = 3.5f; v[0].pos.z = 0.0f;
	v[1].pos.x = 6.0f; v[1].pos.y = -2.5f; v[1].pos.z = 0.0f;
	v[2].pos.x = -6.0f; v[2].pos.y = -2.5f; v[2].pos.z = 0.0f;
	// �|���S���̃��[�J�����W�̈ʒu���w�� end

	//���[���h���W�ϊ��p�̍s��̎Z�o start
	D3DXMATRIX mat_world, mat_trans, mat_rot, mat_rotx, mat_roty, mat_rotz, mat_scale, mat_view;

	D3DXMatrixIdentity(&mat_world);
	D3DXMatrixIdentity(&mat_rot);
	D3DXMatrixIdentity(&mat_view);

	InverseViewMatrix(&mat_view);

	mat_view._41 = 0.f;
	mat_view._42 = 0.f;
	mat_view._43 = 0.f;

	//static float test2 = 1.f;
	//test2++;

	// �ړ�
	D3DXMatrixTranslation(&mat_trans, 0.f, 0.f, 0.f);

	// �|�����킹(�g�k * ��] * �ړ�)
	mat_world = mat_trans * mat_view;

	g_pD3DDevice->SetTransform(D3DTS_WORLD, &mat_world);
	//���[���h���W�ϊ��p�̍s��̎Z�o end

	g_pD3DDevice->SetFVF(D3DFVF_XYZ | D3DFVF_DIFFUSE);

	g_pD3DDevice->SetTexture(0, NULL);

	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 1, v, sizeof(VERTEX));



}


void Draw()
{
	//���C�e�B���O�𖳌��ɂ���B
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	VERTEX v[4];

	// �O�p�`��`��
	// �|���S���̃��[�J�����W�̈ʒu���w�� start
	v[0].color = D3DCOLOR_ARGB(255, 255, 255, 255);
	v[1].color = D3DCOLOR_ARGB(255, 255, 255, 255);
	v[2].color = D3DCOLOR_ARGB(255, 255, 255, 255);
	v[0].pos.x = 0.0f; v[0].pos.y = 3.5f; v[0].pos.z = 0.0f;
	v[1].pos.x = 6.0f; v[1].pos.y = -2.5f; v[1].pos.z = 0.0f;
	v[2].pos.x = -6.0f; v[2].pos.y = -2.5f; v[2].pos.z = 0.0f;
	// �|���S���̃��[�J�����W�̈ʒu���w�� end

	//���[���h���W�ϊ��p�̍s��̎Z�o start
	D3DXMATRIX mat_world, mat_trans, mat_rot, mat_rotx, mat_roty, mat_rotz, mat_scale;
	D3DXMatrixIdentity(&mat_world);
	D3DXMatrixIdentity(&mat_rot);

	// �ړ�
#if 0
	D3DXMatrixTranslation(&mat_trans, 0.0f, 10.0f, 10.0f);
#else 
	HandMadeTranslation(&mat_trans, 0.0f, 0.0f, 10.0f);
#endif
	// ��]

	static float test = 1.f;

	test++;

	//D3DXMatrixRotationX(&mat_rotx, D3DXToRadian(test));

	HandMadeRotationX(&mat_rotx, D3DXToRadian(0.f));

	//D3DXMatrixRotationY(&mat_roty, D3DXToRadian(test));
	HandMadeRotationY(&mat_roty, D3DXToRadian(0.f));

	//D3DXMatrixRotationZ(&mat_rotz, D3DXToRadian(test));
	HandMadeRotationZ(&mat_rotz, D3DXToRadian(0.f));

	/**
	* ������ => ���ʂ��󂯎��
	* ������ => �|�����킹��l
	* ��O���� => �|�����킹��l
	*/
	//D3DXMatrixMultiply(&mat_rot, &mat_rot, &mat_roty);
	//D3DXMatrixMultiply(&mat_rot, &mat_rot, &mat_rotx);
	//D3DXMatrixMultiply(&mat_rot, &mat_rot, &mat_rotz);

	HandMadeMultiply(&mat_rot, &mat_rot, &mat_roty);
	HandMadeMultiply(&mat_rot, &mat_rot, &mat_rotx);
	HandMadeMultiply(&mat_rot, &mat_rot, &mat_rotz);

	// �g��
#if 0
	D3DXMatrixScaling(&mat_scale, 1.0f, 1.0f, 1.0f);
#else
	HandMadeScaling(&mat_scale, 2.f, 2.f, 1.f);
#endif
	// �|�����킹(�g�k * ��] * �ړ�)
	mat_world *= mat_scale * mat_rot * mat_trans;

	g_pD3DDevice->SetTransform(D3DTS_WORLD, &mat_world);
	//���[���h���W�ϊ��p�̍s��̎Z�o end

	g_pD3DDevice->SetFVF(D3DFVF_XYZ | D3DFVF_DIFFUSE);

	g_pD3DDevice->SetTexture(0, NULL);

	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 1, v, sizeof(VERTEX));

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