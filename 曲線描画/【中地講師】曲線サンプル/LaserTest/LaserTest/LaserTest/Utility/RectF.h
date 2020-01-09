#ifndef RECT_H_
#define RECT_H_

#include "Vec.h"
#include "Size.h"

struct RectF
{
	RectF(float x, float y, float width, float height)
	{
		X = x;
		Y = y;
		Width = width;
		Height = height;
	}

	RectF(Vec2 pos, Size size)
	{
		X = pos.X;
		Y = pos.Y;
		Width = size.Width;
		Height = size.Height;
	}

	RectF()
	{
		X = Y = Width = Height = 0.0f;
	}

	float X;
	float Y;
	float Width;
	float Height;
};

#endif
