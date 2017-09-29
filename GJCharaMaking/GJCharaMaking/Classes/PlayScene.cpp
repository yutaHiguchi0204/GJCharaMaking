/*===============================================================
// @param	[PlayScene] class src 
// @create	Kazushi Shinohara
// @date	17/09/26
================================================================*/

// include 
#include "PlayScene.h"
#include "Constant.h"
#include "KeyboardDebuger.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace std;

// constructor
PlayScene::PlayScene(Microsoft::WRL::ComPtr<ID3D11Device> device, Microsoft::WRL::ComPtr<ID3D11DeviceContext> context)
	: Scene(device, context)
{
}

/*==============================================================
// @brief		initialize
// @param		none
// @return		none
===============================================================*/
void PlayScene::Initialize()
{
	// カメラの生成
	camera_ = make_shared<Camera>(SIZE_WINDOW_WIDTH, SIZE_WINDOW_HEIGHT);

	// カメラの初期化
	camera_->SetEyePos(Vector3(0.0f, 10.0f, -25.0f));
	camera_->SetRefPos(Vector3(0.0f, 10.0f, 0.0f));

	// 静的メンバの設定
	Object::InitializeStatic(device_, context_, camera_.get());

	// 天球モデルの読み込み
	skyDome_ = make_unique<IModel>();
	skyDome_->Initialize(L"skyDome");

	// 地面モデルの読み込み
	ground_ = make_unique<IModel>();
	ground_->Initialize(L"ground_200m");

	// プレイヤーの読み込み
	player_ = make_unique<Player>();
	player_->Initialize(CharaData::CHARA_PARTS_NUM);
}

/*==============================================================
// @brief		update
// @param		none
// @return		none
===============================================================*/
void PlayScene::Update()
{
	// カメラの更新
	camera_->Update();

	// カメラをプレイヤー軸で動かす（キーボード操作）
	KeyboardDebuger& kd = KeyboardDebuger::GetInstance();
	kd.MoveCamera(camera_);

	// 天球の更新
	skyDome_->Update();

	// 地面の更新
	ground_->Update();

	// プレイヤーの更新
	player_->Update();
}

/*==============================================================
// @brief		draw
// @param		none
// @return		none
===============================================================*/
void PlayScene::Draw()
{
	// 天球の描画
	skyDome_->Draw();

	// 地面の描画
	ground_->Draw();

	// プレイヤーの描画
	player_->Draw();
}
