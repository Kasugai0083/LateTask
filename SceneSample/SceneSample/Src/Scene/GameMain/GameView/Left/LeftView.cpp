#include "LeftView.h"
#include "../../../../Lib/Input.h"
#include "../../../../Lib/Graphics.h"

void LeftView::Init() {

	for (auto data : m_GameDatas) {
		/* 初期化　*/

	}
}

GameViewID LeftView::Update() {

	if (GetKeyDown(D_KEY)) {
		return GameViewID::CENTER;
	}
	return GameViewID::LEFT;
}

void LeftView::Draw() {

	Texture room;
	Graphic::CreateTexture("Res/playerroom＿left.png", &room);
	Graphic::DrawTexture(0, 0, &room);

	for (auto data : m_GameDatas) {
		Graphic::DrawTexture(
			data->Pos.X,
			data->Pos.Y,
			data->Tex
		);
	}

}
