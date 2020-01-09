#ifndef DRAWER_H_
#define DRAWER_H_

#include <d3d9.h>
#include <d3dx9.h>

class XFile;

class Drawer
{
public:
	Drawer(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 angle, XFile *xfile) : 
		m_Pos(pos),
		m_Scale(scale),
		m_Angle(angle),
		m_pXFile(xfile)
	{}

	void Draw(void);
private:
	D3DXVECTOR3 m_Pos;
	D3DXVECTOR3 m_Scale;
	D3DXVECTOR3 m_Angle;
	XFile *m_pXFile;
};

#endif