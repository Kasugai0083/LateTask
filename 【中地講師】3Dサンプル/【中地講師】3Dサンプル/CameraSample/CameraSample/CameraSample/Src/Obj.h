#ifndef OBJ_H_
#define OBJ_H_

#include <d3d9.h>
#include <d3dx9.h>
#include "XFile.h"

class Obj
{
public:
	Obj(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 angle, XFile *xfile) : 
		m_Pos(pos),
		m_Scale(scale),
		m_Angle(angle),
		m_pXFile(xfile)
	{}

	void Update(void);
	void Draw(void);

	D3DXVECTOR3 GetAngle()
	{
		return m_Angle;
	}

	D3DXVECTOR3 GetPos()
	{
		return m_Pos;
	}

	/**
	* @brief 前方ベクトルの取得関数@n
	* ただのゲッターではなく、@n
	* 関数内で計算が行われるので注意
	* @return オブジェクトの前方ベクトル
	*/
	D3DXVECTOR3 GetForward();

private:
	D3DXVECTOR3 m_Pos;
	D3DXVECTOR3 m_Scale;
	D3DXVECTOR3 m_Angle;
	XFile *m_pXFile;
};

#endif