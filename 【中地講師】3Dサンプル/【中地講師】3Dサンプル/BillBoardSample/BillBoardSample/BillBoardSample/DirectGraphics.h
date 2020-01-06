#ifndef DIRECT_GRAPHICS_H_
#define DIRECT_GRAPHICS_H_

#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>

// 読み込めるテクスチャの最大数
#define MAX_TEXTURE_NUM (100)

// 構造体宣言
typedef struct _VERTEX
{
	D3DXVECTOR3 pos;		// 座標
	D3DXVECTOR2 tex_pos;	// テクスチャ座標
}VERTEX;

typedef struct
{
	LPDIRECT3DTEXTURE9 m_pTexture;
	int m_Width;
	int m_Height;
} TEXTURE_DATA;


/*
	DirectGraphicsの初期化
		戻り値：
			初期化成功：
				true
			初期化失敗：
				false

		引数：
			HWND window_handle：
				DirectGraphicsで描画する対象となるウィンドウのハンドル

		内容：
			DirectXの初期化を行う
			必ずゲームループの前に1度だけ実行すること
			※現状はDirectGraphicsのみ初期化してる
*/
bool InitDirectGraphics(HWND window_handle);

/*
	LPDIRECT3DDEVICE9のゲッター
		戻り値：
			LPDIRECT3DDEVICE9

		引数：
			なし

		内容：
			LPDIRECT3DDEVICE9のゲッター
*/
const LPDIRECT3DDEVICE9 GetD3DDevice();

/*
	DirectGraphicsの終了
		戻り値：
			なし

		引数：
			なし

		内容：
			DirectXを終了させる
			ゲームループを抜けた後必ず１度だけ実行すること
*/
void ReleaseDirectGraphics();

/*
	テクスチャ読み込み
		戻り値：
			成功：
				テクスチャ番号(0以上の値)
			失敗：
				-1
		引数：
			const char * file_name：
				ファイル名

			int use_id：
				テクスチャ番号の指定
				有効番号を指定した場合はその番号で読み込みを完了させる
				※同じ番号で読み込まれているファイルがあればそちらは解放するので注意

		内容：
			指定されたテクスチャを読み込む
			成功したらテクスチャ番号が返り、失敗したら-1が返る
*/
int LoadTexture(const char *file_name, int use_id = -1);

/*
	テクスチャの解放
		戻り値：
			なし

		引数：
			int texture_id：
				テクスチャ番号

		内容：
			引数で指定したテクスチャを解放する
*/
void ReleaseTexture(int texture_id);

/*
	描画開始
		戻り値：
			なし

		引数：
			なし

		内容：
			描画処理を開始するための関数
			描画処理はこの関数を呼び出した後に行うこと
*/
void DrawStart();

/*
	描画終了
		戻り値：
			なし

		引数：
			なし

		内容：
			描画処理終了関数
			描画内容を画面に反映するにはこの関数を呼び出す必要がある
*/
void DrawEnd();

/*
	テクスチャの使用可否判定
		戻り値：
			true => テクスチャ使用可能
			false => テクスチャ使用不可

		引数：
			int tex_id
				使用可否を確認したいテクスチャ番号

		内容：
			指定されたテクスチャ番号が使用可能かどうかを判定する
*/
bool IsUseTexture(int tex_id);

/*
	テクスチャデータのゲッター
		戻り値：
			テクスチャデータのポインタ

		引数：
			取得したいテクスチャの番号

		内容：
			テクスチャデータのゲッター
*/
const TEXTURE_DATA *GetTextureData(int texture_id);

/*
	ビューマトリックスの逆行列取得

		戻り値：
			なし

		引数：
			D3DXMATRIX *out
				逆行列格納用のマトリックスのポインタ

		内容：
			ビューマトリックスの逆行列を取得する
*/
void InverseViewMatrix(D3DXMATRIX *out);

/*
	座標変換
		戻り値：
			なし

		引数：
			const D3DXVECTOR3 *camera_pos

			const D3DXVECTOR3 *eye_pos

		内容：
			ビューマトリックスとプロジェクションマトリックスを
			作成してSetTransformで設定する
*/
void Transform(const D3DXVECTOR3 *camera_pos, const D3DXVECTOR3 *eye_pos);

#endif
