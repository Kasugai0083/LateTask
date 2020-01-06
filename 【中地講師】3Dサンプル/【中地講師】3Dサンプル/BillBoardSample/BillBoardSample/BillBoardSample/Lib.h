#ifndef DIRECTX_LIB_H_
#define DIRECTX_LIB_H_

#include "Window.h"
#include "DirectGraphics.h"
#include "DirectInput.h"

/*
	DirectXの初期化
		戻り値：
			初期化成功：
				true
			初期化失敗：
				false
		
		引数：
			HWND window_handle：
				DirectGraphicsで描画する対象となるウィンドウのハンドル

		内容：
			DirectXの初期化を行う
			必ずゲームループの前に1度だけ実行すること
			※現状はDirectGraphics、DirectInputの初期化をしてる
*/
bool InitDirectX(HINSTANCE instance_handle, HWND window_handle);

/*
	DirectXの終了
		戻り値：
			なし

		引数：
			なし

		内容：
			DirectXを終了する
			ゲームループ終了後に1度だけ実行すること
*/
void EndDirectX();

#endif
