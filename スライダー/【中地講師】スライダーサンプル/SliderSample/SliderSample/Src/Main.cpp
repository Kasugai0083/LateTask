#include <Windows.h>
#include <math.h>
#include "Engine/Engine.h"
#include "Engine/Window.h"
#include "Engine/Input.h"
#include "Engine/Texture.h"
#include "Engine/Graphics.h"

/** @brief スライダーの移動方向 */
enum Direction
{
	LeftToRight,		//!< 左 => 右
	RightToLeft,		//!< 右 => 左
	UpToDown,			//!< 上 => 下
	DownToUp,			//!< 下 => 上
};

/** @brief スライダー構造体 */
struct Slider
{

	// 左上原点
	float X;				//!< スライダー描画位置(X)
	float Y;				//!< スライダー描画位置(Y)

	float MinValue;			//!< 最小値
	float MaxValue;			//!< 最大値

	float CurrentValue;		//!< 現在の値
	float NextValue;		//!< 次の値
	float MoveSpeed;		//!< 移動速度

	Direction Dir;			//!< 進行方向
	TextureList Texture;	//!< 使用するテクスチャ
};

/**
* @brief スライダーのNextValueの更新関数@n
* スライダーのNextValueを更新する
* @param[in] next_value 更新する値
* @param[out] out_slider 更新するスライダーデータ
*/
void UpdateSliderNextValue(float next_value, Slider& out_slider)
{
	// 値を更新する
	out_slider.NextValue = max(out_slider.MinValue, min(next_value, out_slider.MaxValue));

	// 今の値と新しい値の差を出して、速度を算出する
	float distance = fabsf(out_slider.CurrentValue - out_slider.NextValue);

	// 移動にかかるフレーム数
	float moev_frame = 60.0f;
	out_slider.MoveSpeed = distance / moev_frame;
}

/**
* @brief スライダーのCurrentの更新関数@n
* スライダーのCurrentValueを更新する
* @param[out] out_slider 更新するスライダーデータ
*/
void UpdateSliderCurrentValue(Slider& out_slider)
{
	// NextValueとCurrentValueに差があればMoveSpeedで演算する
	if (out_slider.CurrentValue <= out_slider.NextValue)
	{
		out_slider.CurrentValue = min(out_slider.CurrentValue + out_slider.MoveSpeed, out_slider.NextValue);
	}
	else
	{
		out_slider.CurrentValue = max(out_slider.CurrentValue - out_slider.MoveSpeed, out_slider.NextValue);
	}
}

/**
* @brief 逆移動関数@n
* スライダーの移動方向とは反対に動くための処理を行う
* @param[in] rate 描画するスライダーの位置の比率
* @param[in] size スライダーのサイズ
* @param[out] out_pos スライダーの座標
* @param[out] out_tex_pos スライダー画像のテクスチャ座標
* @param[out] out_size スライダー画像のテクスチャサイズ
*/
void ReverseMove(float rate, float size, float& out_pos, float& out_tex_pos, float& out_size)
{
	// 比率から描画開始位置をずらす
	out_pos = (out_pos + size) - (rate * size);

	// サイズも比率で変更する
	out_size *= rate;
	
	// テクスチャの座標も比率の分だけずらす
	out_tex_pos += (1.0f - rate) * size;
}

/**
* @brief スライダー描画関数(矩形Version)@n
* スライダー構造体の情報からスライダーを描画する
* @param[in] slider 描画に使うスライダー情報
*/
void DrawSliderRectVersion(const Slider& slider)
{
	Texture* tex_data = GetTexture(slider.Texture);
	float pos_x = slider.X;
	float pos_y = slider.Y;
	float width = tex_data->Width;
	float height = tex_data->Height;

	// 現状の値を比率として算出する
	float rate = (slider.CurrentValue - slider.MinValue) / (slider.MaxValue - slider.MinValue);
	// 各進行方向による処理を実装する
	if (slider.Dir == Direction::LeftToRight)
	{
		// 横幅に比率を掛けてサイズを調整する
		width *= rate;
	}
	else if (slider.Dir == Direction::RightToLeft)
	{
		// 最小 => 最大の方向とX軸の最小 => 最大が逆なので反転させる
		// 比率から描画開始位置をずらす
		pos_x += (1.0f - rate) * width;

		// サイズも比率で変更する
		width *= rate;
	}
	else if (slider.Dir == Direction::UpToDown)
	{
		// 縦幅に比率を掛けてサイズを調整する
		height *= rate;
	}
	else if (slider.Dir == Direction::DownToUp)
	{
		// 最小 => 最大の方向とY軸の最小 => 最大が逆なので反転させる
		// 比率から描画開始位置をずらす
		pos_y += (1.0f - rate) * height;

		// サイズも比率で変更する
		height *= rate;
	}

	DrawRect(
		pos_x,
		pos_y,
		width,
		height,
		0xff0000ff
	);
}

