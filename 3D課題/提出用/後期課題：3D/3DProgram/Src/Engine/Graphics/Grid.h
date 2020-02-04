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

/**
* @brief 
* 曲線の情報を管理
*/

/**
* 線の座標と経過フレームを保存
*/
struct Line
{
	Vec3 m_Pos;
	int m_Counter;
};

/**
* @brief 線のステータスを管理
* @param m_Width	線の幅
* @param m_Start	線の開始点
* @param m_End		線の終点？
* @param m_Center	線の中間点？
* @param m_Timer	経過フレームを保存
* @param m_Line		位置情報とタイマー
*/
struct LineManager 
{
	float m_Width;				
	Vec3 m_Start;				
	Vec3 m_End;					
	Vec3 m_Center;				
	int m_Timer;				
	std::vector<Line>m_Line;	
};

/**
* @brief 線の位置情報と色彩濃度を保存
*/
struct LineDesc 
{
	Vec3 m_Pos;
	float m_Alpha;
};

class LineDrawer {
public:

	/**
	* @brief コンストラクタ
	* @param start	線の開始点
	* @param center 線の中間点
	* @param end	線の終点
	*/
	LineDrawer(Vec3 start, Vec3 center,Vec3 end)
	{
		// 10.f でしか描画されない
		// 訂正：Widthを上げるとどんどん高い位置で描画される
		// 原因を探る
		// ⑤で Width の値の半分を乗算しているため、位置ずれが起きていると思われる
		m_LineManager.m_Width = 20.0f;
		m_LineManager.m_Line.clear();
		m_LineManager.m_Start = start;
		m_LineManager.m_End = end;
		m_LineManager.m_Center = center;
		m_LineManager.m_Timer = 0;

		Line line =
		{
			m_LineManager.m_Start,
			120,
		};
		m_LineManager.m_Line.push_back(line);
	}

	/**
	* @brief ６フレーム毎に次の線情報を作成する
	*/
	void UpdateLineManager();

	/**
	* @brief 曲線の描画
	*/
	void DrawLine();

private:
	void UpdateLine(); 	//!< @brief m_Counter を減算する

private:
	LineManager m_LineManager;	//!< @brief 曲線の情報を管理

	Drawer2D m_Drawer;			//!< @brief 描画関数を呼び出すために使用

};