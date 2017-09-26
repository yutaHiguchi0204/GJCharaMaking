/* =====================================================================
//! @param		「Object」class src
//! @create		Yuta Higuchi
//! @date		17/09/26
===================================================================== */

// including header
#include "Object.h"

// namespace
using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace std;

// static member
Microsoft::WRL::ComPtr<ID3D11Device>		Object::device_;				// デバイス
Microsoft::WRL::ComPtr<ID3D11DeviceContext> Object::context_;				// デバイスコンテキスト
Camera*										Object::camera_;				// カメラ
unique_ptr<CommonStates>					Object::states_;				// 汎用描画ステート
unique_ptr<EffectFactory>					Object::factory_;				// エフェクトファクトリ
ID3D11BlendState*							Object::blendStateSubtract_;	// 減算描画用

// method

// constructor
Object::Object()
{
	// スケールの初期化
	scale_ = Vector3(1.0f, 1.0f, 1.0f);

	// 親の３Ｄオブジェクトを初期化
	pParent_ = nullptr;
}

// =================================================
// @brief	静的メンバの初期化
// @param	デバイス（ID3D11Device）、デバイスコンテキスト（ID3D11DeviceContext）、カメラ（Camera*）
// @return	none
// =================================================
void Object::InitializeStatic(Microsoft::WRL::ComPtr<ID3D11Device> device, Microsoft::WRL::ComPtr<ID3D11DeviceContext> context, Camera* camera)
{
	device_ = device;
	context_ = context;
	camera_ = camera;

	// 汎用描画ステート生成
	states_ = make_unique<CommonStates>(device_.Get());

	// エフェクトファクトリ生成
	factory_ = make_unique<EffectFactory>(device_.Get());
	factory_->SetDirectory(L"Resources/CMedia");

	// 減算描画用のブレンドステートを作成
	D3D11_BLEND_DESC desc;
	desc.AlphaToCoverageEnable = false;
	desc.IndependentBlendEnable = false;
	desc.RenderTarget[0].BlendEnable = true;
	desc.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
	desc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
	desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_REV_SUBTRACT;
	desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ONE;
	desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_REV_SUBTRACT;
	desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	HRESULT ret = device_->CreateBlendState(&desc, &blendStateSubtract_);
}

// =================================================
// @brief	描画減算の設定
// @param	none
// @return	none
// =================================================
void Object::SetSubtractive()
{
	// 減算描画を設定
	context_->OMSetBlendState(blendStateSubtract_, nullptr, 0xffffff);
}

// =================================================
// @brief	update
// @param	none
// @return	none
// =================================================
void Object::Update()
{
	// スケーリング行列
	Matrix scaleMat = Matrix::CreateScale(scale_);

	// 回転行列
	Matrix rotMat;

	// オイラー角で計算
	Matrix rotMatZ = Matrix::CreateRotationZ(rotate_.z);
	Matrix rotMatX = Matrix::CreateRotationX(rotate_.x);
	Matrix rotMatY = Matrix::CreateRotationY(rotate_.y);
	rotMat = rotMatZ * rotMatX * rotMatY;

	// 平行移動行列
	Matrix transMat = Matrix::CreateTranslation(translate_);

	// ワールド行列の合成
	world_ = scaleMat * rotMat * transMat;

	// 親の行列をかける（子の場合）
	if (pParent_) world_ *= pParent_->GetWorldMatrix();
}

// =================================================
// @brief	draw
// @param	none
// @return	none
// =================================================
void Object::Draw()
{
	if (model_)
	{
		// ３Ｄモデルの描画
		model_->Draw(
			context_.Get(),
			*states_,
			world_,
			camera_->GetViewMatrix(),
			camera_->GetProjectionMatrix()
		);
	}
}

// =================================================
// @brief	減算描画処理
// @param	none
// @return	none
// =================================================
void Object::DrawSubtractive()
{
	if (model_)
	{
		// ３Ｄモデルの描画
		model_->Draw(
			context_.Get(),
			*states_,
			world_,
			camera_->GetViewMatrix(),
			camera_->GetProjectionMatrix(),
			false,
			Object::SetSubtractive
		);
	}
}

// =================================================
// @brief	モデルのロード
// @param	ファイル名（wchar_t*）
// @return	none
// =================================================
void Object::LoadModel(const wchar_t* fileName)
{
	// モデルの読み込み
	model_ = Model::CreateFromCMO(
		device_.Get(),
		fileName,
		*factory_
	);
}

// =================================================
// @brief	オブジェクトのライティングを無効にする
// @param	none
// @return	none
// =================================================
void Object::DisableLighting()
{
	if (model_)
	{
		// モデル内の全メッシュ分回す
		ModelMesh::Collection::const_iterator it_mesh = model_->meshes.begin();
		for (; it_mesh != model_->meshes.end(); it_mesh++)
		{
			ModelMesh* modelmesh = it_mesh->get();
			assert(modelmesh);

			// メッシュ内の全メッシュパーツ分回す
			std::vector<std::unique_ptr<ModelMeshPart>>::iterator it_meshpart = modelmesh->meshParts.begin();
			for (; it_meshpart != modelmesh->meshParts.end(); it_meshpart++)
			{
				ModelMeshPart* meshpart = it_meshpart->get();
				assert(meshpart);

				// メッシュパーツにセットされたエフェクトをBasicEffectとして取得
				std::shared_ptr<IEffect> ieff = meshpart->effect;
				BasicEffect* eff = dynamic_cast<BasicEffect*>(ieff.get());
				if (eff != nullptr)
				{
					// 自己発光を最大値に
					eff->SetEmissiveColor(Vector3(1, 1, 1));

					// エフェクトに含む全ての平行光源分について処理する
					for (int i = 0; i < BasicEffect::MaxDirectionalLights; i++)
					{
						// ライトを無効にする
						eff->SetLightEnabled(i, false);
					}
				}
			}
		}
	}
}