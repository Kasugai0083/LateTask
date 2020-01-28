#include <time.h>
#include <window.h>
#include "Lib.h"
#include "BillBoard.h"
#include "Camera.h"

int APIENTRY WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR     lpCmpLine,
	INT       nCmdShow)
{
	srand((unsigned)time(NULL));

	// �E�B���h�E�쐬
	HWND window_handle = MakeWindow(hInstance, 800, 600);

	if (window_handle == 0)
	{
		return 0;
	}

	// DirectX������
	if (InitDirectX(hInstance, window_handle) == false)
	{
		return 0;
	}

	InitBillBoard();
	CameraInit(GetBillBoardPosPointer());

	while (true)
	{
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
			// �L�[���̍X�V
			KeyUpDate();

			CameraUpdate();

			Transform(GetCameraPos(), GetEyePos());

			DrawStart();

			DrawBillBoard();
			DrawNotBillBoard();

			DrawEnd();
		}

	}

	ReleaseBillBoard();

	// DirectX�I��
	EndDirectX();
}
