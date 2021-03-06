#include "XFile.h"
#include <map>

extern std::map<std::string, LPDIRECT3DTEXTURE9> g_TextureList;
extern LPDIRECT3DDEVICE9 g_pD3DDevice;
std::map<std::string, XFile *>g_pXFileList;	// 読み込んだXFileのリスト

/*
	XFile読み込み
		戻り値：
			読み込み結果：
				成功：
					true
				失敗：
					false
		引数：
			std::string file_name：
				ファイル名
		内容：
			XFileの読み込みを行う
*/
bool XFile::Load(std::string file_name)
{
	// XFileデータを格納する仮バッファ
	LPD3DXBUFFER p_material_buffer = NULL;

	// �@．XFileの読み込み start
	if (FAILED(D3DXLoadMeshFromXA(
		file_name.c_str(),
		D3DXMESH_SYSTEMMEM,
		g_pD3DDevice,
		NULL,
		&p_material_buffer,
		NULL,
		&m_MaterialNum,
		&m_pMesh) ) )
	{
		return false;
	}
	// �@．XFileの読み込み end

	// �A.マテリアル情報のコピー start
	// 読み込まれたXFileのマテリアル分のD3DMATERIAL9を用意する
	m_pMeshMaterialList = new D3DMATERIAL9[m_MaterialNum];

	// メッシュに使用されているテクスチャ用の配列を用意する
	m_pTextureList = new LPDIRECT3DTEXTURE9[m_MaterialNum];

	// バッファの先頭ポインタをD3DXMATERIALにキャストして取得
	D3DXMATERIAL *pmat_list = (D3DXMATERIAL*)p_material_buffer->GetBufferPointer();

	// 各メッシュのマテリアル情報を取得する
	for (DWORD i = 0; i < m_MaterialNum; i++)
	{
		// マテリアル取得
		m_pMeshMaterialList[i] = pmat_list[i].MatD3D;
		m_pTextureList[i] = NULL;

		// マテリアルで設定されているテクスチャ読み込み
		if (pmat_list[i].pTextureFilename != NULL)
		{
			std::string file_name = pmat_list[i].pTextureFilename;
			LPDIRECT3DTEXTURE9 texture = NULL;
			if (g_TextureList[file_name] == NULL)
			{
				D3DXCreateTextureFromFileA(g_pD3DDevice,
											file_name.c_str(),
											&g_TextureList[file_name]);
			}

			m_pTextureList[i] = g_TextureList[file_name];
			m_TextureNameList[i] = file_name;
		}
	}

	// マテリアルのコピーが終わったのでバッファを解放する
	p_material_buffer->Release();
	// �A.マテリアル情報のコピー end

	return true;
}

XFile::~XFile(void)
{
	// マテリアルリストの解放
	if (m_pMeshMaterialList != NULL)
	{
		delete[] (m_pMeshMaterialList);
		m_pMeshMaterialList = NULL;
	}

	// テクスチャリストの解放
	if (m_pTextureList != NULL)
	{
		for (int i = 0; i < m_MaterialNum; i++)
		{
			if (m_pTextureList[i] != NULL &&
				g_TextureList[m_TextureNameList[i]] != NULL)
			{
				// テクスチャの解放
				g_TextureList[m_TextureNameList[i]]->Release();
				m_pTextureList[i] = NULL;
			}
		}

		delete[] (m_pTextureList);
		m_pTextureList = NULL;
	}

	// テクスチャファイル名リストの初期化
	m_TextureNameList.clear();
}

void XFile::Draw(void)
{
	for (DWORD i = 0; i < m_MaterialNum; i++)
	{
		// マテリアルの設定
		g_pD3DDevice->SetMaterial(&m_pMeshMaterialList[i]);
		// テクスチャの設定
		g_pD3DDevice->SetTexture(0, m_pTextureList[i]);
		// メッシュを描画
		m_pMesh->DrawSubset(i);
	}
}
