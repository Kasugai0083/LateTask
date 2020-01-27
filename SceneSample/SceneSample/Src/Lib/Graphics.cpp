﻿#include <d3d9.h>
#include <d3dx9.h>
#include "Graphics.h"
#include "Window.h"
#include "../Utility/Size.h"
#include "../Utility/Vec.h"
#include "Engine.h"

#define FVF (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)

// 静的ライブラリ
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

struct CustomVertex
{
	float X;			// X座標
	float Y;			// Y座標
	float Z;			// Z座標	
	float Rhw;			// 除算数

	float TextureX;		// テクスチャ座標X
	float TexrureY;		// テクスチャ座標Y
};

/*
	staticをグローバル変数に指定すると
	別のcppからのアクセスができなくなる

		メリット
			無駄なアクセスを減らせる

	staticとつける => さわるなを明示してる
*/

LPDIRECT3DDEVICE9 g_D3DDevice;// DirectGraphicsデバイス

namespace {

	// グローバル変数
	static LPDIRECT3D9 g_D3DInterface;						// DirectGraphicsインターフェース
	static LPD3DXFONT g_FontList[FontSize::FontSizeMax];	// フォントデバイスリスト
	static LPDIRECT3DVERTEXBUFFER9 g_VertexBuf9;
}

namespace Graphic {

	// インターフェースの作成
	bool CreateGraphicsInterface();

	// グラフィックデバイスの作成
	bool CreateGraphicsDevice(D3DPRESENT_PARAMETERS* present_param, bool isFullScreen);

	// ViewPortの設定
	bool SetUpViewPort(D3DPRESENT_PARAMETERS* present_param);

	// フォントデバイスの生成
	bool CreateFontDevice();

	bool InitGraphics(bool isFull)
	{
		D3DPRESENT_PARAMETERS present_param;
		ZeroMemory(&present_param, sizeof(D3DPRESENT_PARAMETERS));

		if (CreateGraphicsInterface() == false)
		{
			return false;
		}

		if (CreateGraphicsDevice(&present_param, isFull) == false)
		{
			return false;
		}

		if (SetUpViewPort(&present_param) == false)
		{
			return false;
		}

		if (CreateFontDevice() == false)
		{
			return false;
		}

		return true;
	}

	void EndGraphics()
	{
		for (int i = 0; i < FontSize::FontSizeMax; i++)
		{
			g_FontList[i]->Release();
		}
		g_D3DDevice->Release();
		g_D3DInterface->Release();
	}

	bool DrawStart()
	{
		g_D3DDevice->Clear(
			0,
			NULL,
			D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER|D3DCLEAR_STENCIL,
			D3DCOLOR_XRGB(0, 0, 0),
			0.0f, 0);

		g_D3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
		g_D3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		g_D3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

		if (D3D_OK == g_D3DDevice->BeginScene())
		{
			return true;
		}

		return false;
	}

	void DrawEnd()
	{
		g_D3DDevice->EndScene();
		g_D3DDevice->Present(NULL, NULL, NULL, NULL);
	}


	void DrawTexture(float x, float y, Texture* texture_data)
	{
		CustomVertex v[4] =
		{
			{ x, y, 0.0f, 1.0f, 0.0f, 0.0f },
			{ x + texture_data->Width, y, 0.0f, 1.0f, 1.0f, 0.0f },
			{ x + texture_data->Width, y + texture_data->Height, 0.0f, 1.0f, 1.0f, 1.0f },
			{ x, y + texture_data->Height, 0.0f, 1.0f, 0.0f, 1.0f },
		};

		// 頂点構造の指定
		g_D3DDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_TEX1);

		g_D3DDevice->SetTexture(0, texture_data->TexutreData);

