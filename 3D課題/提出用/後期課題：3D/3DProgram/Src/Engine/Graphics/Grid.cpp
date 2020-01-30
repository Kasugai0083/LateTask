#include "Grid.h"
#include "Drawer2D.h"

void LineDrawer::InitLine(Vec3 start, Vec3 end) {
	m_LineManager.m_Width = 10.0f;
	m_LineManager.m_Line.clear();
	m_LineManager.m_Start = start;
	m_LineManager.m_End = end;
	m_LineManager.m_Center = Vec3(5, 5, 5);
	m_LineManager.m_Timer = 0;

	Line line =
	{
		m_LineManager.m_Start,
		120,
	};
	m_LineManager.m_Line.push_back(line);
}

void LineDrawer::UpdateLine() {
	for (auto& line : m_LineManager.m_Line)
	{
		line.m_Counter -= 0;
	}
}

void LineDrawer::UpdateLineManager() {
	m_LineManager.m_Timer++;

	if (m_LineManager.m_Timer % 6 == 0)
	{
		Vec3 new_pos;
		float percent = m_LineManager.m_Timer / 60.0f;

		new_pos.X = (1 - percent) * (1 - percent) * m_LineManager.m_Start.X + 2 * (1 - percent) * percent * m_LineManager.m_Center.X + percent * percent * m_LineManager.m_End.X;
		new_pos.Y = (1 - percent) * (1 - percent) * m_LineManager.m_Start.Y + 2 * (1 - percent) * percent * m_LineManager.m_Center.Y + percent * percent * m_LineManager.m_End.Y;

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

	for (int i = 0; i < m_LineManager.m_Line.size() - 1; i++)
	{
		Vec3 direction = Vec3(
			m_LineManager.m_Line[i + 1].m_Pos.X - m_LineManager.m_Line[i].m_Pos.X,
			m_LineManager.m_Line[i + 1].m_Pos.Y - m_LineManager.m_Line[i].m_Pos.Y,
			m_LineManager.m_Line[i + 1].m_Pos.Z - m_LineManager.m_Line[i].m_Pos.Z);

		for (int j = 0; j < 2; j++)
		{
			Vec3 normal = Vec3(-direction.Y, direction.X, direction.Z);

			if (j == 1)
			{
				normal.X *= -1.0f;
				normal.Y *= -1.0f;
				normal.Z *= -1.0f;
			}

			float length = sqrtf(normal.X * normal.X + normal.Y * normal.Y+ normal.Z * normal.Z);
			normal.X /= length;
			normal.Y /= length;
			normal.Z /= length;

			Vec3 new_pos = Vec3(direction.X + m_LineManager.m_Width / 2.0f * normal.X,
				direction.Y + m_LineManager.m_Width / 2.0f * normal.Y,
				direction.Z + m_LineManager.m_Width / 2.0f * normal.Z);

			new_pos.X += m_LineManager.m_Line[i].m_Pos.X;
			new_pos.Y += m_LineManager.m_Line[i].m_Pos.Y;
			new_pos.Z += m_LineManager.m_Line[i].m_Pos.Z;

			float alpha = (float)m_LineManager.m_Line[i].m_Counter / 120.0f;
			LineDesc new_desc =
			{
				new_pos,
				//”äŠr	   //^‚Ìê‡:‹U‚Ìê‡
				alpha > 0.0f ? alpha : 0.0f
			};

			desc_list.push_back(new_desc);
		}
	}

	drawer.DrawLine(desc_list);

}