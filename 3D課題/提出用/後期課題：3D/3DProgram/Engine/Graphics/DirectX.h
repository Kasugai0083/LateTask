#ifndef DIRECTX_H_
#define DIRECTX_H_

#include "../../Utility/SingletonTemplate.h"
#include <d3d9.h>
#include <d3dx9.h>
#include <map>
#include <string>

// 静的ライブラリ
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

// 構造体宣言
typedef struct _VERTEX
{
	D3DXVECTOR3 pos;
	D3DCOLOR color;
}VERTEX;

/**
* DirextXステータス構造体
*/
struct DXStatus 
{
	//! DirectXインターフェース
	LPDIRECT3D9 m_D3DInterface;
	//! DirectXの設定
	D3DPRESENT_PARAMETERS* m_pD3DPresentParam;
	//! DirectXデバイス情報
	LPDIRECT3DDEVICE9 m_D3DDevice;
	//! テクスチャリスト
	std::map<std::string, LPDIRECT3DTEXTURE9> m_TextureList;
};

class DXManager : public Singleton<DXManager>
{
public:

	bool InitDirectX(HWND window_handle);

	/**
	* ワールド座標へ変換
	*/
	void Transform();

	void StartDraw();

	void EndDraw();

	/**
	* 光源の設定
	*/
	void SetLighting();

	DXStatus* GetStatus() {
		if (!&m_DXStatus) { return false; }
		return &m_DXStatus;
	}

	// 動かないので保留
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