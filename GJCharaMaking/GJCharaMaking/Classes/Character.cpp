/* =====================================================================
//! @param		[Character] class src
//! @create		Yuki Matsumaru
//! @date		17/09/26
===================================================================== */

// including header
#include "Character.h"

// namespace
using namespace std;

// method

// =================================================
// @brief	Initialize
// @param	none
// @return	none
// =================================================
void Character::Initialize(const wstring file)
{
	parts_.push_back(make_unique<Object>());
	parts_.back()->LoadModel(file);

	// ライティング無効
	parts_.back()->DisableLighting();
}

// =================================================
// @brief	update
// @param	none
// @return	none
// =================================================
void Character::Update()
{

}

// =================================================
// @brief	draw
// @param	none
// @return	none
// =================================================
void Character::Draw()
{

}