/* =====================================================================
//! @param		[Partsview] class src
//! @create		Yuki Matsumaru
//! @date		17/09/27
===================================================================== */

// including header
#include "PartsView.h"
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
	tm.Load(L"customView", partsBoard.GetAddressOf());
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
	tm.Draw(partsBoard.Get(), Vector2(32.0f, 32.0f));
	
}
