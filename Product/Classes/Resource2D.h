/* =====================================================================
//! @param		「Resource2D」class header
//! @create		Yuta Higuchi
//! @date		17/09/28
===================================================================== */
#pragma once

// including header
#include <CommonStates.h>
#include <d3d11_1.h>
#include <SimpleMath.h>
#include <string>
#include <wrl\client.h>

// class
class Resource2D
{
protected:
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> texture_;
	DirectX::SimpleMath::Vector2 pos_;

public:
	Resource2D() {};
	virtual ~Resource2D() {};

	virtual void Initialize(const std::wstring file);							// 初期化
	virtual void Draw();														// 描画

	void SetPos(const DirectX::SimpleMath::Vector2& pos) { pos_ = pos; }		// 座標設定
	inline const DirectX::SimpleMath::Vector2& GetPos() { return pos_; }		// 座標取得
};