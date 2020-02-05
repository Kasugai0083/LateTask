#pragma once

#include "..//Utility/Vec2.h"
#include <windows.h>

/**
* @brief �E�B���h�E�ƃ}�E�X���䂷��֐��Q
*/

namespace Device{
	
	/**
	* @brief �E�B���h�E���쐬����
	* @param x_ X���̃T�C�Y
	* @param y_ Y���̃T�C�Y
	* @param name_ �E�B���h�E�̃N���X��
	*/
	bool MakeWindow(float x_, float y_, char* name_);

	/**
	* @brief ���b�Z�[�W����
	*/ 
	bool ProcessMessage();

	void KeyUpdate();

	bool KeyOn(int n_virtKye);

	bool KeyPress(int n_virtKey);

	bool KeyOff(int n_VirtKey);

	Vec2 GetMousePoint();

	const bool HasClickOnMouse();
}
