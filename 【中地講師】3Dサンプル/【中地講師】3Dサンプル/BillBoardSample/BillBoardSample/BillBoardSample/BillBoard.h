#ifndef BILL_BOARD_H_
#define BILL_BOARD_H_

/**
* @brief �r���{�[�h���W�̎擾�֐�
* @return �r���{�[�h���W
*/
const D3DXVECTOR3* GetBillBoardPosPointer();

/**
* @brief �r���{�[�h�̏������֐�
* @details ����̃r���{�[�h�����ɕK�v�ȕϐ��̏�����
*/
void InitBillBoard();

/**
* @brief �r���{�[�h����֐�
* @details �r���{�[�h�Ɏg�p���Ă��郊�\�[�X�̉�����s��
*/
void ReleaseBillBoard();

/**
* @brief �r���{�[�h�`��֐�
*/
void DrawBillBoard();

/**
* @brief ��r�p�|���`��֐�
* @details �r���{�[�h�������s���Ă��Ȃ���r�p�̔|����`�悷��
*/
void DrawNotBillBoard();

#endif
