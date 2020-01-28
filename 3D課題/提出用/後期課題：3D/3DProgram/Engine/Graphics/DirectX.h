#ifndef DIRECTX_H_
#define DIRECTX_H_

#include "../../Utility/SingletonTemplate.h"
#include <d3d9.h>
#include <d3dx9.h>
#include <map>
#include <string>

// �ÓI���C�u����
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

// �\���̐錾
typedef struct _VERTEX
{
	D3DXVECTOR3 pos;
	D3DCOLOR color;
}VERTEX;

/**
* DirextX�X�e�[�^�X�\����
*/
struct DXStatus 
{
	//! DirectX�C���^�[�t�F�[�X
	LPDIRECT3D9 m_D3DInterface;
	//! DirectX�̐ݒ�
	D3DPRESENT_PARAMETERS* m_pD3DPresentParam;
	//! DirectX�f�o�C�X���
	LPDIRECT3DDEVICE9 m_D3DDevice;
	//! �e�N�X�`�����X�g
	std::map<std::string, LPDIRECT3DTEXTURE9> m_TextureList;
};

class DXManager : public Singleton<DXManager>
{
public:

	bool InitDirectX(HWND window_handle);

	/**
	* ���[���h���W�֕ϊ�
	*/
	void Transform();

	void StartDraw();

	void EndDraw();

	/**
	* �����̐ݒ�
	*/
	void SetLighting();

	DXStatus* GetStatus() {
		if (!&m_DXStatus) { return false; }
		return &m_DXStatus;
	}

	// �����Ȃ��̂ŕۗ�
	//DXStatus GetStatus() {
	//	if (!m_DXStatus.m_D3DDevice 
	//		|| !m_DXStatus.m_D3DInterface 
	//		|| !m_DXStatus.m_pD3DPresentParam 
	//		|| !m_DXStatus.m_TextureList.begin) 
	//	{
	//		return;
	//	}
	//	return m_DXStatus;
	//}

protected:

	DXStatus m_DXStatus;

private:
	friend Singleton<DXManager>;

	DXManager() {};
	virtual ~DXManager() {};

	DXManager(const DXManager&) = delete;
	DXManager& operator=(const DXManager&) = delete;
	DXManager(const DXManager&&) = delete;
	DXManager& operator=(const DXManager&&) = delete;
};



#endif