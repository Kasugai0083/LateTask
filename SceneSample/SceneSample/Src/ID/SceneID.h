#pragma once

//===========================
//　シーン識別子
//===========================
enum  class SceneID
{
	TITLE,
	GAME,
	RESULT,
	UNKNOWN,
};

//============================
// シーン状態識別子
//============================
enum class SceneState {

	INIT,
	UPDATE,
	END,
	UNKNOWN,
};