#pragma once

#include <windows.h>

/**
* @brief �E�B���h�E�𐧌䂷��֐��Q
*/

namespace Window{
	
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
}
