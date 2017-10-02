/* =====================================================================
//! @param		「SceneChangerButton」class src
//! @create		Yuta Higuchi
//! @date		17/10/02
===================================================================== */

// including header
#include "SceneChangerButton.h"
#include "TextureManager.h"

// namespace
using namespace std;

// method

// =================================================
// @brief	initialize
// @param	ファイル名（wstring）
// @return	none
// =================================================
void SceneChangerButton::Initialize(const wstring file)
{
	wstring fileName = L"sceneChanger" + file;

	// パーツビューモデルの読み込み
	TextureManager& tm = TextureManager::GetInstance();
	tm.Load(fileName, texture_.GetAddressOf());
}