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
	* @brief �O���x�N�g���̎擾�֐�@n
	* �����̃Q�b�^�[�ł͂Ȃ��A@n
	* �֐����Ōv�Z���s����̂Œ���
	* @return �I�u�W�F�N�g�̑O���x�N�g��
	*/
	D3DXVECTOR3 GetForward();

private:
	D3DXVECTOR3 m_Pos;
	D3DXVECTOR3 m_Scale;
	D3DXVECTOR3 m_Angle;
	XFile *m_pXFile;
};

#endif