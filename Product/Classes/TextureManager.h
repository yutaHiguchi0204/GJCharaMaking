/* =====================================================================
//! @param		「TextureManager」クラスのヘッダファイル
//! @create		樋口　裕太
//! @date		17/06/05
===================================================================== */
#pragma once

// ヘッダファイルのインクルード
#include "SingletonDirector.h"

#include <CommonStates.h>
#include <d3d11_1.h>
#include <SimpleMath.h>
#include <SpriteBatch.h>
#include <string>
#include "Constant.h"

// クラスの定義
class TextureManager : public SingletonDirector<TextureManager>
{
public:
	ID3D11Device* device_;
	ID3D11DeviceContext* context_;
	ID3D11BlendState* blendState_;

private:
	friend class SingletonDirector<TextureManager>;

	// コンストラクタ
	TextureManager() { blendState_ = NULL; };

public:

	// 初期化処理
	void Initializer(ID3D11Device* device, ID3D11DeviceContext* context);

	// テクスチャのロード
	void Load(std::wstring file, ID3D11ShaderResourceView** texture);

	// ブレンドステートの設定
	void SetBlendState();

	// テクスチャの描画
	void Draw(
		ID3D11ShaderResourceView* texture,													// テクスチャハンドル
		DirectX::SimpleMath::Vector2 pos,													// 表示座標
		float angle = 0.0f,																	// 回転角
		DirectX::SimpleMath::Vector2 textureSize = DirectX::SimpleMath::Vector2(0, 0),		// テクスチャサイズ
		DirectX::SpriteEffects flip = DirectX::SpriteEffects::SpriteEffects_None			// 反転処理
	);
	void Draw(
		ID3D11ShaderResourceView* texture,													// テクスチャハンドル
		DirectX::SimpleMath::Vector2 pos,													// 表示座標
		DirectX::SimpleMath::Vector2 rectPos,												// 切り取る矩形の開始位置
		DirectX::SimpleMath::Vector2 rectSize,												// 切り取る矩形サイズ
		float angle = 0.0f,																	// 回転角
		DirectX::SimpleMath::Vector2 textureSize = DirectX::SimpleMath::Vector2(0, 0),		// テクスチャサイズ
		DirectX::SpriteEffects flip = DirectX::SpriteEffects::SpriteEffects_None			// 反転処理
	);
};