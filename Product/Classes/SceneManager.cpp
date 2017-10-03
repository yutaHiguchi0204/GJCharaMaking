/* =====================================================================
//! @param		「SceneManager」class src
//! @create		Yuta Higuchi
//! @date		17/09/26
===================================================================== */

// including header
#include "SceneManager.h"
#include <cassert>
#include "Constant.h"
#include "CustomizeScene.h"
#include "PlayScene.h"

// namespace
using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace std;

// method

// =================================================
// @brief	initialize
// @param	デバイス（ID3D11Device）、デバイスコンテキスト（ID3D11DeviceContext）
// @return	none
// =================================================
void SceneManager::Initialize(Microsoft::WRL::ComPtr<ID3D11Device> device, Microsoft::WRL::ComPtr<ID3D11DeviceContext> context)
{
	device_ = device;
	context_ = context;

	// プリミティブバッチの設定
	batch_ = make_unique<PrimitiveBatch<VertexPositionNormal>>(context_.Get());

	// エフェクト生成
	effect_ = make_unique<BasicEffect>(device_.Get());
	effect_->SetVertexColorEnabled(true);

	// 行列の初期化
	view_ = Matrix::CreateLookAt(Vector3(0.f, 2.f, 2.f), Vector3::Zero, Vector3::UnitY);
	proj_ = Matrix::CreatePerspectiveFieldOfView(XM_PI / 4.f, float(SIZE_WINDOW_WIDTH) / float(SIZE_WINDOW_HEIGHT), 0.1f, 500.f);

	// エフェクトの初期化
	effect_->SetView(view_);
	effect_->SetProjection(proj_);

	void const* shaderByteCode;
	size_t byteCodeLength;

	// シェーダーバイトコードの処理
	effect_->GetVertexShaderBytecode(&shaderByteCode, &byteCodeLength);

	// デバイス設定
	device_->CreateInputLayout(VertexPositionColor::InputElements,
		VertexPositionColor::InputElementCount,
		shaderByteCode, byteCodeLength,
		inputLayout_.GetAddressOf());

	// エフェクトファクトリの生成
	factory_ = std::make_unique<EffectFactory>(device_.Get());

	// テクスチャの読み取りパス指定
	factory_->SetDirectory(L"Resources/CMedia");

	// 初期シーンをカスタム画面に設定
	scene_ = make_unique<CustomizeScene>(device_, context_);
	scene_->Initialize();
}

// =================================================
// @brief	update
// @param	none
// @return	none
// =================================================
void SceneManager::Update()
{
	scene_->Update();
}

// =================================================
// @brief	draw
// @param	none
// @return	none
// =================================================
void SceneManager::Draw()
{
	scene_->Draw();
}

// =================================================
// @brief	シーン切り替え
// @param	シーン（SCENE）
// @return	none
// =================================================
void SceneManager::ChangeScene(Scene::SCENE scene)
{
	// シーン切り替え
	switch (scene)
	{
	case Scene::CUSTOMIZE:
		scene_ = make_unique<CustomizeScene>(device_, context_);
		break;

	case Scene::PLAY:
		scene_ = make_unique<PlayScene>(device_, context_);
		break;

	default:
		OutputDebugString(L"This scene is unknown.");
		assert(0);
		break;
	}

	scene_->Initialize();
}