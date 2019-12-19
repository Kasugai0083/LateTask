#pragma once

struct Vec3
{
	Vec3()
	{
		X = 0.f;
		Y = 0.f;
		Z = 0.f;
	}

	Vec3(float X_, float Y_, float Z_)
	{
		X = X_;
		Y = Y_;
		Z = Z_;
	}

	Vec3(const Vec3& Vec3_)
	{
		this->X = Vec3_.X;
		this->Y = Vec3_.Y;
		this->Z = Vec3_.Z;
	}

	Vec3 operator + (const Vec3& Vec3_)
	{
		Vec3 tmp;
		tmp.X = this->X + Vec3_.X;
		tmp.Y = this->Y + Vec3_.Y;
		tmp.Z = this->Z + Vec3_.Z;
		return tmp;
	}
	Vec3 operator - (const Vec3& Vec3_)
	{
		Vec3 tmp;
		tmp.X = this->X - Vec3_.X;
		tmp.Y = this->Y - Vec3_.Y;
		tmp.Z = this->Z - Vec3_.Z;
		return tmp;
	}
	Vec3 operator * (const Vec3& Vec3_)
	{
		Vec3 tmp;
		tmp.X = this->X * Vec3_.X;
		tmp.Y = this->Y * Vec3_.Y;
		tmp.Z = this->Z * Vec3_.Z;
		return tmp;
	}
	Vec3 operator / (const Vec3& Vec3_)
	{
		Vec3 tmp;
		tmp.X = this->X / Vec3_.X;
		tmp.Y = this->Y / Vec3_.Y;
		tmp.Z = this->Z / Vec3_.Z;
		return tmp;
	}
	Vec3& operator += (const Vec3& Vec3_)
	{
		this->X += Vec3_.X;
		this->Y += Vec3_.Y;
		this->Z += Vec3_.Z;
		return *this;
	}
	Vec3& operator -= (const Vec3& Vec3_)
	{
		this->X -= Vec3_.X;
		this->Y -= Vec3_.Y;
		this->Z -= Vec3_.Z;
		return *this;
	}
	Vec3& operator *= (const Vec3& Vec3_)
	{
		this->X *= Vec3_.X;
		this->Y *= Vec3_.Y;
		this->Z *= Vec3_.Z;
		return *this;
	}
	Vec3& operator /= (const Vec3& Vec3_)
	{
		this->X /= Vec3_.X;
		this->Y /= Vec3_.Y;
		this->Z /= Vec3_.Z;
		return *this;
	}

	float X, Y, Z;
};