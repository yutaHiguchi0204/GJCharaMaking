/* =====================================================================
//! @param		[Partsview] class src
//! @create		Yuki Matsumaru
//! @date		17/09/27
===================================================================== */

// including header
#include "Partsview.h"
#include "Constant.h"
#include "TextureManager.h"

// namespace
using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace std;

// method

// =================================================
// @brief	Initialize
// @param	none
// @return	none
// =================================================
void PartsView::Initialize()
{
	// �p�[�c�r���[���f���̓ǂݍ���
	TextureManager& tm = TextureManager::GetInstance();
	tm.Load(L"partsView",partsBoard.GetAddressOf());
}

// =================================================
// @brief	update
// @param	none
// @return	none
// =================================================
void PartsView::Update()
{
	// �p�[�c�r���[�̍X�V
	
}

// =================================================
// @brief	draw
// @param	none
// @return	none
// =================================================
void PartsView::Draw()
{
	// �p�[�c�r���[�̕`��
	TextureManager& tm = TextureManager::GetInstance();
	tm.Draw(partsBoard.Get(), Vector2(20.0f, 20.0f));
	
}
