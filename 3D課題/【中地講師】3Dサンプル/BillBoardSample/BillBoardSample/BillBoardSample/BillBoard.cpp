#include "Lib.h"
#include "BillBoard.h"

extern int g_TextureList[];

static D3DXVECTOR3 g_BillBoardPos;		// ���W
static int g_BillBoardTextureId = 0;	// �e�N�X�`���ԍ�
static D3DXVECTOR2 g_TexturePos;		// �e�N�X�`�����W
static D3DXVECTOR2 g_TextureSize;		// �e�N�X�`���T�C�Y

const D3DXVECTOR3 *GetBillBoardPosPointer()
{
	return &g_BillBoardPos;
}

void InitBillBoard()
{
	g_BillBoardTextureId = LoadTexture("sample.png");
	g_BillBoardPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_TexturePos = D3DXVECTOR2(0.0f, 0.0f);
	g_TextureSize = D3DXVECTOR2(128.0f, 128.0f);
}

void ReleaseBillBoard()
{
	ReleaseTexture(g_BillBoardTextureId);
}

void DrawBillBoard()
{
	D3DXMATRIX view_mat, world, trans;

	D3DXMatrixIdentity(&world);
	D3DXMatrixIdentity(&trans);
	D3DXMatrixIdentity(&view_mat);
	
	// �A�D�I�u�W�F�N�g�̍s����쐬����
	// �ړ�
	D3DXMatrixTranslation(&trans, g_BillBoardPos.x, g_BillBoardPos.y, g_BillBoardPos.z);

	// �B�D�J�����̃r���[�s��̋t�s����쐬����
	// �r���[�}�g���b�N�X�̋t�s��쐬
	InverseViewMatrix(&view_mat);

	// �C�D�t�s��̈ړ��l��ł�����
	// �ړ����̑ł�����
	view_mat._41 = 0.0f;
	view_mat._42 = 0.0f;
	view_mat._43 = 0.0f;

	// �D�D�s����|�����킹��
	// ���[���h���W�쐬
	world = view_mat * trans;

	// �E�D�s��̐ݒ�
	// ���[���h���W�̐ݒ�
	GetD3DDevice()->SetTransform(D3DTS_WORLD, &world);

	// �ȉ��|���̕`��
	float left_tu = 0.0f;
	float right_tu = 1.0f;
	float top_tv = 0.0f;
	float bottom_tv = 1.0f;
	const TEXTURE_DATA *texture_data = GetTextureData(g_BillBoardTextureId);

	if (texture_data->m_pTexture != NULL)
	{
		left_tu = g_TexturePos.x / texture_data->m_Width;
		right_tu = (g_TexturePos.x + g_TextureSize.x) / texture_data->m_Width;
		top_tv = g_TexturePos.y / texture_data->m_Height;
		bottom_tv = (g_TexturePos.y + g_TextureSize.y) / texture_data->m_Height;
	}

	float harf_x = texture_data->m_Width / 2.0f;
	float harf_y = texture_data->m_Height / 2.0f;

	// �O�p�`��`��
	VERTEX v[4] = 
	{
		{ D3DXVECTOR3(-harf_x, harf_y, 0.0f), D3DXVECTOR2(left_tu, top_tv) },
		{ D3DXVECTOR3(harf_x, harf_y, 0.0f), D3DXVECTOR2(right_tu, top_tv) },
		{ D3DXVECTOR3(harf_x, -harf_y, 0.0f), D3DXVECTOR2(right_tu, bottom_tv) },
		{ D3DXVECTOR3(-harf_x, -harf_y, 0.0f), D3DXVECTOR2(left_tu, bottom_tv) },
	};

	// �@����ݒ肵�Ă��Ȃ��̂Ń��C�e�B���O�͂Ȃ�
	GetD3DDevice()->SetRenderState( D3DRS_LIGHTING, FALSE );	// RHW�Ŗ������_��LIGHT�������̂Ŗ����ɂ��Ă���
	GetD3DDevice()->SetRenderState( D3DRS_CULLMODE, D3DCULL_CCW );	

	// �F�D�|���`��
	// ���_�\���̎w��
	GetD3DDevice()->SetFVF(D3DFVF_XYZ | D3DFVF_TEX1);
	GetD3DDevice()->SetTexture(0, texture_data->m_pTexture);
	GetD3DDevice()->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, v, sizeof(VERTEX));

}

// ��r�p
void DrawNotBillBoard()
{
	D3DXMATRIXA16 world, trans;

	D3DXMatrixIdentity(&world);
	D3DXMatrixIdentity(&trans);
	
	// �ړ�
	D3DXMatrixTranslation(&trans, g_BillBoardPos.x, g_BillBoardPos.y + 150.0f, g_BillBoardPos.z);
	world = trans;

	GetD3DDevice()->SetTransform(D3DTS_WORLD, &world);

	/////////////////////////////////////////////////////
	float left_tu = 0.0f;
	float right_tu = 1.0f;
	float top_tv = 0.0f;
	float bottom_tv = 1.0f;
	const TEXTURE_DATA *texture_data = GetTextureData(g_BillBoardTextureId);

	if (texture_data->m_pTexture != NULL)
	{
		left_tu = g_TexturePos.x / texture_data->m_Width;
		right_tu = (g_TexturePos.x + g_TextureSize.x) / texture_data->m_Width;
		top_tv = g_TexturePos.y / texture_data->m_Height;
		bottom_tv = (g_TexturePos.y + g_TextureSize.y) / texture_data->m_Height;
	}

	float harf_x = texture_data->m_Width / 2.0f;
	float harf_y = texture_data->m_Height / 2.0f;

	// �O�p�`��`�� start
	VERTEX v[4] = 
	{
		{ D3DXVECTOR3(-harf_x, harf_y, 0.0f), D3DXVECTOR2(left_tu, top_tv) },
		{ D3DXVECTOR3(harf_x, harf_y, 0.0f), D3DXVECTOR2(right_tu, top_tv) },
		{ D3DXVECTOR3(harf_x, -harf_y, 0.0f), D3DXVECTOR2(right_tu, bottom_tv) },
		{ D3DXVECTOR3(-harf_x, -harf_y, 0.0f), D3DXVECTOR2(left_tu, bottom_tv) },
	};

	GetD3DDevice()->SetRenderState( D3DRS_LIGHTING, FALSE ); // RHW�Ŗ������_��LIGHT�������̂Ŗ����ɂ��Ă���

	// ���_�\���̎w��
	GetD3DDevice()->SetFVF(D3DFVF_XYZ | D3DFVF_TEX1);
	GetD3DDevice()->SetTexture(0, texture_data->m_pTexture);
	GetD3DDevice()->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, v, sizeof(VERTEX));
}