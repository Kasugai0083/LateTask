#include "Lib.h"
#include "BillBoard.h"

extern int g_TextureList[];

static D3DXVECTOR3 g_BillBoardPos;		// 座標
static int g_BillBoardTextureId = 0;	// テクスチャ番号
static D3DXVECTOR2 g_TexturePos;		// テクスチャ座標
static D3DXVECTOR2 g_TextureSize;		// テクスチャサイズ

const D3DXVECTOR3 *GetBillBoardPosPointer()
{
	return &g_BillBoardPos;
}

void InitBillBoard()
{
	g_BillBoardTextureId = LoadTexture("sample.png");
	g_BillBoardPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_TexturePos = D3DXVECTOR2(0.0f, 0.0f);
	g_TextureSize = D3DXVECTOR2(128.0f, 128.0f);
}

void ReleaseBillBoard()
{
	ReleaseTexture(g_BillBoardTextureId);
}

void DrawBillBoard()
{
	D3DXMATRIX view_mat, world, trans;

	D3DXMatrixIdentity(&world);
	D3DXMatrixIdentity(&trans);
	D3DXMatrixIdentity(&view_mat);
	
	// ②．オブジェクトの行列を作成する
	// 移動
	D3DXMatrixTranslation(&trans, g_BillBoardPos.x, g_BillBoardPos.y, g_BillBoardPos.z);

	// ③．カメラのビュー行列の逆行列を作成する
	// ビューマトリックスの逆行列作成
	InverseViewMatrix(&view_mat);

	// ④．逆行列の移動値を打ち消す
	// 移動情報の打ち消し
	view_mat._41 = 0.0f;
	view_mat._42 = 0.0f;
	view_mat._43 = 0.0f;

	// ⑤．行列を掛け合わせる
	// ワールド座標作成
	world = view_mat * trans;

	// ⑥．行列の設定
	// ワールド座標の設定
	GetD3DDevice()->SetTransform(D3DTS_WORLD, &world);

	// 以下板ポリの描画
	float left_tu = 0.0f;
	float right_tu = 1.0f;
	float top_tv = 0.0f;
	float bottom_tv = 1.0f;
	const TEXTURE_DATA *texture_data = GetTextureData(g_BillBoardTextureId);

	if (texture_data->m_pTexture != NULL)
	{
		left_tu = g_TexturePos.x / texture_data->m_Width;
		right_tu = (g_TexturePos.x + g_TextureSize.x) / texture_data->m_Width;
		top_tv = g_TexturePos.y / texture_data->m_Height;
		bottom_tv = (g_TexturePos.y + g_TextureSize.y) / texture_data->m_Height;
	}

	float harf_x = texture_data->m_Width / 2.0f;
	float harf_y = texture_data->m_Height / 2.0f;

	// 三角形を描画
	VERTEX v[4] = 
	{
		{ D3DXVECTOR3(-harf_x, harf_y, 0.0f), D3DXVECTOR2(left_tu, top_tv) },
		{ D3DXVECTOR3(harf_x, harf_y, 0.0f), D3DXVECTOR2(right_tu, top_tv) },
		{ D3DXVECTOR3(harf_x, -harf_y, 0.0f), D3DXVECTOR2(right_tu, bottom_tv) },
		{ D3DXVECTOR3(-harf_x, -harf_y, 0.0f), D3DXVECTOR2(left_tu, bottom_tv) },
	};

	// 法線を設定していないのでライティングはなし
	GetD3DDevice()->SetRenderState( D3DRS_LIGHTING, FALSE );	// RHWで無い頂点はLIGHTが効くので無効にしておく
	GetD3DDevice()->SetRenderState( D3DRS_CULLMODE, D3DCULL_CCW );	

	// ⑦．板ポリ描画
	// 頂点構造の指定
	GetD3DDevice()->SetFVF(D3DFVF_XYZ | D3DFVF_TEX1);
	GetD3DDevice()->SetTexture(0, texture_data->m_pTexture);
	GetD3DDevice()->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, v, sizeof(VERTEX));

}

// 比較用
void DrawNotBillBoard()
{
	D3DXMATRIXA16 world, trans;

	D3DXMatrixIdentity(&world);
	D3DXMatrixIdentity(&trans);
	
	// 移動
	D3DXMatrixTranslation(&trans, g_BillBoardPos.x, g_BillBoardPos.y + 150.0f, g_BillBoardPos.z);
	world = trans;

	GetD3DDevice()->SetTransform(D3DTS_WORLD, &world);

	/////////////////////////////////////////////////////
	float left_tu = 0.0f;
	float right_tu = 1.0f;
	float top_tv = 0.0f;
	float bottom_tv = 1.0f;
	const TEXTURE_DATA *texture_data = GetTextureData(g_BillBoardTextureId);

	if (texture_data->m_pTexture != NULL)
	{
		left_tu = g_TexturePos.x / texture_data->m_Width;
		right_tu = (g_TexturePos.x + g_TextureSize.x) / texture_data->m_Width;
		top_tv = g_TexturePos.y / texture_data->m_Height;
		bottom_tv = (g_TexturePos.y + g_TextureSize.y) / texture_data->m_Height;
	}

	float harf_x = texture_data->m_Width / 2.0f;
	float harf_y = texture_data->m_Height / 2.0f;

	// 三角形を描画 start
	VERTEX v[4] = 
	{
		{ D3DXVECTOR3(-harf_x, harf_y, 0.0f), D3DXVECTOR2(left_tu, top_tv) },
		{ D3DXVECTOR3(harf_x, harf_y, 0.0f), D3DXVECTOR2(right_tu, top_tv) },
		{ D3DXVECTOR3(harf_x, -harf_y, 0.0f), D3DXVECTOR2(right_tu, bottom_tv) },
		{ D3DXVECTOR3(-harf_x, -harf_y, 0.0f), D3DXVECTOR2(left_tu, bottom_tv) },
	};

	GetD3DDevice()->SetRenderState( D3DRS_LIGHTING, FALSE ); // RHWで無い頂点はLIGHTが効くので無効にしておく

	// 頂点構造の指定
	GetD3DDevice()->SetFVF(D3DFVF_XYZ | D3DFVF_TEX1);
	GetD3DDevice()->SetTexture(0, texture_data->m_pTexture);
	GetD3DDevice()->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, v, sizeof(VERTEX));
}