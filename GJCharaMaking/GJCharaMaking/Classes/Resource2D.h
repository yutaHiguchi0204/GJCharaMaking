/* =====================================================================
//! @param		ÅuResource2DÅvclass header
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
private:
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> texture_;

public:
	Resource2D() {};
	virtual ~Resource2D() {};

	void Initialize(const std::wstring file);				// èâä˙âª
	void Draw(const DirectX::SimpleMath::Vector2 pos);		// ï`âÊ
};