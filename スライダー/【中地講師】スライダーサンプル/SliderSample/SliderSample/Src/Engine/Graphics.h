/**
* @file Graphics.h
* @brief 描画に関する関数、定数の宣言
*/
#ifndef GRAPHICS_H_
#define GRAPHICS_H_

#include <Windows.h>
#include <d3d9.h>
#include "Texture.h"

/** @brief フォントカラー */
enum FontColor
{
	Black,			//!< 黒
	White,			//!< 白
	Red,			//!< 赤
};

// @brief フォントサイズ */
enum FontSize
{
	Small,			//!< 小
	Regular,		//!< 中
	Large,			//!< 大
	FontSizeMax,	//!< サイズ最大数
};

#define SMALL_FONT_SIZE (16)	//!< フォントサイズ(小)
#define REGULAR_FONT_SIZE (24)	//!< フォントサイズ(中)
#define LARGE_FONT_SIZE (32)	//!< フォントサイズ(大)

/** @brief UV情報から矩形を作成するための構造体 */
struct UVRect
{
	/**
	* @brief Constructor@n
	* @param[in] pos_x テクスチャ座標X
	* @param[in] pos_y テクスチャ座標Y
	* @param[in] width 矩形の横幅
	* @param[in] height 矩形の縦幅
	* @param[in] tex_id 使用するテクスチャのID
	*/
	UVRect(float pos_x, float pos_y, float width, float height, TextureList tex_id) :
		m_TexturePosX(pos_x),
		m_TexturePosY(pos_y),
		m_RectWidth(width),
		m_RectHeight(height),
		m_TextureId(tex_id)
	{
	}

	float m_TexturePosX;		//!< テクスチャ座標X
	float m_TexturePosY;		//!< テクスチャ座標Y
	float m_RectWidth;			//!< 矩形横幅
	float m_RectHeight;			//!< 矩形縦幅
	TextureList m_TextureId;	//!< 対象のテクスチャID
};


struct UVAnimationRect : public UVRect
{
	/**
	* @brief Constructor@n
	* @param[in] pos_x テクスチャ座標X
	* @param[in] pos_y テクスチャ座標Y
	* @param[in] width 矩形の横幅
	* @param[in] height 矩形の縦幅
	* @param[in] tex_id 使用するテクスチャのID
	* @param[in] change_frame 切り替えにかかるフレーム
	* @param[in] next_id 次のアニメーションID
	*/
	UVAnimationRect(float pos_x, float pos_y, float width, float height, TextureList tex_id, float change_frame, float next_id) :
		UVRect(pos_x, pos_y, width, height, tex_id),
		m_ChangeFrame(change_frame),
		m_NextAnimationId(next_id)
	{}

	float m_ChangeFrame;		//!< 切り替えフレーム
	float m_NextAnimationId;	//!< 次のアニメーションID
};

/**
* @brief Graphics機能初期化関数@n
* 描画関連を使用可能にするための初期化を行う@n
* ※Engine.cppのInitEngineで実行しているので@n
* 　使用者は自分たちで使う必要はない
* @return 初期化結果 (trueが成功)
*/
bool InitGraphics();

/**
* @brief Graphics機能終了関数@n
* 描画関連の処理の後始末を行う処理@n
* ※Engine.cppのEndEngineで実行しているので@n
* 　使用者は自分たちで使う必要はない
*/
void EndGraphics();

/**
* @brief 描画開始関数@n
* 描画開始を宣言し、バックバッファのクリアを行う
* @return 描画開始の成否 (成功はtrue)
*/
bool DrawStart();

/**
* @brief 描画終了関数@n
* 描画の終了を宣言し、バックバッファとフロントバッファを入れ替える@n
* ※この関数は必ずDrawStartの後に実行されるようにしてください。
*/
void DrawEnd();

/**
* @brief テクスチャ描画関数@n
* 指定された位置にテクスチャを描画する@n
* ※texture_dataはFile.hのGetTextureDataを使用してください。
* @param[in] x X軸描画座標
* @param[in] y Y軸描画座標
* @param[in] texture_data 描画で使用するテクスチャのデータ
*/
void DrawTexture(float x, float y, Texture* texture_data);

void DrawUVMappingTexture(float x, float y, UVRect* rect);

void DrawUVMappingTexture(float x, float y, Texture* texture_data, float texture_x, float texture_y, float sprite_width, float sprite_height);

void DrawRect(float x, float y, float width, float height, DWORD color);

/**
* @brief フォント描画関数@n
* 指定された位置にフォントを描画する@n
* @param[in] x X軸描画座標
* @param[in] y Y軸描画座標
* @param[in] text 描画するテキスト
* @param[in] size フォントサイズの種類
* @param[in] color フォントの色
*/
void DrawFont(float pos_x, float pos_y, const char* text, FontSize size, FontColor color);

/**
* @brief テクスチャ作成@n
* 指定された情報から読み込み、テクスチャを作成する@n
* ※開発側はFile.hのLoadTextureを使用してください。
* @return 作成結果(成功はtrue)
* @param[in] file_name 読み込むテクスチャの名前(パス込み)
* @param[out] texture_data 読み込まれたテクスチャを反映するデータ
*/
bool CreateTexture(const char* file_name, Texture* texture_data);

#endif
