#include "Lib.h"
#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>

bool InitDirectX(HINSTANCE instance_handle, HWND window_handle)
{
	if (InitDirectGraphics(window_handle) == false)
	{
		return false;
	}

	if (InitDirectInput(instance_handle, window_handle) == false)
	{
		ReleaseDirectGraphics();
		return false;
	}

	return true;
}

void EndDirectX()
{
	ReleaseDirectInput();
	ReleaseDirectGraphics();
}
