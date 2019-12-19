#pragma once

class Size
{
public:
	Size()
	{
		Width = 0.f;
		Height = 0.f;
	}

	Size(float width_, float height_) 
	{
		Width = width_;
		Height = height_;
	}

	Size(const Size& size_)
	{
		this->Width = size_.Width;
		this->Height = size_.Height;
	}

	Size operator + (const Size& size_)
	{
		Size tmp;
		tmp.Width = this->Width + size_.Width;
		tmp.Height = this->Height + size_.Height;
		return tmp;
	}
	Size operator - (const Size& size_)
	{
		Size tmp;
		tmp.Width = this->Width - size_.Width;
		tmp.Height = this->Height - size_.Height;
		return tmp;
	}
	Size operator * (const Size& size_)
	{
		Size tmp;
		tmp.Width = this->Width * size_.Width;
		tmp.Height = this->Height * size_.Height;
		return tmp;
	}
	Size operator / (const Size& size_)
	{
		Size tmp;
		tmp.Width = this->Width / size_.Width;
		tmp.Height = this->Height / size_.Height;
		return tmp;
	}
	Size& operator += (const Size& size_)
	{
		this->Width += size_.Width;
		this->Height += size_.Height;
		return *this;
	}
	Size& operator -= (const Size& size_)
	{
		this->Width -= size_.Width;
		this->Height -= size_.Height;
		return *this;
	}
	Size& operator *= (const Size& size_)
	{
		this->Width *= size_.Width;
		this->Height *= size_.Height;
		return *this;
	}
	Size& operator /= (const Size& size_)
	{
		this->Width /= size_.Width;
		this->Height /= size_.Height;
		return *this;
	}

private:
	float Width;
	float Height;
};