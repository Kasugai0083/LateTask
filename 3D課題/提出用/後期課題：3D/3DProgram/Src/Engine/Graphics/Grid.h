#pragma once

#include "../../Utility/Vec3.h"
#include "Drawer2D.h"
#include <d3dx9.h>
#include <vector>

/*
	・曲線の描画
	以下の流れを参考に曲線の描画をする
	①．あるオブジェクトの座標を一定フレーム毎に保存する
	②．保存されてる座標と次の座標でベクトルを算出する
	③．②のベクトルに対して直角なベクトルを算出する
	④．③のベクトルを単位ベクトルにする
	⑤．線の幅 / 2 を④のベクトルに掛ける
	⑥．⑤のベクトルに座標を足した新しい座標を作る
	⑦．⑤のベクトルを180度回転する
	⑧．⑦のベクトルと座標を足した新しい座標を作る
	⑨．②～⑧を繰り返してTriangleStripで描画するための頂点の塊を作る
*/

struct Line
{
	Vec3 m_Pos;
	int m_Counter;
};

struct LineManager 
{
	float m_Width;		// 線の幅
	Vec3 m_Start;		// 線の開始点
	Vec3 m_End;			// ??
	Vec3 m_Center;		// ??
	int m_Timer;		// 更新
	std::vector<Line>m_Line;	// 位置情報とタイマー
};

struct LineDesc 
{
	Vec3 m_Pos;
	float m_Alpha;
};

class LineDrawer {
public:
	LineDrawer(Vec3 start, Vec3 end)
	{
		m_LineManager.m_Width = 10.0f;
		m_LineManager.m_Line.clear();
		m_LineManager.m_Start = start;
		m_LineManager.m_End = end;
		m_LineManager.m_Center = Vec3(0.f, 0.f, 0.f);
		m_LineManager.m_Timer = 0;

		Line line =
		{
			m_LineManager.m_Start,
			120,
		};
		m_LineManager.m_Line.push_back(line);
	}

	void UpdateLineManager();

	void DrawLine();

private:
	void UpdateLine();

private:

	LineManager m_LineManager;

	std::vector<Vec3> m_Lines;

	Drawer2D drawer;

};