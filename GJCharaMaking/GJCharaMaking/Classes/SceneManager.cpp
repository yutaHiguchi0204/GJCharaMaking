/* =====================================================================
//! @param		「SceneManager」class src
//! @create		Yuta Higuchi
//! @date		17/09/26
===================================================================== */

// including header
#include "SceneManager.h"
#include <cassert>
#include "CustomizeScene.h"
#include "PlayScene.h"

// namespace
using namespace std;

// method

// constructor
SceneManager::SceneManager()
{
	scene_ = make_unique<CustomizeScene>();
}

// =================================================
// @brief	update
// @param	none
// @return	none
// =================================================
void SceneManager::Update()
{
	scene_->Update();
}

// =================================================
// @brief	draw
// @param	none
// @return	none
// =================================================
void SceneManager::Draw()
{
	scene_->Draw();
}

// =================================================
// @brief	シーン切り替え
// @param	シーン（SCENE）
// @return	none
// =================================================
void SceneManager::ChangeScene(Scene::SCENE scene)
{
	// シーン切り替え
	switch (scene)
	{
	case Scene::CUSTOMIZE:
		scene_ = make_unique<CustomizeScene>();
		break;

	case Scene::PLAY:
		scene_ = make_unique<PlayScene>();
		break;

	default:
		OutputDebugString(L"This scene is unknown.");
		assert(0);
		break;
	}
}