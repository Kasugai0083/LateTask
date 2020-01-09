#include <Windows.h>
#include <vector>
#include <math.h>
#include "Engine/Engine.h"
#include "Engine/Window.h"
#include "Engine/Input.h"
#include "Engine/Texture.h"
#include "Utility/Size.h"
#include "Utility/RectF.h"
#include "Utility/Vec.h"
#include "Engine/Graphics.h"
#include "Grid.h"

struct Line
{
	Vec2 m_Pos;
	int m_Counter;
};

struct LineManager
{
	float m_Width;
	Vec2 m_Start;
	Vec2 m_End;
	Vec2 m_Center;
	int m_Timer;
	std::vector<Line> m_Line;
};

LineManager g_LineManager;

void InitLine(Vec2 start, Vec2 end)
{
	g_LineManager.m_Width = 5.0f;
	g_LineManager.m_Line.clear();
	g_LineManager.m_Start = start;
	g_LineManager.m_End = end;
	g_LineManager.m_Center = Vec2(100, 100);
	g_LineManager.m_Timer = 0;

	Line line =
	{
		g_LineManager.m_Start,
		120,
	};
	g_LineManager.m_Line.push_back(line);
}

void UpdateLine()
{
	for (auto& line : g_LineManager.m_Line)
	{
		line.m_Counter--;
	}
}


void UpdateLineManager()
{
	g_LineManager.m_Timer++;

	if (g_LineManager.m_Timer % 6 == 0)
	{
		Vec2 new_pos;
		float percent = g_LineManager.m_Timer / 60.0f;

		new_pos.X = (1 - percent) * (1 - percent) * g_LineManager.m_Start.X + 2 * (1 - percent) * percent * g_LineManager.m_Center.X + percent * percent * g_LineManager.m_End.X;
		new_pos.Y = (1 - percent) * (1 - percent) * g_LineManager.m_Start.Y + 2 * (1 - percent) * percent * g_LineManager.m_Center.Y + percent * percent * g_LineManager.m_End.Y;

		Line new_line =
		{
			new_pos,
			120,
		};
		g_LineManager.m_Line.push_back(new_line);
	}

	UpdateLine();
}

void DrawLine()
{
	if (g_LineManager.m_Line.size() <= 2)
	{
		return;
	}

	std::vector<LineDesc> desc_list;

	for (int i = 0; i < g_LineManager.m_Line.size() - 1; i++)
	{
		Vec2 direction = Vec2(
			g_LineManager.m_Line[i + 1].m_Pos.X - g_LineManager.m_Line[i].m_Pos.X,
			g_LineManager.m_Line[i + 1].m_Pos.Y - g_LineManager.m_Line[i].m_Pos.Y);

		float percent = g_LineManager.m_Line[i].m_Counter / 120.0f;

		if (percent <= 0.0f)
		{
			percent = 0.0f;
		}

		for (int j = 0; j < 2; j++)
		{
			Vec2 normal = Vec2(-direction.Y, direction.X);

			if (j == 1)
			{
				normal.X *= -1.0f;
				normal.Y *= -1.0f;
			}

			float length = sqrtf(normal.X * normal.X + normal.Y * normal.Y);
			normal.X /= length;
			normal.Y /= length;

			Vec2 new_pos = Vec2(direction.X + g_LineManager.m_Width / 2.0f * normal.X,
				direction.Y + g_LineManager.m_Width / 2.0f * normal.Y);

			new_pos.X += g_LineManager.m_Line[i].m_Pos.X;
			new_pos.Y += g_LineManager.m_Line[i].m_Pos.Y;

			float alpha = (float)g_LineManager.m_Line[i].m_Counter / 120.0f;
			LineDesc new_desc =
			{
				new_pos,
				alpha > 0.0f ? alpha : 0.0f
			};

			desc_list.push_back(new_desc);
		}
	}

	DrawLine(desc_list);
}

int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR     lpCmpLine,
	INT       nCmdShow)
{
	// エンジンの初期化
	if (InitEngine(WINDOW_WIDTH, WINDOW_HEIGHT, "レーザー") == false)
	{
		return 0;
	}

	int frame = 0;

	InitLine(Vec2(0.0f, 200.0f), Vec2(200.0f, 200.0f));

	while (true)
	{
		bool message_ret = false;
		MSG msg;

		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				break;
			}
			else 
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			UpdateLineManager();

			std::vector<Vec2> lines;
			lines.push_back(Vec2(100.0f, 100.0f));
			lines.push_back(Vec2(200.0f, 100.0f));
			lines.push_back(Vec2(200.0f, 200.0f));

			DrawStart();
			
			//引数なしで曲線描画
			DrawLine();
			//DrawLine(lines, 0xffff0000);

			DrawEnd();
		}
	}

	// エンジン終了
	EndEngine();

	return 0;
}

