/* =====================================================================
//! @param		「DXTKManager」クラスのヘッダファイル
//! @create		樋口　裕太
//! @date		17/06/05
===================================================================== */
#pragma once

// ヘッダファイルのインクルード
#include "SingletonDirector.h"

#include <CommonStates.h>
#include <SpriteBatch.h>

// クラスの定義
class DXTKManager : public SingletonDirector<DXTKManager>
{
public:
	ID3D11Device* m_device;
	ID3D11DeviceContext* m_context;

	// コモンステート
	std::unique_ptr<DirectX::CommonStates> m_states;

	// スプライトバッチ
	std::unique_ptr<DirectX::SpriteBatch> m_spriteBatch;

private:
	friend class SingletonDirector<DXTKManager>;

	// コンストラクタ
	DXTKManager() {}

public:

	// 初期化処理
	void Initializer(ID3D11Device* device, ID3D11DeviceContext* context)
	{
		m_device = device;
		m_context = context;

		// コモンステートを作成
		m_states = std::make_unique<DirectX::CommonStates>(device);

		// スプライトバッチ
		m_spriteBatch = std::make_unique<DirectX::SpriteBatch>(context);
	}

	// ステートの更新処理
	void UpdateInputState()
	{
	}
};