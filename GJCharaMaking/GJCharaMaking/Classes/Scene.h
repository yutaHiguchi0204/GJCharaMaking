/* =====================================================================
//! @param		「Scene」class header
//! @create		Yuta Higuchi
//! @date		17/09/26
===================================================================== */
#pragma once

// including header
#include "SingletonDirector.h"

// class
class Scene
{
public:
	// シーンの種類
	enum SCENE
	{
		CUSTOMIZE = 0,
		PLAY
	};

private:
	SCENE sceneDirector_;				// シーン管理

public:
	Scene();
	virtual ~Scene() {};

	virtual void Update() = 0;			// update
	virtual void Draw() = 0;			// draw

	virtual void ChangeScene(Scene::SCENE scene);		// シーン切り替え
};