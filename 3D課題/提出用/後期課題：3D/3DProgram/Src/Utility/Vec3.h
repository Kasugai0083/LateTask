#pragma once

#pragma once

/**
* @file Vec.h
* @brief 3Dの情報を保存できる構造体の宣言
*/

//=====================================================================//
//! Vector用構造体(3D版)
//=====================================================================//
typedef struct Vec3
{
	/** Constructor */
	Vec3()
	{
		X = 0.0f;
		Y = 0.0f;
		Z = 0.0f;
	}

	/**
	* @brief Constructor
	* @param[in] x 横幅
	* @param[in] y 縦幅
	* @param[in] z 奥行
	*/
	Vec3(float x, float y, float z)
	{
		X = x;
		Y = y;
		Z = z;
	}

	/**
	* @brief Constructor
	* @param[in] Vec3 コピー用Vec2データ
	*/
	Vec3(const Vec3& size)
	{
		this->X = size.X;
		this->Y = size.Y;
		this->Z = size.Z;
	}

	float X;	//!< X値
	float Y;	//!< Y値
	float Z;	//!< Z値
}Pos3;
