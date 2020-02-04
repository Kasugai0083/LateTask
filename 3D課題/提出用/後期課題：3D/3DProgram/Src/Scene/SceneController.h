#pragma once

#include "SceneBase.h"
#include "../Utility/SingletonTemplate.h"
#include <vector>

class SceneController : public Singleton<SceneController> {
public:
	void Init(SceneID id);

	void Update();

	void Draw();

	void ChanegeScene(SceneID id);

	void Release();
private:
	std::vector<SceneBase*> m_SceneList;
	SceneBase* m_CurrScene;
	SceneID m_SceneID;
private:
	friend Singleton<SceneController>;

	SceneController() {};
	virtual ~SceneController() {};

	SceneController(const SceneController&) = delete;
	SceneController& operator=(const SceneController&) = delete;
	SceneController(const SceneController&&) = delete;
	SceneController& operator=(const SceneController&&) = delete;

};