		g_D3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, v, sizeof(CustomVertex));
	}
	void DrawTexture(float x, float y, Texture* texture_data, float width_, float height_)
	{
		CustomVertex v[4] =
		{
			{ x, y, 0.0f, 1.0f, 0.0f, 0.0f },
			{ x + width_, y, 0.0f, 1.0f, 1.0f, 0.0f },
			{ x + width_, y + height_, 0.0f, 1.0f, 1.0f, 1.0f },
			{ x, y + height_, 0.0f, 1.0f, 0.0f, 1.0f },
		};

		// 頂点構造の指定
		g_D3DDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_TEX1);

		g_D3DDevice->SetTexture(0, texture_data->TexutreData);

		g_D3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, v, sizeof(CustomVertex));
	}

	//統合画像切り抜き用
	void DrawIntegratedTexture(float x, float y, Texture* texture_data, float tu, float tv, float spriteX, float spriteY, int spriteNumX, int spriteNumY)
	{

		int tmpX = spriteNumX - 1;
		int tmpY = spriteNumY - 1;

		CustomVertex v[4] =
		{
			{ x, y, 0.0f, 1.0f, tu*tmpX, tv*tmpY },
			{ x + spriteX, y, 0.0f, 1.0f, tu*spriteNumX, tv*tmpY },
			{ x + spriteX, y + spriteY, 0.0f, 1.0f, tu*spriteNumX, tv*spriteNumY },
			{ x, y + spriteY, 0.0f, 1.0f, tu*tmpX, tv*spriteNumY},
		};

		// 頂点構造の指定
		g_D3DDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_TEX1);

		g_D3DDevice->SetTexture(0, texture_data->TexutreData);

		g_D3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, v, sizeof(CustomVertex));
	}

	void DrawUVScrollTexture(float x, float y, Texture* texture_data, float tu, float tv)
	{
		CustomVertex v[4] =
		{
			{ x, y, 0.0f, 1.0f, tu, tv },
			{ x + texture_data->Width, y, 0.0f, 1.0f, tu + 1.0f, tv },
			{ x + texture_data->Width, y + texture_data->Height, 0.0f, 1.0f, tu + 1.0f, tv + 1.0f },
			{ x, y + texture_data->Height, 0.0f, 1.0f, tu, tv + 1.0f },
		};

		// 頂点構造の指定
		g_D3DDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_TEX1);

		g_D3DDevice->SetTexture(0, texture_data->TexutreData);

		g_D3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, v, sizeof(CustomVertex));
	}

	float center_x, center_y;

	void PlayerDrawTexture(float x, float y, float rotate, Texture* texture_data)
	{

		float RAD = 3.141592f / 180.0f; // ラジアンの初期化


		CustomVertex v[4] =
		{
			{ x , y , 0.0f, 1.0f, 0.0f, 0.0f },
			{ x + texture_data->Width, y, 0.0f, 1.0f, 1.0f, 0.0f },
			{ x + texture_data->Width, y + texture_data->Height, 0.0f, 1.0f, 1.0f, 1.0f },
			{ x , y + texture_data->Height , 0.0f, 1.0f, 0.0f, 1.0f },
		};

		D3DXMATRIX PosMatrix, RotateMatrix;
		int i;

		center_x = (v[2].X - v[0].X) / 2.0f + v[0].X;
		center_y = (v[2].Y - v[0].Y) / 2.0f + v[0].Y;

		for (int i = 0; i < 4; i++) {
			v[i].X -= center_x;
			v[i].Y -= center_y;
		}


		// 行列の初期化（単位行列生成）
		D3DXMatrixIdentity(&PosMatrix);
		D3DXMatrixIdentity(&RotateMatrix);

		// 回転行列に角度を設定
		D3DXMatrixRotationZ(&RotateMatrix, rotate * RAD);

		// 回転処理
		for (i = 0; i < 4; i++) {
			// 現在の頂点座標を格納
			D3DXMatrixTranslation(&PosMatrix, v[i].X, v[i].Y, v[i].Z);
			// 演算
			PosMatrix *= RotateMatrix;
			// 結果を戻す
			v[i].X = PosMatrix._41;
			v[i].Y = PosMatrix._42;
			v[i].Z = PosMatrix._43;
		}



		for (int i = 0; i < 4; i++) {
			v[i].X += center_x;
			v[i].Y += center_y;
		}

		// 頂点構造の指定
		g_D3DDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_TEX1);

		g_D3DDevice->SetTexture(0, texture_data->TexutreData);

		g_D3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, v, sizeof(CustomVertex));

	}



	void DrawFont(float pos_x, float pos_y, const char* text, FontSize font_type, FontColor color)
	{
		RECT rect =
		{
			(long)pos_x,
			(long)pos_y,
			(long)pos_x + 1500,
			(long)pos_y + 200,
		};

		int r, g, b;
		r = g = b = 255;

		if (color == FontColor::Black)
		{
			r = g = b = 0;
		}
		else if (color == FontColor::Red)
		{
			r = 255;
			g = b = 0;
		}

		g_FontList[font_type]->DrawTextA(
			NULL,
			text,
			-1,
			&rect,
			DT_LEFT,
			D3DCOLOR_XRGB(r, g, b)
		);
	}

	bool CreateTexture(const char* file_name, Texture* texture_data)
	{
		Size size;
		D3DXIMAGE_INFO info;

		// 2の累乗じゃないケースを想定して元のサイズを取得してD3DXCreateTextureFromFileExで使う
		D3DXGetImageInfoFromFileA(file_name, &info);

		if (FAILED(D3DXCreateTextureFromFileExA(g_D3DDevice,
			file_name,
			info.Width,
			info.Height,
			1,
			0,
			D3DFMT_UNKNOWN,
			D3DPOOL_MANAGED,
			D3DX_DEFAULT,
			D3DX_DEFAULT,
			0x0000ff00,
			nullptr,
			nullptr,
			&texture_data->TexutreData)))
		{
			return false;
		}
		else
		{
			// テクスチャサイズの取得
			D3DSURFACE_DESC desc;

			if (FAILED(texture_data->TexutreData->GetLevelDesc(0, &desc)))
			{
				texture_data->TexutreData->Release();
				return false;
			}
			texture_data->Width = desc.Width;
			texture_data->Height = desc.Height;
		}

		return true;
	}



	bool CreateGraphicsInterface()
	{
		// インターフェース作成
		g_D3DInterface = Direct3DCreate9(D3D_SDK_VERSION);
		if (g_D3DInterface == NULL)
		{
			// 作成失敗
			return false;
		}

		// 作成成功
		return true;
	}

	bool CreateGraphicsDevice(D3DPRESENT_PARAMETERS* present_param, bool isFullScreen)
	{

		bool IsFullScreen = true;

		// バックバッファの数 => 1
		present_param->BackBufferCount = 1;
		//ディスプレイモード
		present_param->BackBufferFormat = D3DFMT_A8R8G8B8;
		//ステンシルバッファのフォーマット
		present_param->AutoDepthStencilFormat = D3DFMT_D24S8;
		//バックバッファからフロントバッファへ転送時のオプション
		present_param->Flags = D3DPRESENTFLAG_DISCARD_DEPTHSTENCIL;

		if (isFullScreen == true) {
			// ウィンドウモード設定 => 定数で切り替え
			present_param->Windowed = false;
			//横の解像度
			present_param->BackBufferWidth = 1920;
			//縦の解像度
			present_param->BackBufferHeight = 1080;
			//フルスクリーンのリフレッシュレート
			present_param->FullScreen_RefreshRateInHz = 60.f;
		}
		else {
			// ウィンドウモード設定 => 定数で切り替え
			present_param->Windowed = true;
			//横の解像度
			present_param->BackBufferWidth = WIN_W;
			//縦の解像度
			present_param->BackBufferHeight = WIN_H;
			//フルスクリーンのリフレッシュレート
			present_param->FullScreen_RefreshRateInHz = 0.f;
		}


		//マルチサンプルの数
		present_param->MultiSampleType = D3DMULTISAMPLE_4_SAMPLES;
		//マルチサンプルの品質レベル
		present_param->MultiSampleQuality = 0;
		//深度ステンシルバッファがあるかどうか
		present_param->EnableAutoDepthStencil = TRUE;
		//スワップエフェクトの書き換えタイミング
		present_param->PresentationInterval = D3DPRESENT_INTERVAL_ONE;
		// スワップエフェクト => バックバッファとフロントバッファへの切り替え方法
		present_param->SwapEffect = D3DSWAPEFFECT_DISCARD;

		// DirectDeviceの作成
		if (FAILED(g_D3DInterface->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			FindWindowA(WINDOW_CLASS_NAME, nullptr),
			D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED,
			present_param,
			&g_D3DDevice)))
		{
			return false;
		}

		return true;
	}

	bool SetUpViewPort(D3DPRESENT_PARAMETERS* present_param)
	{
		// ビューポートパラメータ
		D3DVIEWPORT9 view_port;

		// ビューポートの左上座標
		view_port.X = 0;
		view_port.Y = 0;
		// ビューポートの幅
		view_port.Width = present_param->BackBufferWidth;
		// ビューポートの高さ
		view_port.Height = present_param->BackBufferHeight;
		// ビューポート深度設定
		view_port.MinZ = 0.0f;
		view_port.MaxZ = 1.0f;

		// ビューポート設定
		if (FAILED(g_D3DDevice->SetViewport(&view_port)))
		{
			return false;
		}

		return true;
	}

	bool CreateFontDevice()
	{
		int size_list[] =
		{
			SMALL_FONT_SIZE,
			REGULAR_FONT_SIZE,
			LARGE_FONT_SIZE
		};

		for (int i = 0; i < FontSize::FontSizeMax; i++)
		{
			if (FAILED(D3DXCreateFont(g_D3DDevice,
				size_list[i],
				size_list[i] / 2,
				FW_REGULAR,
				NULL,
				FALSE,
				DEFAULT_CHARSET,
				OUT_DEFAULT_PRECIS,
				PROOF_QUALITY,
				FIXED_PITCH | FF_SCRIPT,
				TEXT("ＭＳ　Ｐゴシック"),
				&g_FontList[i])))
			{
				return false;
			}
		}

		return true;
	}
};