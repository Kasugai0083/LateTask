#pragma once

#include "../../Utility/Vec3.h"
#include "Drawer2D.h"
#include <d3dx9.h>
#include <vector>

/*
	�E�Ȑ��̕`��
	�ȉ��̗�����Q�l�ɋȐ��̕`�������
	�@�D����I�u�W�F�N�g�̍��W�����t���[�����ɕۑ�����
	�A�D�ۑ�����Ă���W�Ǝ��̍��W�Ńx�N�g�����Z�o����
	�B�D�A�̃x�N�g���ɑ΂��Ē��p�ȃx�N�g�����Z�o����
	�C�D�B�̃x�N�g����P�ʃx�N�g���ɂ���
	�D�D���̕� / 2 ���C�̃x�N�g���Ɋ|����
	�E�D�D�̃x�N�g���ɍ��W�𑫂����V�������W�����
	�F�D�D�̃x�N�g����180�x��]����
	�G�D�F�̃x�N�g���ƍ��W�𑫂����V�������W�����
	�H�D�A�`�G���J��Ԃ���TriangleStrip�ŕ`�悷�邽�߂̒��_�̉�����
*/

struct Line
{
	Vec3 m_Pos;
	int m_Counter;
};

struct LineManager 
{
	float m_Width;		// ���̕�
	Vec3 m_Start;		// ���̊J�n�_
	Vec3 m_End;			// ??
	Vec3 m_Center;		// ??
	int m_Timer;		// �X�V
	std::vector<Line>m_Line;	// �ʒu���ƃ^�C�}�[
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