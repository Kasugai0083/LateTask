#pragma once

#include "..//Utility/Vec2.h"
#include <windows.h>

/**
* @brief ウィンドウとマウス制御する関数群
*/

namespace Device{
	
	/**
	* @brief ウィンドウを作成する
	* @param x_ X軸のサイズ
	* @param y_ Y軸のサイズ
	* @param name_ ウィンドウのクラス名
	*/
	bool MakeWindow(float x_, float y_, char* name_);

	/**
	* @brief メッセージ処理
	*/ 
	bool ProcessMessage();

	void KeyUpdate();

	bool KeyOn(int n_virtKye);

	bool KeyPress(int n_virtKey);

	bool KeyOff(int n_VirtKey);

	Vec2 GetMousePoint();

	const bool HasClickOnMouse();
}
