#pragma once

#include <Windows.h>
#include <d3d9.h>

class Size;
class Vec3;

const int SMALL_FONT_SIZE = 16;
const int REGULAR_FONT_SIZE = 24;
const int LARGE_FONT_SIZE = 64;

enum class FontSize
{
	Small,
	Regular,
	Large,
	FontSizeMax
};

enum class FontColor
{
	Black,
	White,
	Red,
	Yellow
};

struct Texture
{
	LPDIRECT3DTEXTURE9 TextureData;
	float Width, Height;
};

class TextureFactory
{
public:


	bool InitGraphics(bool is_fullscreen_);

	void EndGraphics();

	bool DrawStart();

	void DrawEnd();

	void DrawTexture(Vec3 vec_, Texture* texture_data);

	void DrawFont(Vec3 vec_, const char* text_, FontSize size_, FontColor color_);

	bool CreateTexture(const char* file_name_, Texture* texture_data_);

private:

	bool CreateGraphicsInterface();
	bool CreateGraphicsDevice(D3DPRESENT_PARAMETERS* present_param_, bool isFullScreen_);
	bool SetUpViewPort(D3DPRESENT_PARAMETERS* present_param);
	bool CreateFontDevice();

private:

	LPDIRECT3D9 m_D3DInterface;
	LPDIRECT3DDEVICE9 m_D3DDevice;
	LPD3DXFONT m_FontList[static_cast<int>(FontSize::FontSizeMax)];

};

TextureFactory* TexFactory();
