#include <d3dx9.h>
#include <stdlib.h>
#include "../Engine/Graphics.h"
#include "Texture.h"

// カテゴリごとのテクスチャ保存用配列
static Texture g_TextureList[TextureList::TextureMax];

// IDチェック
bool IsRangeCheck(int texture_id);

void InitTexture()
{
	AllReleaseTexture();

	for (int i = 0; i < TextureList::TextureMax; i++)
	{
		g_TextureList[i].TexutreData = nullptr;
	}
}

void ReleaseCategoryTexture()
{
	for (int i = 0; i < TextureList::TextureMax; i++)
	{
		if (g_TextureList[i].TexutreData == nullptr)
		{
			continue;
		}

		g_TextureList[i].TexutreData->Release();
		g_TextureList[i].TexutreData = nullptr;
	}
}

void AllReleaseTexture()
{
	ReleaseCategoryTexture();
}

bool LoadTexture(const char* file_name, int texture_id)
{
	if (IsRangeCheck(texture_id) == false)
	{
		return false;
	}

	return CreateTexture(file_name, &g_TextureList[texture_id]);
}

Texture* GetTexture(int texture_id)
{
	if (IsRangeCheck(texture_id) == false)
	{
		return nullptr;
	}
	return &g_TextureList[texture_id];
}

bool IsRangeCheck(int texture_id)
{
	if (texture_id <= -1 ||
		texture_id >= TextureList::TextureMax)
	{
		return false;
	}

	return true;
}
