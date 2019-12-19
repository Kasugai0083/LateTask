#include "Camera.h"
#include "DirectX.h"

extern LPDIRECT3DDEVICE9 g_pD3DDevice;

void Camera::Update() {
	D3DXMATRIX matView;

	//�r���[���W�ϊ��p�̍s��Z�o start
	D3DXVECTOR3 camera_pos(m_CameraPos.X, m_CameraPos.Y, m_CameraPos.Z); // �J�����ʒu
	D3DXVECTOR3 eye_pos(m_Gaze.X, m_Gaze.Y, m_Gaze.Z);		// �����_
	D3DXVECTOR3 up_vector(0.0f, 1.0f, 0.0f);	// �J�����̌���

	D3DXMatrixIdentity(&matView);
	D3DXMatrixLookAtLH(&matView,
		&camera_pos,				// �J�������W
		&eye_pos,					// �����_���W
		&up_vector);				// �J�����̏�̌����̃x�N�g��
	g_pD3DDevice->SetTransform(D3DTS_VIEW, &matView);
	//�r���[���W�ϊ��p�̍s��Z�o end
}