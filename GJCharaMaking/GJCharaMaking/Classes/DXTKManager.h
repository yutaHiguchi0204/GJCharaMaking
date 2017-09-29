/* =====================================================================
//! @param		「DXTKManager」クラスのヘッダファイル
//! @create		樋口　裕太
//! @date		17/06/05
===================================================================== */
#pragma once

// ヘッダファイルのインクルード
#include "SingletonDirector.h"

#include <CommonStates.h>
#include <Keyboard.h>
#include <SpriteBatch.h>

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

	// キーボード関係
	std::unique_ptr<DirectX::Keyboard> keyboard_;
	std::unique_ptr<DirectX::Keyboard::KeyboardStateTracker> keyTracker_;

private:
	friend class SingletonDirector<DXTKManager>;

	// コンストラクタ
	DXTKManager() 
	{
		// キーボード関係の初期化
		keyboard_ = std::make_unique<DirectX::Keyboard>();
		keyTracker_ = std::make_unique <DirectX::Keyboard::KeyboardStateTracker>();
	}

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
	}

	// ステートの更新処理
	void UpdateInputState()
	{
		// キー入力情報を取得
		DirectX::Keyboard::State key = keyboard_->GetState();
		keyTracker_->Update(key);
	}
};