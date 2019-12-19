#include <d3d9.h>
#include <d3dx9.h>
#include "Graphics.h"
#include "Size.h"
#include "Vec.h"

TextureFactory* TexFactory() {
	TextureFactory Instance;
	return &Instance;
}

struct CustomVertex 
{
	float X, Y, Z;
	float Rhw;

	float TextureX, TextureY;
};

const int FVF = (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1);

bool TextureFactory::InitGraphics(bool is_fullscreen_)
{
	D3DPRESENT_PARAMETERS present_param;
	ZeroMemory(&present_param, sizeof(D3DPRESENT_PARAMETERS));

	if (CreateGraphicsInterface() == false) 
	{
		return false;
	}

	if (CreateGraphicsDevice(&present_param, is_fullscreen_) == false)
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

void TextureFactory::EndGraphics()
{
	for(LPD3DXFONT list: m_FontList)
	{
		list->Release();
	}
	m_D3DDevice->Release();
	m_D3DInterface->Release();
}

bool TextureFactory::DrawStart()
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

void TextureFactory::DrawEnd()
{
	m_D3DDevice->EndScene();
	m_D3DDevice->Present(nullptr, nullptr, nullptr, nullptr);
}

void TextureFactory::DrawTexture(Vec3 size_, Texture* texture_data_) 
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

void TextureFactory::DrawFont(Vec3 vec_, const char* text, FontSize font_type_, FontColor color)
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
