#include "Scene.h"
#include "../Engine/Graphics.h"
#include "../Engine/Input.h"
#include "TitleScene.h"
#include "GameScene.h"
#include "HelpScene.h"
#include "GameOverScene.h"
#include "GameClearScene.h"

static SceneId g_CurrentSceneId = SceneId::TitleScene;		// 動作中シーンID
static SceneStep g_CurrentSceneStep = SceneStep::InitStep;	// 動作中シーンのステップ

SceneId GetCurrentSceneId()
{
	return g_CurrentSceneId;
}

SceneStep GetCurrentSceneStep()
{
	return g_CurrentSceneStep;
}

void ChangeSceneStep(SceneStep next_step)
{
	g_CurrentSceneStep = next_step;
}

void UpdateScene()
{
	UpdateInput();

	SceneId scene_id = g_CurrentSceneId;
	switch (g_CurrentSceneId)
	{
	case SceneId::TitleScene:
		scene_id = UpdateTitleScene();
		break;
	case SceneId::GameScene:
		scene_id = UpdateGameScene();
		break;
	case SceneId::GameClearScene:
		scene_id = UpdateGameClearScene();
		break;
	case SceneId::GameOverScene:
		scene_id = UpdateGameOverScene();
		break;
	case SceneId::HelpScene:
		scene_id = UpdateHelpScene();
		break;
	}

	DrawScene();

	if (scene_id != g_CurrentSceneId)
	{
		g_CurrentSceneId = scene_id;
		ChangeSceneStep(SceneStep::InitStep);
	}
}

void DrawScene()
{
	if (DrawStart() == false)
	{
		return;
	}
	if (g_CurrentSceneStep == SceneStep::MainStep)
	{
		switch (g_CurrentSceneId)
		{
		case SceneId::TitleScene:
			DrawTitleScene();
			break;
		case SceneId::GameScene:
			DrawGameScene();
			break;
		case SceneId::GameClearScene:
			DrawGameClearScene();
			break;
		case SceneId::GameOverScene:
			DrawGameOverScene();
			break;
		case SceneId::HelpScene:
			DrawHelpScene();
			break;
		}
	}

	DrawEnd();
}