/**
* @brief スライダー描画関数(UVマッピングVersion)@n
* スライダー構造体の情報からスライダーを描画する
* @param[in] slider 描画に使うスライダー情報
*/
void DrawSliderUVMappingVersion(const Slider& slider)
{
	Texture* tex_data = GetTexture(slider.Texture);
	// 変更される情報をsliderとtexture_dataから取得する
	float pos_x = slider.X;
	float pos_y = slider.Y;
	float tex_x = 0.0f;
	float tex_y = 0.0f;
	float tex_width = tex_data->Width;
	float tex_height = tex_data->Height;

	// 現状の値を比率として算出する
	float rate = (slider.CurrentValue - slider.MinValue) / (slider.MaxValue - slider.MinValue);
	// 各進行方向による処理を実装する
	if (slider.Dir == Direction::LeftToRight)
	{
		// 横幅に比率を掛けてサイズを調整する
		tex_width *= rate;
	}
	else if (slider.Dir == Direction::RightToLeft)
	{
		// 最小 => 最大の方向とX軸の最小 => 最大が逆なので反転させる
		ReverseMove(rate, tex_width, pos_x, tex_x, tex_width);
	}
	else if (slider.Dir == Direction::UpToDown)
	{
		// 縦幅に比率を掛けてサイズを調整する
		tex_height *= rate;
	}
	else if (slider.Dir == Direction::DownToUp)
	{
		// 最小 => 最大の方向とY軸の最小 => 最大が逆なので反転させる
		ReverseMove(rate, tex_height, pos_y, tex_y, tex_height);
	}

	DrawUVMappingTexture(
		pos_x,
		pos_y,
		tex_data,
		tex_x,
		tex_y,
		tex_width,
		tex_height
	);
}

int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR     lpCmpLine,
	INT       nCmdShow)
{
	// エンジンの初期化
	if (InitEngine(WINDOW_WIDTH, WINDOW_HEIGHT, "SliderSample") == false)
	{
		return 0;
	}

	LoadTexture("Res/Slider01.png", TextureList::Slider01Texture);
	LoadTexture("Res/Slider02.png", TextureList::Slider02Texture);

	Slider sliders[] = 
	{
		{
			120.0f,							// X座標
			100.0f,							// Y座標
			0.0f,							// 最小値
			100.0f,							// 最大値
			0.0f,							// 現状の値
			100.0f,							// 次の値
			0.0f,							// 速度 
			Direction::RightToLeft,			// 進行方向
			TextureList::Slider01Texture	// 使用するテクスチャ
		},

		{
			120.0f,							// X座標
			300.0f,							// Y座標
			0.0f,							// 最小値
			100.0f,							// 最大値
			0.0f,							// 現状の値
			100.0f,							// 次の値
			0.0f,							// 速度 
			Direction::LeftToRight,			// 進行方向
			TextureList::Slider01Texture	// 使用するテクスチャ
		},

		{
			540.0f,							// X座標
			20.0f,							// Y座標
			0.0f,							// 最小値
			100.0f,							// 最大値
			0.0f,							// 現状の値
			100.0f,							// 次の値
			0.0f,							// 速度 
			Direction::UpToDown,			// 進行方向
			TextureList::Slider02Texture	// 使用するテクスチャ
		},

		{
			20.0f,							// X座標
			20.0f,							// Y座標
			0.0f,							// 最小値
			100.0f,							// 最大値
			0.0f,							// 現状の値
			100.0f,							// 次の値
			0.0f,							// 速度 
			Direction::DownToUp,			// 進行方向
			TextureList::Slider02Texture	// 使用するテクスチャ
		}
	};

	while (true)
	{
		bool message_ret = false;
		MSG msg;

		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				break;
			}
			else 
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			static int count = 0;
			count++;

			// 毎フレーム更新して時間がたったらCurrentを変更する
			for (int i = 0; i < 4; i++)
			{
				UpdateSliderCurrentValue(sliders[i]);

				if (count % 120 == 0)
				{
					UpdateSliderNextValue(sliders[i].MaxValue, sliders[i]);
				}
				else if (count % 60 == 0)
				{
					UpdateSliderNextValue(sliders[i].MinValue, sliders[i]);
				}
			}

			DrawStart();

			for (int i = 0; i < 4; i++)
			{
				DrawSliderUVMappingVersion(sliders[i]);
			}

			DrawEnd();
		}
	}

	// エンジン終了
	EndEngine();

	return 0;
}

