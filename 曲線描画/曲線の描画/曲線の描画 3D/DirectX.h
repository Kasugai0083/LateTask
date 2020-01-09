#ifndef DIRECTX_H_
#define DIRECTX_H_

#include <d3d9.h>
#include <d3dx9.h>
#include <vector>

// 静的ライブラリ
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

typedef struct Vector {

	Vector() {
		x = 0.f;
		y = 0.f;
		z = 0.f;
	};

	Vector(float x_, float y_, float z_) {
		x = x_;
		y = y_;
		z = z_;
	};

	float x, y, z;
}Vec3;


// 構造体宣言
typedef struct _VERTEX
{
	D3DXVECTOR3 pos;
	D3DCOLOR color;
}VERTEX;

bool InitDirectX(HWND window_handle);
void Transform(void);
void Draw(void);

void DrawLine(D3DXVECTOR3 start_, D3DXVECTOR3 end_);
void DrawLine(Vec3 start_, Vec3 end_, DWORD color_);
void DrawLine(std::vector<Vec3>& line_, DWORD color_);


#endif