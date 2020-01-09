#ifndef DIRECT_GRAPHICS_H_
#define DIRECT_GRAPHICS_H_

#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>

// �ǂݍ��߂�e�N�X�`���̍ő吔
#define MAX_TEXTURE_NUM (100)

// �\���̐錾
typedef struct _VERTEX
{
	D3DXVECTOR3 pos;		// ���W
	D3DXVECTOR2 tex_pos;	// �e�N�X�`�����W
}VERTEX;

typedef struct
{
	LPDIRECT3DTEXTURE9 m_pTexture;
	int m_Width;
	int m_Height;
} TEXTURE_DATA;


/*
	DirectGraphics�̏�����
		�߂�l�F
			�����������F
				true
			���������s�F
				false

		�����F
			HWND window_handle�F
				DirectGraphics�ŕ`�悷��ΏۂƂȂ�E�B���h�E�̃n���h��

		���e�F
			DirectX�̏��������s��
			�K���Q�[�����[�v�̑O��1�x�������s���邱��
			�������DirectGraphics�̂ݏ��������Ă�
*/
bool InitDirectGraphics(HWND window_handle);

/*
	LPDIRECT3DDEVICE9�̃Q�b�^�[
		�߂�l�F
			LPDIRECT3DDEVICE9

		�����F
			�Ȃ�

		���e�F
			LPDIRECT3DDEVICE9�̃Q�b�^�[
*/
const LPDIRECT3DDEVICE9 GetD3DDevice();

/*
	DirectGraphics�̏I��
		�߂�l�F
			�Ȃ�

		�����F
			�Ȃ�

		���e�F
			DirectX���I��������
			�Q�[�����[�v�𔲂�����K���P�x�������s���邱��
*/
void ReleaseDirectGraphics();

/*
	�e�N�X�`���ǂݍ���
		�߂�l�F
			�����F
				�e�N�X�`���ԍ�(0�ȏ�̒l)
			���s�F
				-1
		�����F
			const char * file_name�F
				�t�@�C����

			int use_id�F
				�e�N�X�`���ԍ��̎w��
				�L���ԍ����w�肵���ꍇ�͂��̔ԍ��œǂݍ��݂�����������
				�������ԍ��œǂݍ��܂�Ă���t�@�C��������΂�����͉������̂Œ���

		���e�F
			�w�肳�ꂽ�e�N�X�`����ǂݍ���
			����������e�N�X�`���ԍ����Ԃ�A���s������-1���Ԃ�
*/
int LoadTexture(const char *file_name, int use_id = -1);

/*
	�e�N�X�`���̉��
		�߂�l�F
			�Ȃ�

		�����F
			int texture_id�F
				�e�N�X�`���ԍ�

		���e�F
			�����Ŏw�肵���e�N�X�`�����������
*/
void ReleaseTexture(int texture_id);

/*
	�`��J�n
		�߂�l�F
			�Ȃ�

		�����F
			�Ȃ�

		���e�F
			�`�揈�����J�n���邽�߂̊֐�
			�`�揈���͂��̊֐����Ăяo������ɍs������
*/
void DrawStart();

/*
	�`��I��
		�߂�l�F
			�Ȃ�

		�����F
			�Ȃ�

		���e�F
			�`�揈���I���֐�
			�`����e����ʂɔ��f����ɂ͂��̊֐����Ăяo���K�v������
*/
void DrawEnd();

/*
	�e�N�X�`���̎g�p�۔���
		�߂�l�F
			true => �e�N�X�`���g�p�\
			false => �e�N�X�`���g�p�s��

		�����F
			int tex_id
				�g�p�ۂ��m�F�������e�N�X�`���ԍ�

		���e�F
			�w�肳�ꂽ�e�N�X�`���ԍ����g�p�\���ǂ����𔻒肷��
*/
bool IsUseTexture(int tex_id);

/*
	�e�N�X�`���f�[�^�̃Q�b�^�[
		�߂�l�F
			�e�N�X�`���f�[�^�̃|�C���^

		�����F
			�擾�������e�N�X�`���̔ԍ�

		���e�F
			�e�N�X�`���f�[�^�̃Q�b�^�[
*/
const TEXTURE_DATA *GetTextureData(int texture_id);

/*
	�r���[�}�g���b�N�X�̋t�s��擾

		�߂�l�F
			�Ȃ�

		�����F
			D3DXMATRIX *out
				�t�s��i�[�p�̃}�g���b�N�X�̃|�C���^

		���e�F
			�r���[�}�g���b�N�X�̋t�s����擾����
*/
void InverseViewMatrix(D3DXMATRIX *out);

/*
	���W�ϊ�
		�߂�l�F
			�Ȃ�

		�����F
			const D3DXVECTOR3 *camera_pos

			const D3DXVECTOR3 *eye_pos

		���e�F
			�r���[�}�g���b�N�X�ƃv���W�F�N�V�����}�g���b�N�X��
			�쐬����SetTransform�Őݒ肷��
*/
void Transform(const D3DXVECTOR3 *camera_pos, const D3DXVECTOR3 *eye_pos);

#endif
