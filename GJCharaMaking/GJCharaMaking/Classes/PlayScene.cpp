/*===============================================================
// @param	[PlayScene] class src 
// @create	Kazushi Shinohara
// @date	17/09/26
================================================================*/

// include 
#include "PlayScene.h"
#include "Constant.h"

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
	camera_ = make_unique<Camera>(SIZE_WINDOW_WIDTH, SIZE_WINDOW_HEIGHT);

	// 静的メンバの設定
	Object::InitializeStatic(device_, context_, camera_.get());

	// 天球モデルの読み込み
	skyDome_ = make_unique<Object>();
	skyDome_->LoadModel(L"Resources/CMedia/skyDome.cmo");

	//地形と天球ライティングを無効にする
	skyDome_->DisableLighting();
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

	// 天球の更新
	skyDome_->Update();
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
}
