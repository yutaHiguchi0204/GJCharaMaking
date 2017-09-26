/* =====================================================================
//! @param		�uScene�vclass src
//! @create		Yuta Higuchi
//! @date		17/09/26
===================================================================== */

// including header
#include "Scene.h"
#include <cassert>
#include "CustomizeScene.h"
#include "PlayScene.h"
#include "SceneManager.h"

// namespace
using namespace std;

// method

// constructor
Scene::Scene()
{
	// �����V�[���̐ݒ�
	sceneDirector_ = CUSTOMIZE;
}

// =================================================
// @brief	�V�[���؂�ւ�
// @param	�V�[���iSCENE�j
// @return	none
// =================================================
void Scene::ChangeScene(SCENE scene)
{
	sceneDirector_ = scene;

	// �V�[���̃C���X�^���X��ύX
	SceneManager& sm = SceneManager::GetInstance();
	sm.ChangeScene(scene);
}