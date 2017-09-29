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
#include <Mouse.h>

// クラスの定義
class DXTKManager : public SingletonDirector<DXTKManager>
{
public:
	ID3D11Device* device_;
	ID3D11DeviceContext* context_;

	// コモンステート
	std::unique_ptr<DirectX::CommonStates> states_;

	// スプライトバッチ
	std::unique_ptr<DirectX::SpriteBatch> spriteBatch_;

	//マウス
	std::unique_ptr<DirectX::Mouse> mouse_;
	std::unique_ptr<DirectX::Mouse::ButtonStateTracker> mouseTracker_;

private:
	friend class SingletonDirector<DXTKManager>;

	// コンストラクタ
	DXTKManager() {}

public:

	// 初期化処理
	void Initializer(ID3D11Device* device, ID3D11DeviceContext* context)
	{
		device_ = device;
		context_ = context;

		// コモンステートを作成
		states_ = std::make_unique<DirectX::CommonStates>(device);

		// スプライトバッチ
		spriteBatch_ = std::make_unique<DirectX::SpriteBatch>(context);

		//マウス
		mouse_ = std::make_unique<DirectX::Mouse>();
		mouseTracker_ = std::make_unique<DirectX::Mouse::ButtonStateTracker>();
	}

	// ステートの更新処理
	void UpdateInputState()
	{
		// マウス情報を取得
		Mouse::State mouse = mouse_->GetState();
		mouseTracker_->Update(mouse);
	}
};