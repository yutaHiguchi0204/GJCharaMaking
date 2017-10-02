/* =====================================================================
//! @param		�uSceneChangerButton�vclass src
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
// @param	�t�@�C�����iwstring�j
// @return	none
// =================================================
void SceneChangerButton::Initialize(const wstring file)
{
	wstring fileName = L"sceneChanger" + file;

	// �p�[�c�r���[���f���̓ǂݍ���
	TextureManager& tm = TextureManager::GetInstance();
	tm.Load(fileName, texture_.GetAddressOf());
}