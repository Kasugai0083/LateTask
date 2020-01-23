#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include "DirectX.h"
#include <vector>

// �ÓI���C�u����
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

extern LPDIRECT3D9 g_pD3DInterface;	// DirectX�C���^�[�t�F�[�X
extern D3DPRESENT_PARAMETERS* g_pD3DPresentParam;
extern LPDIRECT3DDEVICE9 g_pD3DDevice;

LRESULT CALLBACK WindowProc(HWND window_handle, UINT message_id, WPARAM wparam, LPARAM lparam)
{
	switch (message_id)
	{
	case WM_CLOSE:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(window_handle, message_id, wparam, lparam);
		break;
	}

	return 0;
}


int APIENTRY WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR     lpCmpLine,
	INT       nCmdShow)
{
	HWND hWnd;
	WNDCLASSEX window_class = {
		sizeof(WNDCLASSEX),				// �\���̂̃T�C�Y
		CS_HREDRAW | CS_VREDRAW,		// �N���X�̃X�^�C��
		WindowProc,						// �E�B���h�E�v���V�[�W��
		0,								// �⏕������
		0,								// �⏕������
		hInstance,						// ���̃v���O�����̃C���X�^���X�n���h��
		LoadIcon(NULL, MAKEINTRESOURCE(IDI_APPLICATION)),// �A�C�R���摜
		LoadCursor(NULL, IDC_ARROW),	// �J�[�\���摜
		NULL,							// �w�i�u���V(�w�i�F)
		NULL,							// ���j���[��
		TEXT("First3DProgram"),			// �N���X��									
		NULL							// �������A�C�R��
	};

	// �\���̂̓o�^
	if (RegisterClassEx(&window_class) == 0)
	{
		return false;
	}

	// �E�B���h�E�쐬
	hWnd = CreateWindow(
		TEXT("First3DProgram"),
		TEXT("First3DProgram"),
		(WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME) | WS_VISIBLE,
		400,
		10,
		400,
		400,
		NULL,
		NULL,
		hInstance,
		NULL);

	if (hWnd == NULL)
	{
		return false;
	}

	//DirectX�̏�����
	if (InitDirectX(hWnd) == false)
	{
		return false;
	}

	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);

	while (true)
	{
		bool message_ret = false;
		MSG msg;

		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				break;
			}
			else {
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else {

			//���W�ϊ�
			Transform();

			//�`��
			//Draw();

			D3DXVECTOR3 pos1(0.f, 0.f, 0.f);
			D3DXVECTOR3 pos2(3.f, 0.f, 0.f);

			std::vector<Vec3> Lines;

			Vec3 v1(1.f,1.f,0.f);
			Vec3 v2(10.f,1.f,0.f);
			Vec3 v3(10.f,10.f,0.f);
			Vec3 v4(10.f,-10.f,0.f);

			Lines.push_back(v1);
			Lines.push_back(v2);
			//Lines.push_back(v3);
			//Lines.push_back(v4);

			DWORD color = D3DCOLOR_ARGB(255, 255, 255, 255);

			DrawLine(Lines, color);
			//DrawLine(pos1, pos2);

		}
	}
}
