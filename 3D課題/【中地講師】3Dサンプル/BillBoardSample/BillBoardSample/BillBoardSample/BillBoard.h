#ifndef BILL_BOARD_H_
#define BILL_BOARD_H_

/**
* @brief ビルボード座標の取得関数
* @return ビルボード座標
*/
const D3DXVECTOR3* GetBillBoardPosPointer();

/**
* @brief ビルボードの初期化関数
* @details 今回のビルボード処理に必要な変数の初期化
*/
void InitBillBoard();

/**
* @brief ビルボード解放関数
* @details ビルボードに使用しているリソースの解放を行う
*/
void ReleaseBillBoard();

/**
* @brief ビルボード描画関数
*/
void DrawBillBoard();

/**
* @brief 比較用板ポリ描画関数
* @details ビルボード処理を行っていない比較用の板ポリを描画する
*/
void DrawNotBillBoard();

#endif
