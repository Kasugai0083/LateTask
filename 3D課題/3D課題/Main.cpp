#include <Windows.h>

enum class WINDOW_MODE {
	WINDOWED,
	FULL_SCLEEN
};


int WinMain(HINSTANCE hInstancec,
	HINSTANCE PrevInstance,
	LPSTR lpCmpLine,
	INT nCmdShow) 
{
	if (InitEngine(1920, 1080, "3D‰Û‘è", WINDOW_MODE::WINDOWED) == false)
	{
		return 0;
	}

	while (true) {
		bool mssage_ret = false;
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
		}else
		{
			UpdateScene();
		}
		EndEngine();
	}
	return 0;
}