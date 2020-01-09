#include "../Engine/Graphics.h"
#include "../Engine/Input.h"
#include "../Texture/Texture.h"
#include "TitleScene.h"

// タイトルシーンの初期化
void InitTitleScene();
// タイトルシーンのメイン処理
void MainTitleScene();
// タイトルシーンの終了
SceneId FinishTitleScene();

SceneId UpdateTitleScene()
{
	switch (GetCurrentSceneStep())
	{
	case SceneStep::InitStep:
		InitTitleScene();
		break;
	case SceneStep::MainStep:
		MainTitleScene();
		break;
	case SceneStep::EndStep:
		return FinishTitleScene();
		break;
	}

	return SceneId::TitleScene;
}

void DrawTitleScene()
{
	///*
	//* @param[in] 取得したいテクスチャのカテゴリ
	//* @param[in] 取得したいテクスチャのID
	//*/
	//Texture* texture = GetTexture(TEXTURE_CATEGORY_TITLE, TitleCategoryTextureList::TitleBgTex);

	/*
	* @param[in] x X軸描画座標
	* @param[in] y Y軸描画座標
	* @param[in] texture_data 描画で使用するテクスチャのデータ
	*/
	DrawTexture(0.0f, 0.0f, GetTexture(TEXTURE_CATEGORY_TITLE, TitleCategoryTextureList::TitleBgTex));

}

void InitTitleScene()
{
	LoadTexture("Res/TitleBg.png", TEXTURE_CATEGORY_TITLE, TitleCategoryTextureList::TitleBgTex);
	LoadTexture("Res/TitleMenuStart.png", TEXTURE_CATEGORY_TITLE, TitleCategoryTextureList::TitleMenuGoGameTex);
	LoadTexture("Res/TitleMenuHelp.png", TEXTURE_CATEGORY_TITLE, TitleCategoryTextureList::TitleMenuGoHelpTex);

	ChangeSceneStep(SceneStep::MainStep);
}

void MainTitleScene()
{

}

SceneId FinishTitleScene()
{
	// リリース解放
	ReleaseCategoryTexture(SceneId::TitleScene);

	// 次のシーンIDを返す
	return SceneId::GameScene;
}

