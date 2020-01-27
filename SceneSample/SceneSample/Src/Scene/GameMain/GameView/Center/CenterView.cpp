#include "CenterView.h"
#include "../../../../Lib/Input.h"
#include "../../../../Lib/Graphics.h"

void CenterView::Init() {

	for (auto data : m_GameDatas) {
		/* 初期化　*/
		
	}
}

GameViewID CenterView::Update() {

	if (GetKeyDown(D_KEY)) {
		return GameViewID::RIGHT;
	}
	if (GetKeyDown(A_KEY)) {
		return GameViewID::LEFT;
	}
	return GameViewID::CENTER;
}

void CenterView::Draw() {
	
	Texture room;
	Graphic::CreateTexture("Res/playerroom＿center.png", &room);
	Graphic::DrawTexture(0, 0, &room);

	Texture right_tex;
	Graphic::CreateTexture("Res/candle＿effect＿center.png", &right_tex);
	Graphic::DrawTexture(0, 0, &right_tex);

	for (auto data : m_GameDatas) {
		Graphic::DrawTexture(
			data->Pos.X,
			data->Pos.Y,
			data->Tex
		);
	}

}
