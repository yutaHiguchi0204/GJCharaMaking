/* =====================================================================
//! @param		「CustomizeScene」class src
//! @create		Yuta Higuchi
//! @date		17/09/26
===================================================================== */

// including header
#include "CustomizeScene.h"
#include "CharaData.h"
#include "Constant.h"

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

	// 静的メンバの設定
	Object::InitializeStatic(device_, context_, camera_.get());

	// パーツデータの読み込み
	CharaData& data = CharaData::GetInstance();
	data.ImportData();

	// 天球モデルの読み込み
	skyDome_ = make_unique<IModel>();
	skyDome_->Initialize(L"skyDome");

	// 地面モデルの読み込み
	ground_ = make_unique<IModel>();
	ground_->Initialize(L"ground_200m");
	ground_->GetRootParts()->SetTranslate(Vector3(0, -1.0f, 0));

	//パーツビューの読み込み
	partsView_ = make_unique<PartsView>();
	partsView_->Initialize();
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

	// 地面の更新
	ground_->Update();

	//パーツビューの更新
	partsView_->Update();
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

	// 地面の描画
	ground_->Draw();

	//パーツビューの描画
	partsView_->Draw();

}