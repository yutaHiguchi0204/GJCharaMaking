/* =====================================================================
//! @param		「CustomizeScene」class src
//! @create		Yuta Higuchi
//! @date		17/09/26
===================================================================== */

// including header
#include "CustomizeScene.h"
#include "CharaData.h"
#include "Constant.h"
#include "DXTKManager.h"
#include "KeyboardDebuger.h"

// namespace
using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace std;

// method

// constructor
CustomizeScene::CustomizeScene(Microsoft::WRL::ComPtr<ID3D11Device> device, Microsoft::WRL::ComPtr<ID3D11DeviceContext> context)
	: Scene(device, context)
{
}

// =================================================
// @brief	initialize
// @param	none
// @return	none
// =================================================
void CustomizeScene::Initialize()
{
	// カメラの生成
	camera_ = make_unique<Camera>(SIZE_WINDOW_WIDTH, SIZE_WINDOW_HEIGHT);

	// カメラの初期化
	camera_->SetEyePos(Vector3(9.0f, 10.0f, -25.0f));
	camera_->SetRefPos(Vector3(9.0f, 10.0f, 0.0f));

	// 静的メンバの設定
	Object::InitializeStatic(device_, context_, camera_.get());

	// 天球モデルの読み込み
	skyDome_ = make_unique<IModel>();
	skyDome_->Initialize(L"skyDome");

	// プレイヤーの読み込み
	player_ = make_unique<Player>();
	player_->Initialize(CharaData::CHARA_PARTS_NUM);

	// プレイヤーの回転角の初期化
	playerRot_ = 0.0f;

	// パーツビューの読み込み
	partsView_ = make_unique<PartsView>();
	partsView_->Initialize(L"customView");
	partsView_->LoadPanel();
}

// =================================================
// @brief	update
// @param	none
// @return	none
// =================================================
void CustomizeScene::Update()
{
	// カメラの更新
	camera_->Update();

	// 天球の更新
	skyDome_->Update();

	// プレイヤーの更新
	player_->Update();

	// プレイヤーをローテーションさせる
	playerRot_ -= 0.01f;
	player_->GetRootParts()->SetRotate(Vector3(0, playerRot_, 0));

	// キーボード処理（デバッグ用）
	KeyboardDebuger& kd = KeyboardDebuger::GetInstance();
	CharaData& data = CharaData::GetInstance();
	if (kd.ChangeCharaParts())
	{
		player_->ChangeParts(data.GetPartsGenre(), data.GetModelData(data.GetPartsGenre()));
		playerRot_ = 0.0f;
	}
}

// =================================================
// @brief	draw
// @param	none
// @return	none
// =================================================
void CustomizeScene::Draw()
{
	// 天球の描画
	skyDome_->Draw();

	// プレイヤーの描画
	player_->Draw();

	// パーツビューの描画
	partsView_->Draw();
	partsView_->DrawPanel();
}