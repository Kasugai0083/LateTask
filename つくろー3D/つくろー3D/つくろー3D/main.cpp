/// 3Dオブジェクト描画サンプルプログラム

#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

#include <windows.h>
#include <tchar.h>
#include <d3d9.h>
#include <d3dx9.h>

_TCHAR gName[100] = _T("3Dオブジェクト描画サンプルプログラム");


// ウィンドウプロシージャ
LRESULT CALLBACK WndProc(HWND hWnd, UINT mes, WPARAM wParam, LPARAM lParam) {
	if (mes == WM_DESTROY) { PostQuitMessage(0); return 0; }
	return DefWindowProc(hWnd, mes, wParam, lParam);
}


int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	// アプリケーションの初期化
	MSG msg; HWND hWnd;
	WNDCLASSEX wcex = { sizeof(WNDCLASSEX), CS_HREDRAW | CS_VREDRAW, WndProc, 0, 0, hInstance, NULL, NULL,
									 (HBRUSH)(COLOR_WINDOW + 1), NULL, (_TCHAR*)gName, NULL };
	if (!RegisterClassEx(&wcex))
		return 0;

	if (!(hWnd = CreateWindow(gName, gName, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0, CW_USEDEFAULT, 0,
		NULL, NULL, hInstance, NULL)))
		return 0;

	// Direct3Dの初期化
	LPDIRECT3D9 g_pD3D;
	LPDIRECT3DDEVICE9 g_pD3DDev;
	if (!(g_pD3D = Direct3DCreate9(D3D_SDK_VERSION))) return 0;

	D3DPRESENT_PARAMETERS d3dpp = { 0,0,D3DFMT_UNKNOWN,0,D3DMULTISAMPLE_NONE,0,
													   D3DSWAPEFFECT_DISCARD,NULL,TRUE,TRUE,D3DFMT_D24S8,0,D3DPRESENT_RATE_DEFAULT,D3DPRESENT_INTERVAL_DEFAULT };

	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &g_pD3DDev)))
		if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &g_pD3DDev)))
		{
			g_pD3D->Release();
			return 0;
		}

	// 立方体オブジェクト生成
	ID3DXBuffer* pMaterials;
	DWORD NumMaterials;
	ID3DXMesh* pMesh;
	if (FAILED(D3DXLoadMeshFromX(_T("Cube2.x"), D3DXMESH_MANAGED, g_pD3DDev, NULL, &pMaterials, NULL, &NumMaterials, &pMesh))) {
		g_pD3DDev->Release(); g_pD3D->Release(); return 0;
	}

	// 軸オブジェクト生成
	ID3DXBuffer* pAX_Materials;
	DWORD AX_NumMaterials;
	ID3DXMesh* pAX_Mesh;
	if (FAILED(D3DXLoadMeshFromX(_T("Axis.x"), D3DXMESH_MANAGED, g_pD3DDev, NULL, &pAX_Materials, NULL, &AX_NumMaterials, &pAX_Mesh))) {
		pMesh->Release(); g_pD3DDev->Release(); g_pD3D->Release(); return 0;
	}

	// ライト
	D3DLIGHT9 light;
	ZeroMemory(&light, sizeof(D3DLIGHT9));
	light.Direction = D3DXVECTOR3(-1, -20, 0);
	light.Type = D3DLIGHT_DIRECTIONAL;
	light.Diffuse.r = 1.0f;
	light.Diffuse.g = 1.0f;
	light.Diffuse.b = 1.0f;
	light.Ambient.r = 0.5f;
	light.Ambient.g = 0.5f;
	light.Ambient.b = 0.5f;
	light.Range = 1000;

	g_pD3DDev->SetLight(0, &light);
	g_pD3DDev->LightEnable(0, true);
	g_pD3DDev->SetRenderState(D3DRS_LIGHTING, TRUE);
	g_pD3DDev->SetRenderState(D3DRS_AMBIENT, 0x00808080);   // アンビエントライト

	// ウィンドウ表示
	ShowWindow(hWnd, SW_SHOW);


	////////////////////////////
	// メッセージループ
	/////
	D3DXMATRIX World;          // 立方体ワールド変換行列
	D3DXMATRIX Rot_X, Rot_Y;   // 立方体回転行列
	D3DXMATRIX Offset;         // 立方体オフセット行列
	D3DXMATRIX AXWorld;   // 軸ワールド変換行列
	D3DXMatrixIdentity(&AXWorld);   // 軸は原点に位置するので単位行列
	D3DXMATRIX View;   // ビュー変換行列
	D3DXMATRIX Persp;   // 射影変換行列
	D3DCOLORVALUE MAmbient = { 0.2f, 0.2f, 0.2f, 1.0f };   // マテリアルのアンビエント反射率

	FLOAT Ang = 0.0f;   // 回転角度
	unsigned int i;
	do {
		Sleep(1);
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) { DispatchMessage(&msg); }
		g_pD3DDev->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(40, 40, 80), 1.0f, 0);
		g_pD3DDev->BeginScene();

		Ang += 1;

		///////////////////////////
		// ライト
		////////
			// ライトの方向回転
		light.Direction.x = 20 * sin(D3DXToRadian(Ang));
		light.Direction.z = 20 * cos(D3DXToRadian(Ang));
		g_pD3DDev->SetLight(0, &light);

		///////////////////////////
		// 立方体
		////////
		D3DXMatrixRotationX(&Rot_X, D3DXToRadian(Ang * 0.15f));
		D3DXMatrixRotationY(&Rot_Y, D3DXToRadian(Ang * 0.2f) + 70.0f);
		D3DXMatrixTranslation(&Offset, 10, 10, 10);

		D3DXMatrixIdentity(&World);          // 単位行列化
		D3DXMatrixMultiply(&World, &World, &Offset);   // まずオフセットして、
		D3DXMatrixMultiply(&World, &World, &Rot_X);    // X軸回転後
		D3DXMatrixMultiply(&World, &World, &Rot_Y);    // Y軸回転させます。

	// ビュー変換
		// 視点は原点固定ですが、カメラの位置は適当です
		D3DXMatrixLookAtLH(
			&View,
			&D3DXVECTOR3(47.5f * cos(D3DXToRadian(Ang * 0.7f)), 70.2f * cos(D3DXToRadian(Ang * 0.2f)), 56.7f * sin(D3DXToRadian(Ang * 1.2f))),
			&D3DXVECTOR3(0, 0, 0),
			&D3DXVECTOR3(sin(D3DXToRadian(Ang * 0.4f)), 1, 0)
		);

		// 射影変換
		D3DXMatrixPerspectiveFovLH(&Persp, D3DXToRadian(45), 640.0f / 480.0f, 1.0f, 10000.0f);

		// 行列登録
		g_pD3DDev->SetTransform(D3DTS_WORLD, &World);
		g_pD3DDev->SetTransform(D3DTS_VIEW, &View);
		g_pD3DDev->SetTransform(D3DTS_PROJECTION, &Persp);

		// 立方体描画
		for (i = 0; i < NumMaterials; i++) {
			D3DXMATERIAL* mtrl = (D3DXMATERIAL*)(pMaterials->GetBufferPointer());
			mtrl->MatD3D.Ambient = MAmbient;
			g_pD3DDev->SetMaterial(&mtrl->MatD3D);
			pMesh->DrawSubset(i);
		};

		///////////////////////////
		// 軸
		////////
		// ワールド変換（単位行列のみ）
		g_pD3DDev->SetTransform(D3DTS_WORLD, &AXWorld);

		for (i = 0; i < AX_NumMaterials; i++) {      // 軸描画
			D3DXMATERIAL* mtrl = ((D3DXMATERIAL*)(pAX_Materials->GetBufferPointer()) + i);
			mtrl->MatD3D.Ambient = MAmbient;
			g_pD3DDev->SetMaterial(&mtrl->MatD3D);
			pAX_Mesh->DrawSubset(i);
		};

		g_pD3DDev->EndScene();
		g_pD3DDev->Present(NULL, NULL, NULL, NULL);
	} while (msg.message != WM_QUIT);

	pMesh->Release();
	pAX_Mesh->Release();
	g_pD3DDev->Release();
	g_pD3D->Release();

	return 0;
}
