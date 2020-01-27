#pragma once

#include "SceneBase.h"
#include <vector>

class SceneController {

public:
	
	static SceneController* GetInstance() {
		static SceneController instance;
		return &instance;
	}

	void Init(SceneID id);

	void Update();

	void Draw();

	void ChangeScene(SceneID id);

	void Release();

private:
	std::vector<SceneBase*> m_SceneList;
	SceneBase* m_CurrScene;
	SceneID m_SceneID;

};
