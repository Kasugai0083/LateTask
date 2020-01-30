#pragma once

#include "../../Utility/Vec3.h"
#include "Drawer2D.h"
#include <d3dx9.h>
#include <vector>

struct Line
{
	Vec3 m_Pos;
	int m_Counter;
};

struct LineManager 
{
	float m_Width;
	Vec3 m_Start;
	Vec3 m_End;
	Vec3 m_Center;
	int m_Timer;
	std::vector<Line>m_Line;
};

struct LineDesc 
{
	Vec3 m_Pos;
	float m_Alpha;
};

class LineDrawer {
public:
	LineDrawer()
	{
		//m_LineManager.m_Start = start_;
		//m_LineManager.m_End = end_;

	}

	void InitLine(Vec3 start, Vec3 end);

	void UpdateLineManager();

	void DrawLine();

private:
	void UpdateLine();

private:

	LineManager m_LineManager;

	std::vector<Vec3> m_Lines;

	Drawer2D drawer;

};