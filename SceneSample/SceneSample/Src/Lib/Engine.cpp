#include "Window.h"
#include "Graphics.h"
#include "Input.h"
#include "Engine.h"

namespace Engine {

	bool InitEngine(int width_, int height_, const char* titleName_, bool isFull_)
	{
		if (MakeWindow(width_, height_, titleName_) == false)
		{
			return false;
		}

		if (Graphic::InitGraphics(isFull_) == false)
		{
			return false;
		}

		if (InitInput() == false)
		{
			return false;
		}

		return true;
	}

	void EndEngine()
	{

		Graphic::EndGraphics();
		EndInput();
	}
};