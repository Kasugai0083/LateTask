#pragma once

#include <windows.h>

/**
* @brief ウィンドウを制御する関数群
*/

namespace Window{
	
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
}
