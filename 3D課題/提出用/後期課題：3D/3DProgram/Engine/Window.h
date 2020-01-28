#pragma once

#include <windows.h>

namespace Window{
	
	// ウィンドウを作成する
	bool MakeWindow(float x_, float y_, char* name_);

	// メッセージ処理
	bool ProcessMessage();
}
