#include "Window.h"
#include <tchar.h>

TCHAR pName[100] = _T("�������T���v���v���O����");

// �E�B���h�E�v���V�[�W��
LRESULT CALLBACK WndProc(HWND hWnd, UINT mes, WPARAM wParam, LPARAM lParam) 
{
	if (mes == WM_DESTROY) { PostQuitMessage(0); return 0; }
	return DefWindowProc(hWnd, mes, wParam, lParam);
}

HWND MakeWindow(float width, float height) 
{
	HWND hWnd;
	hWnd = CreateWindow(
		pName,
		pName,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		0,
		width,
		height,
		NULL,
		NULL,
		GetModuleHandle(nullptr),
		NULL
	);

	return hWnd;
}