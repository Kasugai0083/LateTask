#include "Camera.h"

Obj* g_Target = nullptr;
extern LPDIRECT3DDEVICE9 g_pD3DDevice;	// �f�o�C�X

void SetCameraTarget(Obj* obj)
{
	g_Target = obj;
}

void UpdateCamera()
{
	if (g_Target == nullptr)
	{
		return;
	}

	D3DXMATRIX view_matrix;
	// �Ώۂ̍��W
	D3DXVECTOR3 pos = g_Target->GetPos();
	// �Ώۂ̌����x�N�g��
	D3DXVECTOR3 target_vec = g_Target->GetForward();
	// �J�����ƑΏۂ̋���
	float distance = 5.0f;
	// TPS�p���������p�I�t�Z�b�g
	float offset_height = 0.0f;

	// �x�N�g���������Ɣ��΂ɂ���
	target_vec *= -1.0f;
	target_vec.y += offset_height;

	// �x�N�g��������̋����𗣂ꂽ�ꏊ���J�������W�Ƃ���
	D3DXVECTOR3 cam_pos = pos + (target_vec * distance);

	//�r���[���W�ϊ��p�̍s��Z�o start
	D3DXVECTOR3 up_vector(0.0f, 1.0f, 0.0f);	// �J�����̌���

	D3DXMatrixIdentity(&view_matrix);
	D3DXMatrixLookAtLH(&view_matrix,
		&cam_pos,				// �J�������W
		&pos,					// �����_���W
		&up_vector);				// �J�����̏�̌����̃x�N�g��
	g_pD3DDevice->SetTransform(D3DTS_VIEW, &view_matrix);
	//�r���[���W�ϊ��p�̍s��Z�o end

}
