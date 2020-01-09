#include <windows.h>
#include <map>
#include "DirectX.h"
#include "XFile.h"
#include "Obj.h"
#include "Camera.h"

extern LPDIRECT3D9 g_pD3DInterface;	// DirectX�C���^�[�t�F�[�X
extern D3DPRESENT_PARAMETERS *g_pD3DPresentParam;
extern LPDIRECT3DDEVICE9 g_pD3DDevice;
extern std::map<std::string, XFile *>g_pXFileList;

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
		TEXT("CameraSample"),				// �N���X��									
		NULL							// �������A�C�R��
	};

	// �\���̂̓o�^
	if (RegisterClassEx(&window_class) == 0)
	{
		return false;
	}

	// �E�B���h�E�쐬
	hWnd = CreateWindow(
		TEXT("CameraSample"),
		TEXT("CameraSample"),
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

	if (InitDirectX(hWnd) == false)
	{
		return false;
	}

	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);

	// �ǂݍ��݃t�@�C�������X�g
	std::string file_name_list[] =
	{
		"Res/Sample01.x",
		"Res/Sample02.x",
	};

	// XFile�ǂݍ���
	for (int i = 0; i <2; i++)
	{
		g_pXFileList[file_name_list[i]] = new XFile();
		g_pXFileList[file_name_list[i]]->Load(file_name_list[i]);
	}

	// XFile�I�u�W�F�N�g�쐬
	Obj obj1(
		D3DXVECTOR3(0.0f, 0.0f, 4.0f),
		D3DXVECTOR3(1.0f, 1.0f, 1.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		g_pXFileList["Res/Sample01.x"]);

	Obj obj2(
		D3DXVECTOR3(3.0f, 0.0f, 3.0f),
		D3DXVECTOR3(0.01f, 0.01f, 0.01f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		g_pXFileList["Res/Sample02.x"]);

	SetCameraTarget(&obj1);

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
			else 
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		} 
		else
		{
			obj1.Update();
			obj2.Update();

			UpdateCamera();

			// �`��J�n
			StartDraw();

			// ���W�ϊ�		
			Transform();

			// ���C�e�B���O�ݒ�
			SetLighting();

			// �I�u�W�F�N�g�`��
			obj1.Draw();
			obj2.Draw();
			
			// �`��I��
			EndDraw();
		}
	}

	for (int i = 0; i < 2; i++)
	{
		delete(g_pXFileList[file_name_list[i]]);
	}
	return 0;
}

