#include "Window.h"
#include "Graphics/DirectX.h"

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

bool MakeWindow() {

	DXManager* Ins_DXManager = DXManager::GetInstance();

	HWND hWnd;
	WNDCLASSEX window_class = {
		sizeof(WNDCLASSEX),									// �\���̂̃T�C�Y
		CS_HREDRAW | CS_VREDRAW,							// �N���X�̃X�^�C��
		WindowProc,											// �E�B���h�E�v���V�[�W��
		0,													// �⏕������
		0,													// �⏕������
		GetModuleHandle(nullptr),							// ���̃v���O�����̃C���X�^���X�n���h��
		LoadIcon(NULL, MAKEINTRESOURCE(IDI_APPLICATION)),	// �A�C�R���摜
		LoadCursor(NULL, IDC_ARROW),						// �J�[�\���摜
		NULL,												// �w�i�u���V(�w�i�F)
		NULL,												// ���j���[��
		TEXT("First3DProgram"),								// �N���X��									
		NULL												// �������A�C�R��
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
		GetModuleHandle(nullptr),
		NULL);

	if (hWnd == NULL)
	{
		return false;
	}

	if (!Ins_DXManager->InitDirectX(hWnd))
	{
		return false;
	}

	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);

	return true;
}