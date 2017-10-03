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
using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace std;

// method

// constructor
Scene::Scene(Microsoft::WRL::ComPtr<ID3D11Device> device, Microsoft::WRL::ComPtr<ID3D11DeviceContext> context)
{
	device_ = device;
	context_ = context;

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