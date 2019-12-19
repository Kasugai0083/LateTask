#include <Windows.h>
#include "DirectX.h"
#include <string>
#include <map>

// グローバル変数
LPDIRECT3D9 g_pD3DInterface;								// DirectXインターフェース
D3DPRESENT_PARAMETERS *g_pD3DPresentParam;					// プレゼントパラメータ
LPDIRECT3DDEVICE9 g_pD3DDevice;								// デバイス
std::map<std::string, LPDIRECT3DTEXTURE9> g_TextureList;	// テクスチャリスト

/*
	DirectXの初期化
		戻り値：
			初期化結果
				成功：
					true
				失敗：
					false
		引数：
			HWND window_handle：
				ウィンドウハンドル
		内容：
			DirectXの初期化を行う
*/
bool InitDirectX(HWND window_handle)
{
	// インターフェース作成
	g_pD3DInterface = Direct3DCreate9(D3D_SDK_VERSION);
	if (g_pD3DInterface == NULL)
	{
		// 作成失敗
		return false;
	}

	// プレゼントパラメータ設定
	g_pD3DPresentParam = new D3DPRESENT_PARAMETERS;
	if (g_pD3DPresentParam == NULL)
	{
		return false;
	}
	ZeroMemory(g_pD3DPresentParam, sizeof(D3DPRESENT_PARAMETERS));

	// バックバッファの数 => 1
	g_pD3DPresentParam->BackBufferCount = 1;
	// バックバッファのフォーマット => D3DFMT_UNKNOWN(フォーマットを知りません)
	g_pD3DPresentParam->BackBufferFormat = D3DFMT_UNKNOWN;
	// ウィンドウモード設定 => 定数で切り替え
	g_pD3DPresentParam->Windowed = true;

	// スワップエフェクト設定 => ディスプレイドライバ依存
	// スワップエフェクト => バックバッファとフロントバッファへの切り替え方法
	g_pD3DPresentParam->SwapEffect = D3DSWAPEFFECT_DISCARD;

	//デプスとステンシルバッファの有効設定
	g_pD3DPresentParam->EnableAutoDepthStencil = true;
	//デプスとステンシルバッファのフォーマット設定
	g_pD3DPresentParam->AutoDepthStencilFormat = D3DFMT_D16;

	// DirectDeviceの作成
	if (FAILED(g_pD3DInterface->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		window_handle,
		D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED,
		g_pD3DPresentParam,
		&g_pD3DDevice)))
	{
		return false;
	}

	// ビューポートパラメータ
	D3DVIEWPORT9 view_port;

	// ビューポートの左上座標
	view_port.X = 0;
	view_port.Y = 0;
	// ビューポートの幅
	view_port.Width = g_pD3DPresentParam->BackBufferWidth;
	// ビューポートの高さ
	view_port.Height = g_pD3DPresentParam->BackBufferHeight;
	// ビューポート深度設定
	view_port.MinZ = 0.0f;
	view_port.MaxZ = 1.0f;

	// ビューポート設定
	if (FAILED(g_pD3DDevice->SetViewport(&view_port)))
	{
		return false;
	}

	return true;
}

/*
	座標変換設定
		戻り値：
			なし
		引数：
			なし
		内容：
			ビュー座標、プロジェクション座標変換を行う
*/
void Transform(void)
{
	D3DXMATRIX matProj;

	////ビュー座標変換用の行列算出 start
	//D3DXVECTOR3 camera_pos(0.0f, 0.0f, -10.0f); // カメラ位置
	//D3DXVECTOR3 eye_pos(0.0f, 0.0f, 0.0f);		// 注視点
	//D3DXVECTOR3 up_vector(0.0f, 1.0f, 0.0f);	// カメラの向き

	//D3DXMatrixIdentity(&matView);
	//D3DXMatrixLookAtLH(&matView, 
	//	&camera_pos,				// カメラ座標
	//	&eye_pos,					// 注視点座標
	//	&up_vector);				// カメラの上の向きのベクトル
	//g_pD3DDevice->SetTransform(D3DTS_VIEW, &matView);
	////ビュー座標変換用の行列算出 end

	//射影座標変換用の行列算出 start
	D3DVIEWPORT9 vp;
	g_pD3DDevice->GetViewport(&vp);
	float aspect = (float)vp.Width / (float)vp.Height;

	D3DXMatrixPerspectiveFovLH(
		&matProj,
		D3DXToRadian(60),	// 画角
		aspect,				// アスペクト比
		0.1f,				// near
		500.0f);			// far
	g_pD3DDevice->SetTransform(D3DTS_PROJECTION, &matProj);
	//射影座標変換用の行列算出 end
}


/*
	描画開始
		戻り値：
			なし
		引数：
			なし
		内容：
			描画を始めるための処理を行う
*/
void StartDraw(void)
{
	// 青色でレンダリングターゲットをクリア
	g_pD3DDevice->Clear(0, 
		NULL,
		//クリアするバッファの設定
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		//クリアカラー
		D3DCOLOR_XRGB(0, 0, 255),
		//デプスバッファの初期値
		1.0f,
		//ステンシルバッファの初期値
		0);
	
	g_pD3DDevice->BeginScene();
}

/*
	描画終了
		戻り値：
			なし
		引数：
			なし
		内容：
			描画終了のための処理を行う
*/
void EndDraw(void)
{
	g_pD3DDevice->EndScene();
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

/*
	ライトの設定
		戻り値：
			なし
		引数：
			なし
		内容：
			3D空間で使用するライトの設定を行う
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