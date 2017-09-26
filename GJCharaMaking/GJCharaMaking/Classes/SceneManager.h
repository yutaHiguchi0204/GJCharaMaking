/* =====================================================================
//! @param		「SceneManager」class header
//! @create		Yuta Higuchi
//! @date		17/09/26
===================================================================== */
#pragma once

// including header
#include "SingletonDirector.h"
#include <CommonStates.h>
#include "Scene.h"

// class
class SceneManager : public SingletonDirector<SceneManager>
{
private:
	std::unique_ptr<Scene> scene_;		// シーン

private:
	friend class SingletonDirector<SceneManager>;

	// constructor
	SceneManager();

public:
	void Update();								// update
	void Draw();								// draw

	void ChangeScene(Scene::SCENE scene);		// シーン切り替え
};