#include "Camera.h"

Obj* g_Target = nullptr;
extern LPDIRECT3DDEVICE9 g_pD3DDevice;	// デバイス

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
	// 対象の座標
	D3DXVECTOR3 pos = g_Target->GetPos();
	// 対象の向きベクトル
	D3DXVECTOR3 target_vec = g_Target->GetForward();
	// カメラと対象の距離
	float distance = 5.0f;
	// TPS用高さ調整用オフセット
	float offset_height = 0.0f;

	// ベクトルを向きと反対にする
	target_vec *= -1.0f;
	target_vec.y += offset_height;

	// ベクトルから一定の距離を離れた場所をカメラ座標とする
	D3DXVECTOR3 cam_pos = pos + (target_vec * distance);

	//ビュー座標変換用の行列算出 start
	D3DXVECTOR3 up_vector(0.0f, 1.0f, 0.0f);	// カメラの向き

	D3DXMatrixIdentity(&view_matrix);
	D3DXMatrixLookAtLH(&view_matrix,
		&cam_pos,				// カメラ座標
		&pos,					// 注視点座標
		&up_vector);				// カメラの上の向きのベクトル
	g_pD3DDevice->SetTransform(D3DTS_VIEW, &view_matrix);
	//ビュー座標変換用の行列算出 end

}
