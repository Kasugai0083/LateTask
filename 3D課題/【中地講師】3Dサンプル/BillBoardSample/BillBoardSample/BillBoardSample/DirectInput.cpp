#include "DirectInput.h"
#include <Windows.h>
#include <dinput.h>
#include <d3d9.h>
#include <d3dx9.h>

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

// �L�[���\����
struct INPUTSTATE
{
	DWORD now;
	DWORD trg;
	DWORD ntrg;
};

// DIRECTINPUT8�̃|�C���^
static LPDIRECTINPUT8 g_pInputInterface;

// DIRECTINPUTDEVICE8�̃|�C���^
static LPDIRECTINPUTDEVICE8 g_pKeyDevice;

// �L�[���
static INPUTSTATE g_InputState;

bool InitDirectInput(HINSTANCE instance_handle, HWND window_handle)
{
	// IDirectInput8�C���^�[�t�F�C�X�̎擾
	HRESULT hr = DirectInput8Create(instance_handle, 
									DIRECTINPUT_VERSION,
									IID_IDirectInput8,
									(void**)&g_pInputInterface,
									NULL);
	if (FAILED(hr))
	{
		MessageBox(window_handle, (char*)"error", (char*)"�G���[A", MB_OK);
		return false;
	}

	// IDirectInputDevice8�C���^�[�t�F�C�X�̎擾
	hr = g_pInputInterface->CreateDevice(GUID_SysKeyboard, &g_pKeyDevice, NULL);
	if (FAILED(hr))
	{
		MessageBox(window_handle, (char*)"error", (char*)"�G���[B", MB_OK);
		return false;
	}
	
	// �f�o�C�X�̃t�H�[�}�b�g�̐ݒ�
	hr = g_pKeyDevice->SetDataFormat(&c_dfDIKeyboard);
	if (FAILED(hr))
	{
		MessageBox(window_handle, (char*)"error", (char*)"�G���[C", MB_OK);
		return false;
	}
	
	// �������[�h�̐ݒ�
	hr = g_pKeyDevice->SetCooperativeLevel(window_handle, DISCL_BACKGROUND | DISCL_NONEXCLUSIVE);
	if (FAILED(hr))
	{
		MessageBox(window_handle, (char*)"error", (char*)"�G���[D", MB_OK);
		return false;
	}

	// �f�o�C�X�̎擾�J�n
	g_pKeyDevice->Acquire();

	return true;
}

void ReleaseDirectInput()
{
	g_pKeyDevice->Unacquire();
	g_pKeyDevice->Release();
	g_pInputInterface->Release();
}

void KeyUpDate()
{
	// �L�[����i�[�p
	BYTE KeyState[256];
	HRESULT hr;

	// �L�[�{�[�h�f�o�C�X�̃Q�b�^�[
	hr = g_pKeyDevice->GetDeviceState(256, KeyState);
	if (SUCCEEDED(hr))
	{	
		// 1�t���[���O�̃L�[���̊m��
		DWORD old = g_InputState.now;	

		// �L�[���N���A
		g_InputState.now = CLEAR_KEY;	

		// ��L�[
		if (KeyState[DIK_UP] & 0x80)
		{
			g_InputState.now |= KEY_CODE_UP; 
		}

		// ���L�[
		if (KeyState[DIK_DOWN] & 0x80)
		{
			g_InputState.now |= KEY_CODE_DOWN; 
		}

		// ���L�[
		if (KeyState[DIK_LEFT] & 0x80)
		{
			g_InputState.now |= KEY_CODE_LEFT; 
		}

		// �E�L�[
		if (KeyState[DIK_RIGHT] & 0x80)
		{
			g_InputState.now |= KEY_CODE_RIGHT; 
		}

		g_InputState.trg = (g_InputState.now & (~old));	// �g���K�[���擾
		g_InputState.ntrg = (~g_InputState.now) & old;	// �t�g���K�[���擾

	} else if (hr == DIERR_INPUTLOST) {
		g_pKeyDevice->Acquire();
	}
}

bool GetKey(DWORD key_code)
{
	return g_InputState.now & key_code;
}

bool GetKeyDown(DWORD key_code)
{
	return g_InputState.trg & key_code;
}

bool GetKeyUp(DWORD key_code)
{
	return g_InputState.ntrg & key_code;
}
