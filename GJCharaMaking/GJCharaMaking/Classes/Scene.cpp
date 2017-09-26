/* =====================================================================
//! @param		「Scene」class src
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

	// 初期シーンの設定
	sceneDirector_ = CUSTOMIZE;
}

// =================================================
// @brief	シーン切り替え
// @param	シーン（SCENE）
// @return	none
// =================================================
void Scene::ChangeScene(SCENE scene)
{
	sceneDirector_ = scene;

	// シーンのインスタンスを変更
	SceneManager& sm = SceneManager::GetInstance();
	sm.ChangeScene(scene);
}