#include "DirectX.h"
#include "HandMade.h"
#include <Windows.h>

bool DXManager::InitDirectX(HWND window_handle)
{
	// インターフェース作成
	m_DXStatus.m_D3DInterface = Direct3DCreate9(D3D_SDK_VERSION);
	if (m_DXStatus.m_D3DInterface == NULL)
	{
		// 作成失敗
		return false;
	}
	
	m_DXStatus.m_pD3DPresentParam = new D3DPRESENT_PARAMETERS;
	if (m_DXStatus.m_pD3DPresentParam == NULL)
	{
		return false;
	}
	ZeroMemory(m_DXStatus.m_pD3DPresentParam, sizeof(D3DPRESENT_PARAMETERS));

	// バックバッファの数 => 1
	m_DXStatus.m_pD3DPresentParam->BackBufferCount = 1;
	// バックバッファのフォーマット => D3DFMT_UNKNOWN(フォーマットを知りません)
	m_DXStatus.m_pD3DPresentParam->BackBufferFormat = D3DFMT_UNKNOWN;
	// ウィンドウモード設定 => 定数で切り替え
	m_DXStatus.m_pD3DPresentParam->Windowed = true;

	// スワップエフェクト設定 => ディスプレイドライバ依存
	// スワップエフェクト => バックバッファとフロントバッファへの切り替え方法
	m_DXStatus.m_pD3DPresentParam->SwapEffect = D3DSWAPEFFECT_DISCARD;

	// DirectDeviceの作成
	if (FAILED(m_DXStatus.m_D3DInterface->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		window_handle,
		D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED,
		m_DXStatus.m_pD3DPresentParam,
		&m_DXStatus.m_D3DDevice)))
	{
		return false;
	}

	// ビューポートパラメータ
	D3DVIEWPORT9 view_port;

	// ビューポートの左上座標
	view_port.X = 0;
	view_port.Y = 0;
	// ビューポートの幅
	view_port.Width = m_DXStatus.m_pD3DPresentParam->BackBufferWidth;
	// ビューポートの高さ
	view_port.Height = m_DXStatus.m_pD3DPresentParam->BackBufferHeight;
	// ビューポート深度設定
	view_port.MinZ = 0.0f;
	view_port.MaxZ = 1.0f;

	// ビューポート設定
	if (FAILED(m_DXStatus.m_D3DDevice->SetViewport(&view_port)))
	{
		return false;
	}

	return true;
}

void DXManager::Transform()
{
	//ビュー座標変換用の行列算出 start

	D3DXVECTOR3 camera_pos(0.f, 0.f, -10.f); // カメラ位置
	D3DXVECTOR3 eye_pos(0.0f, 0.0f, 0.0f);		// 注視点
	D3DXVECTOR3 up_vector(0.0f, 1.0f, 0.0f);	// カメラの向き
	
	// カメラの移動
	static float test = 1.f;

	test++;

	float rad = test * 3.14f / 180.f;
	float distance = 10.0f;
	D3DXVECTOR3 vec = D3DXVECTOR3(
		sinf(rad) * distance,
		0.0f,
		-cosf(rad) * distance
	);

	camera_pos.z += vec.z;
	camera_pos.x += vec.x;
	//カメラの移動 end

	D3DXMatrixIdentity(&m_MatView);
	D3DXMatrixLookAtLH(&m_MatView, 
		&camera_pos,				// カメラ座標
		&eye_pos,					// 注視点座標
		&up_vector);				// カメラの上の向きのベクトル
	m_DXStatus.m_D3DDevice->SetTransform(D3DTS_VIEW, &m_MatView);
	//ビュー座標変換用の行列算出 end

	//射影座標変換用の行列算出 start
	D3DVIEWPORT9 vp;
	m_DXStatus.m_D3DDevice->GetViewport(&vp);
	float aspect = (float)vp.Width / (float)vp.Height;

	D3DXMatrixPerspectiveFovLH(
		&m_MatProj,
		D3DXToRadian(60),	// 画角
		aspect,				// アスペクト比
		0.1f,				// near
		10000.0f);			// far
	m_DXStatus.m_D3DDevice->SetTransform(D3DTS_PROJECTION, &m_MatProj);
	//射影座標変換用の行列算出 end
}

void DXManager::StartDraw() {
	m_DXStatus.m_D3DDevice->Clear(0L,
		NULL,
		D3DCLEAR_TARGET,
		D3DCOLOR_ARGB(255, 0, 0, 255),
		1.0f,	// Zバッファの初期値
		0);		// ステンシルバッファの初期値

	m_DXStatus.m_D3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	m_DXStatus.m_D3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_DXStatus.m_D3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	m_DXStatus.m_D3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

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

bool DXManager::CreateFontDevice(Size size_) {

	if (FAILED(D3DXCreateFont(m_DXStatus.m_D3DDevice,
		size_.Width,
		size_.Height,
		FW_REGULAR,
		NULL,
		FALSE,
		DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS,
		PROOF_QUALITY,
		FIXED_PITCH | FF_SCRIPT,
		TEXT("ＭＳ　Ｐゴシック"),
		&m_Font)))
	{
		return false;
	}
	return true;
}