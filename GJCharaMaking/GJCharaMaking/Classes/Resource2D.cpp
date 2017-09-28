/* =====================================================================
//! @param		「Resource2D」class src
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
// @param	ファイル名（wstring）
// @return	none
// =================================================
void Resource2D::Initialize(const wstring file)
{
	// パーツビューモデルの読み込み
	TextureManager& tm = TextureManager::GetInstance();
	tm.Load(file, texture_.GetAddressOf());
}

// =================================================
// @brief	draw
// @param	座標（Vector2）
// @return	none
// =================================================
void Resource2D::Draw(const Vector2 pos)
{
	// パーツビューの描画
	TextureManager& tm = TextureManager::GetInstance();
	tm.Draw(texture_.Get(), pos);
}