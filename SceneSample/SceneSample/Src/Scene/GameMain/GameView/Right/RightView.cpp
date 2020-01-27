#include "RightView.h"
#include "../../../../Lib/Input.h"
#include "../../../../Lib/Graphics.h"

void RightView::Init() {

	for (auto data : m_GameDatas) {
		/* 初期化　*/

	}
}

GameViewID RightView::Update() {

	if (GetKeyDown(A_KEY)) {
		return GameViewID::CENTER;
	}
	return GameViewID::RIGHT;
}

void RightView::Draw() {

	Texture room;
	Graphic::CreateTexture("Res/playerroom＿right.png", &room);
	Graphic::DrawTexture(0, 0, &room);

	for (auto data : m_GameDatas) {
		Graphic::DrawTexture(
			data->Pos.X,
			data->Pos.Y,
			data->Tex
		);
	}

}
