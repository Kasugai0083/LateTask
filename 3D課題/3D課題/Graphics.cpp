#include <d3d9.h>
#include <d3dx9.h>
#include "Graphics.h"
#include "Size.h"
#include "Vec.h"
#include "Window.h"

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

GraphicsFactory* GrapFactory() {
	GraphicsFactory Instance;
	return &Instance;
}

struct CustomVertex 
{
	float X, Y, Z;
	float Rhw;

	float TextureX, TextureY;
};

const int FVF = (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1);

bool GraphicsFactory::InitGraphics(bool is_fullscreen_)
{
	D3DPRESENT_PARAMETERS present_param;
	ZeroMemory(&present_param, sizeof(D3DPRESENT_PARAMETERS));

	if (CreateGraphicsInterface() == false) 
	{
		return false;
	}

	if (CreateGraphicsDevice(&present_param) == false)
	{
		return false;
	}

	if(SetUpViewPort(&present_param) == false)
	{
		return false;
	}

	if(CreateFontDevice() == false)
	{
		return false;
	}
	return true;
}

void GraphicsFactory::EndGraphics()
{
	for(LPD3DXFONT list: m_FontList)
	{
		list->Release();
	}
	m_D3DDevice->Release();
	m_D3DInterface->Release();
}

bool GraphicsFactory::DrawStart()
{
	m_D3DDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0,0,0), 0.f, 0);

	m_D3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	m_D3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_D3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	if(D3D_OK == m_D3DDevice->BeginScene())
	{
		return true;
	}
	return false;
}

void GraphicsFactory::DrawEnd()
{
	m_D3DDevice->EndScene();
	m_D3DDevice->Present(nullptr, nullptr, nullptr, nullptr);
}

void GraphicsFactory::DrawTexture(Vec3 size_, Texture* texture_data_) 
{
	CustomVertex v[4] =
	{
		{ size_.X, size_.Y, size_.Z, 1.0f, 0.0f, 0.0f }, 
		{ size_.X + texture_data_->Width, size_.Y, size_.Z, 1.0f, 1.0f, 0.0f }, 
		{ size_.X + texture_data_->Width, size_.Y + texture_data_->Height, size_.Z, 1.0f, 1.0f, 1.0f },
		{ size_.X, texture_data_->Width + texture_data_->Height, size_.Z, 1.0f, 0.0f, 1.0f },
	};

	m_D3DDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_TEX1);

	m_D3DDevice->SetTexture(0, texture_data_->TextureData);

	m_D3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, v, sizeof(CustomVertex));
}

void GraphicsFactory::DrawFont(Vec3 vec_, const char* text, FontSize font_type_, FontColor color)
{
	RECT rect =
	{
		(long)vec_.X,
		(long)vec_.Y,
		(long)vec_.X + 1500,
		(long)vec_.Y + 200,
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
	else if (color == FontColor::Yellow)
	{
		r = 255;
		g = 215;
		b = 20;
	}

	m_FontList[static_cast<int>(font_type_)]->DrawTextA(
		NULL,
		text,
		-1,
		&rect,
		DT_LEFT,
		D3DCOLOR_XRGB(r, g, b)
	);
}

bool GraphicsFactory::CreateTexture(const char* file_name_, Texture* texture_data_)
{
	Size size;
	D3DXIMAGE_INFO info;

	D3DXGetImageInfoFromFileA(file_name_, &info);

	if(FAILED(D3DXCreateTextureFromFileExA(m_D3DDevice,
		file_name_,
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
		&texture_data_->TextureData)))
	{
		return false;
	}
	else
	{
		D3DSURFACE_DESC desc;

		if (FAILED(texture_data_->TextureData->GetLevelDesc(0, &desc))) 
		{
			texture_data_->TextureData->Release();
			return false;
		}
		texture_data_->Width = desc.Width;
		texture_data_->Height = desc.Height;
	}
	return true;
}

bool GraphicsFactory::CreateGraphicsInterface()
{
	m_D3DInterface = Direct3DCreate9(D3D_SDK_VERSION);
	if(m_D3DInterface == NULL)
	{
		return false;
	}
	return true;
}

bool GraphicsFactory::CreateGraphicsDevice(D3DPRESENT_PARAMETERS* present_param_)
{
	//! バックバッファの数 => 1
	present_param_->BackBufferCount = 1;
	//! ディスプレイモード
	present_param_->BackBufferFormat = D3DFMT_A8R8G8B8;
	//! ステンシルバッファのフォーマット
	present_param_->AutoDepthStencilFormat = D3DFMT_D24S8;
	//! バックバッファからフロントバッファへ転送時のオプション
	present_param_->Flags = D3DPRESENTFLAG_DISCARD_DEPTHSTENCIL;

	if(m_FullScreen == true)
	{
		//! ウィンドウモード設定 => 定数で切り替え
		present_param_->Windowed = false;
		//! 横の解像度
		present_param_->BackBufferWidth = 1920.f;
		//! 縦の解像度
		present_param_->BackBufferHeight = 1080.f;
		//! フルスクリーンのリフレッシュレート
		present_param_->FullScreen_RefreshRateInHz = 60.f;
	}
	else
	{
		//! ウィンドウモード設定 => 定数で切り替え
		present_param_->Windowed = false;
		//! 横の解像度
		present_param_->BackBufferWidth = 1920.f;
		//! 縦の解像度
		present_param_->BackBufferHeight = 1080.f;
		//! フルスクリーンのリフレッシュレート
		present_param_->FullScreen_RefreshRateInHz = 60.f;
	}

	//! マルチサンプルの数
	present_param_->MultiSampleType = D3DMULTISAMPLE_4_SAMPLES;
	//! マルチサンプルの品質レベル
	present_param_->MultiSampleQuality = 0;
	//! 深度ステンシルバッファがあるかどうか
	present_param_->EnableAutoDepthStencil = TRUE;
	//! スワップエフェクトの書き換えタイミング
	present_param_->PresentationInterval = D3DPRESENT_INTERVAL_ONE;
	//! スワップエフェクト => バックバッファとフロントバッファへの切り替え方法
	present_param_->SwapEffect = D3DSWAPEFFECT_DISCARD;

	//! DirectDeviceの作成
	if (FAILED(m_D3DInterface->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		FindWindowA(WINDOW_CLASS_NAME, nullptr),
		D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED,
		present_param_,
		&m_D3DDevice))) 
	{
		return false;
	}
	return true;
}

bool GraphicsFactory::SetUpViewPort(D3DPRESENT_PARAMETERS* present_param_)
{
	D3DVIEWPORT9 view_port;

	view_port.X = 0;
	view_port.Y = 0;

	view_port.Width = present_param_->BackBufferWidth;
	view_port.Height = present_param_->BackBufferHeight;

	view_port.MinZ = 0.f;
	view_port.MaxZ = 1.f;

	if(FAILED(m_D3DDevice->SetViewport(&view_port)))
	{
		return false;
	}
	return true;
}

bool GraphicsFactory::CreateFontDevice()
{
	int size_list[] =
	{
		SMALL_FONT_SIZE,
		REGULAR_FONT_SIZE,
		LARGE_FONT_SIZE
	};

	for(int i = 0; i < static_cast<int>(FontSize::FontSizeMax); i++)
	{
		if(FAILED(D3DXCreateFont(m_D3DDevice,
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
			&m_FontList[i])))
		{
			return false;
		}
	}
	return true;
}
