#ifndef WINDOW_H_
#define WINDOW_H_

#include <Windows.h>

/*
	ウィンドウ作成
		戻り値：
			作成成功：
				非0
			作成失敗：
				-1

		引数：
			HINSTANCE instance
				ウィンドウを作成するアプリのインスタンスハンドル

			int width
				横のサイズ

			int height
				縦のサイズ

		内容：
			引数で指定したサイズでウィンドウを作成する
			成功したらWindowハンドルが返り、失敗したら-1が返る
*/
HWND MakeWindow(HINSTANCE instance, int width, int height);

#endif
