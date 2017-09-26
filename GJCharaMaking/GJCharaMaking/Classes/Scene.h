/* =====================================================================
//! @param		�uScene�vclass header
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
	// �V�[���̎��
	enum SCENE
	{
		CUSTOMIZE = 0,
		PLAY
	};

private:
	SCENE sceneDirector_;				// �V�[���Ǘ�

public:
	Scene();
	virtual ~Scene() {};

	virtual void Update() = 0;			// update
	virtual void Draw() = 0;			// draw

	virtual void ChangeScene(Scene::SCENE scene);		// �V�[���؂�ւ�
};