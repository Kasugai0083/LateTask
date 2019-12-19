#include "Camera.h"
#include "DirectX.h"

extern LPDIRECT3DDEVICE9 g_pD3DDevice;

void Camera::Update() {
	D3DXMATRIX matView;

	//ビュー座標変換用の行列算出 start
	D3DXVECTOR3 camera_pos(m_CameraPos.X, m_CameraPos.Y, m_CameraPos.Z); // カメラ位置
	D3DXVECTOR3 eye_pos(m_Gaze.X, m_Gaze.Y, m_Gaze.Z);		// 注視点
	D3DXVECTOR3 up_vector(0.0f, 1.0f, 0.0f);	// カメラの向き

	D3DXMatrixIdentity(&matView);
	D3DXMatrixLookAtLH(&matView,
		&camera_pos,				// カメラ座標
		&eye_pos,					// 注視点座標
		&up_vector);				// カメラの上の向きのベクトル
	g_pD3DDevice->SetTransform(D3DTS_VIEW, &matView);
	//ビュー座標変換用の行列算出 end
}