/* =====================================================================
//! @param		「TextureManager」クラスのソースファイル
//! @create		樋口　裕太
//! @date		17/06/05
===================================================================== */

// ヘッダファイルのインクルード
#include "TextureManager.h"

#include "DXTKManager.h"
#include "WICTextureLoader.h"

// 名前空間
using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace std;

// メンバ関数の定義

/* =====================================================================
//! 内　容		初期化処理
//! 引　数		デバイス（ID3D11Device*）、コンテキスト（ID3D11DeviceContext*）
//! 戻り値		なし
===================================================================== */
void TextureManager::Initializer(ID3D11Device* device, ID3D11DeviceContext* context)
{
	device_ = device;
	context_ = context;

	// ブレンドステートの設定
	SetBlendState();
}

/* =====================================================================
//! 内　容		テクスチャのロード
//! 引　数		ファイル名（wchar_t*）、テクスチャ（ID3D11ShaderResourceView**）
//! 戻り値		なし
===================================================================== */
void TextureManager::Load(wstring file, ID3D11ShaderResourceView** texture)
{
	const wstring fileName = L"Resources/Texture2D/" + file + L".png";

	CreateWICTextureFromFile(device_, fileName.c_str(), nullptr, texture);
}

/* =====================================================================
//! 内　容		ブレンドステートの設定
//! 引　数		なし
//! 戻り値		なし
===================================================================== */
void TextureManager::SetBlendState()
{
	D3D11_BLEND_DESC bd;
	ZeroMemory(&bd, sizeof(D3D11_BLEND_DESC));
	bd.IndependentBlendEnable = false;
	bd.AlphaToCoverageEnable = false;
	bd.RenderTarget[0].BlendEnable = true;
	bd.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	bd.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	bd.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	bd.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	bd.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	bd.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	bd.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	
	device_->CreateBlendState(&bd, &blendState_);

	float blendFactor[4] = { D3D11_BLEND_ZERO, D3D11_BLEND_ZERO, D3D11_BLEND_ZERO, D3D11_BLEND_ZERO };
	UINT mask = 0xffffffff;
	context_->OMSetBlendState(blendState_, blendFactor, mask);
}

/* =====================================================================
//! 内　容		テクスチャの描画（矩形なし）
//! 引　数		テクスチャハンドル（ID3D11ShaderResourceView*）、表示座標（Vector2）、回転角（float）、テクスチャサイズ（Vector2）、反転処理（SpriteEffects）
//! 戻り値		なし
===================================================================== */
void TextureManager::Draw(ID3D11ShaderResourceView* texture, Vector2 pos, float angle, Vector2 textureSize, SpriteEffects flip)
{
	DXTKManager& dxtk = DXTKManager::GetInstance();

	dxtk.spriteBatch_->Begin(SpriteSortMode_Deferred, blendState_);
	dxtk.spriteBatch_->Draw(texture, pos, nullptr, Colors::White, angle, Vector2(textureSize.x / 2, textureSize.y / 2), 1.0f, flip);
	dxtk.spriteBatch_->End();
}

/* =====================================================================
//! 内　容		テクスチャの描画（矩形あり）
//! 引　数		テクスチャハンドル（ID3D11ShaderResourceView*）、表示座標（Vector2）、画像の矩形開始座標（Vector2）、画像の矩形サイズ（Vector2）、回転角（float）、テクスチャサイズ（Vector2）、反転処理（SpriteEffects）
//! 戻り値		なし
===================================================================== */
void TextureManager::Draw(ID3D11ShaderResourceView* texture, Vector2 pos, Vector2 rectPos, Vector2 rectSize, float angle, Vector2 textureSize, SpriteEffects flip)
{
	DXTKManager& dxtk = DXTKManager::GetInstance();

	// 矩形指定
	int left = rectPos.x, right = rectPos.x + rectSize.x;
	int top = rectPos.y, bottom = rectPos.y + rectSize.y;
	RECT rect = RECT{ left, top, right, bottom };

	dxtk.spriteBatch_->Begin(SpriteSortMode_Deferred, blendState_);
	dxtk.spriteBatch_->Draw(texture, pos, &rect, Colors::White, angle, Vector2(textureSize.x / 2, textureSize.y / 2), 1.0f, flip);
	dxtk.spriteBatch_->End();
}