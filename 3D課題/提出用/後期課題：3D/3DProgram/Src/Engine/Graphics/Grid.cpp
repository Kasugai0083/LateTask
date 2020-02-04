#include "Grid.h"
#include "Drawer2D.h"

// m_Counter を減算する
void LineDrawer::UpdateLine() {
	for (auto& line : m_LineManager.m_Line)
	{
		line.m_Counter -= 0;
	}
}

void LineDrawer::UpdateLineManager() {
	// m_Timer を加算
	m_LineManager.m_Timer++;

	// 6 flame 後、行われる処理
	if (m_LineManager.m_Timer % 6 == 0)
	{
		Vec3 new_pos;

		// persent <= こいつは何？
		// 毎フレーム加算される Timer に 1秒 => 60フレームが割られている
		// persent は時間に関わる割合であると予測できる
		// persent の値を変更すると =>
		// 曲線の描画速度があがる + 座標が変わる(問題！)
		float percent = m_LineManager.m_Timer / 15.0f;

		// 仮説①：始点と中間点、終点を結ぶ曲線の計算をしている
		// 仮説②：ブレンドする値は始点・中間点・終点といった関わりではなく、
		//		   曲線の曲がり具合を設定するものである
		new_pos.X = 
			(1 - percent) 
			* (1 - percent) 
			* m_LineManager.m_Start.X + 2 
			* (1 - percent) 
			* percent 
			* m_LineManager.m_Center.X + percent 
			* percent 
			* m_LineManager.m_End.X;

		new_pos.Y = 
			(1 - percent) 
			* (1 - percent) 
			* m_LineManager.m_Start.Y + 2 
			* (1 - percent) * percent 
			* m_LineManager.m_Center.Y + percent 
			* percent 
			* m_LineManager.m_End.Y;

		new_pos.Z = 
			(1 - percent) 
			* (1 - percent) 
			* m_LineManager.m_Start.Z + 2 
			* (1 - percent) * percent 
			* m_LineManager.m_Center.Z + percent 
			* percent 
			* m_LineManager.m_End.Z;

		Line new_line =
		{
			new_pos,
			120,
		};
		m_LineManager.m_Line.push_back(new_line);
	}

	UpdateLine();
}

void LineDrawer::DrawLine() {
	if (m_LineManager.m_Line.size() <= 2)
	{
		return;
	}

	std::vector<LineDesc> desc_list;

	for (int i = 0; i < (int)m_LineManager.m_Line.size() - 1; i++)
	{
		Vec3 direction = Vec3(
			// ②.保存されてる座標と次の座標でベクトルを算出する
			m_LineManager.m_Line[i + 1].m_Pos.X - m_LineManager.m_Line[i].m_Pos.X,
			m_LineManager.m_Line[i + 1].m_Pos.Y - m_LineManager.m_Line[i].m_Pos.Y,
			m_LineManager.m_Line[i + 1].m_Pos.Z - m_LineManager.m_Line[i].m_Pos.Z
		);


		// ⑧．⑦のベクトルと座標を足した新しい座標を作る
		for (int j = 0; j < 2; j++)
		{
			// 	③．②のベクトルに対して直角なベクトルを算出する
			Vec3 normal = Vec3(-direction.Y, direction.X, direction.Z);

			if (j == 1)
			{
				// ベクトルu と ベクトルv を算出
				// ⑦．⑤のベクトルを180度回転する
				normal.X *= -1.0f;
				normal.Y *= -1.0f;
				normal.Z *= 1.0f;
			}

			//	④．③のベクトルを単位ベクトルにする
			float length = sqrtf(normal.X * normal.X + normal.Y * normal.Y+ normal.Z * normal.Z);
			normal.X /= length;
			normal.Y /= length;
			normal.Z /= length;

			// ⑤．線の幅 / 2 を④のベクトルに掛ける
			Vec3 new_pos = Vec3(
				direction.X + m_LineManager.m_Width / 2.0f * normal.X,
				direction.Y + m_LineManager.m_Width / 2.0f * normal.Y,
				direction.Z + m_LineManager.m_Width / 2.0f * normal.Z
			);

			// 	⑥．⑤のベクトルに座標を足した新しい座標を作る
			new_pos.X += m_LineManager.m_Line[i].m_Pos.X;
			new_pos.Y += m_LineManager.m_Line[i].m_Pos.Y;
			new_pos.Z += m_LineManager.m_Line[i].m_Pos.Z;

			// alpha 色の濃度
			float alpha = (float)m_LineManager.m_Line[i].m_Counter / 120.0f;
			LineDesc new_desc =
			{
				new_pos,

				// 比較	   // 真の場合:偽の場合
				// alphaが負の数の場合 0 を返す
				alpha > 0.0f ? alpha : 0.0f
			};

			desc_list.push_back(new_desc);
		}
	}

	m_Drawer.DrawLine(desc_list);

}