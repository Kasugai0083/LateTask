#ifndef DIRECTX_H_
#define DIRECTX_H_

#include <d3d9.h>
#include <d3dx9.h>

// 静的ライブラリ
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

// 構造体宣言
typedef struct _VERTEX
{
	D3DXVECTOR3 pos;
	D3DCOLOR color;
}VERTEX;

bool InitDirectX(HWND window_handle);
bool LoadXFile();
void Transform(void);
void StartDraw(void);
void EndDraw(void);
void SetLighting(void);

#endif