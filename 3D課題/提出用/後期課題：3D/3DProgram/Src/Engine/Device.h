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

	/**
	* @brief キーボード入力状態を監視
	*/
	void KeyUpdate();

	/**
	* @brief キーボード入力状態を取得
	* @param n_virtKey 入力キーを char (大文字)で指定
	* @return キーボードが入力されている時 => true
	*/
	bool KeyOn(int n_virtKye);

	/**
	* @brief キーボード入力時の状態を取得
	* @param n_virtKey 入力キーを char (大文字)で指定
	* @return キーボードが入力された時 => true
	*/
	bool KeyPress(int n_virtKey);

	/**
	* @brief キーボード入力を話した時の状態を取得
	* @param n_virtKey 入力キーを char (大文字)で指定
	* @return キーボード入力が解除された時 => true
	*/
	bool KeyOff(int n_VirtKey);

	/**
	* @brief 現在のマウス座標を取得？
	* @return マウスの X座標 と Y座標 を返す
	*/
	Vec2 GetMousePoint();

	/**
	* @brief クリック中のマウス座標を取得？
	* @return マウスの X座標 と Y座標 を返す
	*/
	Vec2 GetPointOnDrag();

	/**
	* @brief マウスがクリックされたかどうかを判定
	* @return マウスがクリックされた場合 => true
	*/
	const bool HasClickOnMouse();
}
