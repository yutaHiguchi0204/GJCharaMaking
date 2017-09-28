/* =====================================================================
//! @param		�uResource2D�vclass src
//! @create		Yuta Higuchi
//! @date		17/09/28
===================================================================== */

// including header
#include "Resource2D.h"
#include "TextureManager.h"

// namespace
using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace std;

// method

// =================================================
// @brief	initialize
// @param	�t�@�C�����iwstring�j
// @return	none
// =================================================
void Resource2D::Initialize(const wstring file)
{
	// �p�[�c�r���[���f���̓ǂݍ���
	TextureManager& tm = TextureManager::GetInstance();
	tm.Load(file, texture_.GetAddressOf());
}

// =================================================
// @brief	draw
// @param	���W�iVector2�j
// @return	none
// =================================================
void Resource2D::Draw(const Vector2 pos)
{
	// �p�[�c�r���[�̕`��
	TextureManager& tm = TextureManager::GetInstance();
	tm.Draw(texture_.Get(), pos);
}