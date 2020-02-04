#ifndef DIRECTX_H_
#define DIRECTX_H_

#include "../../Utility/SingletonTemplate.h"
#include <d3d9.h>
#include <d3dx9.h>
#include <map>
#include <string>

/**
* @brief 
* DirectXを初期化・管理するクラス
*/

/**
* @brief DirextXステータス構造体\n
* 受け渡しを簡略化するために構造体に纏める
*/
struct DXStatus 
{
	LPDIRECT3D9 m_D3DInterface;	//!< @brief DirectXインターフェース
	
	D3DPRESENT_PARAMETERS* m_pD3DPresentParam; //!< @brief DirectXの設定
	
	LPDIRECT3DDEVICE9 m_D3DDevice; //!< @brief DirectXデバイス情報
	
	std::map<std::string, LPDIRECT3DTEXTURE9> m_TextureList; //!< @brief テクスチャリスト
};

class DXManager : public Singleton<DXManager>
{
public:

	/**
	* @brief DirectX を初期化
	* @param ウィンドウハンドル
	* @return 初期化に成功した場合 => true
	*/
	bool InitDirectX(HWND window_handle);

	/**
	* @brief カメラ情報を初期化
	*/
	void Transform();

	/**
	* @brief DirectXでの描画情報を初期化
	*/
	void StartDraw();

	/**
	* @brief DirectXでの描画情報を解放
	*/
	void EndDraw();

	/**
	* @brief 光源の設定
	*/
	void SetLighting();

	/**
	* @return DirectX 構造体のアドレスを返す
	*/
	DXStatus* GetStatus() {
		if (!&m_DXStatus) { return false; }
		return &m_DXStatus;
	}

	/**
	* @return MatView のアドレスを返す
	*/
	D3DXMATRIX* GetViewMatrix() {
		if (!&m_MatView) { return false; }
		return &m_MatView;
	}

protected:

	DXStatus m_DXStatus; //!< @brief DirectX の周辺情報を保管

	D3DXMATRIX m_MatProj, m_MatView; //!> @brief 視点情報行列

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