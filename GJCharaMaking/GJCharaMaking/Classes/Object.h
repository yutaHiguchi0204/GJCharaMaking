/* =====================================================================
//! @param		「Object」class header
//! @create		Yuta Higuchi
//! @date		17/09/26
===================================================================== */
#pragma once

// including header
#include <CommonStates.h>
#include <d3d11_1.h>
#include <Effects.h>
#include <Model.h>
#include <WICTextureLoader.h>
#include "Camera.h"

// class
class Object
{
private:
	static Microsoft::WRL::ComPtr<ID3D11Device>            device_;			// デバイス
	static Microsoft::WRL::ComPtr<ID3D11DeviceContext>     context_;		// デバイスコンテキスト
	static Camera* camera_;													// カメラ
	static std::unique_ptr<DirectX::CommonStates> states_;					// 汎用描画ステート
	static std::unique_ptr<DirectX::EffectFactory> factory_;				// エフェクトファクトリ
	static ID3D11BlendState* blendStateSubtract_;							// 減算描画用

	std::unique_ptr<DirectX::Model>		model_;																					// ３Ｄモデル

	DirectX::SimpleMath::Vector3		scale_;																					// スケーリング
	DirectX::SimpleMath::Vector3		rotate_;																					// 回転角（オイラー角）
	DirectX::SimpleMath::Vector3		translate_;																				// 平行移動

	DirectX::SimpleMath::Matrix			world_;																					// ワールド行列
	Object*								pParent_;

public:
	Object();
	virtual ~Object() {};

	// 静的メンバ変数の初期化
	static void InitializeStatic(
		Microsoft::WRL::ComPtr<ID3D11Device> device,
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> context,
		Camera* camera
	);

	// 減算描画の設定
	static void SetSubtractive();

	void Update();																													// 更新
	void Draw();																													// 描画
	void DrawSubtractive();																											// 減算描画

	void LoadModel(const wchar_t* fileName);																						// モデルのロード

	void SetScale(const DirectX::SimpleMath::Vector3& scale)			{ scale_ = scale; };										// スケーリングの設定
	void SetRotate(const DirectX::SimpleMath::Vector3& rotate)			{ rotate_ = rotate; };										// 回転角の設定（オイラー角）
	void SetTranslate(const DirectX::SimpleMath::Vector3& translate)	{ translate_ = translate; };								// 平行移動の設定

	void SetWorldMatrix(const DirectX::SimpleMath::Matrix& mat)			{ world_ = mat; };											// ワールド行列の設定

	void SetParent(Object* obj)											{ pParent_ = obj; };										// 親の３Ｄオブジェクトを設定

	const DirectX::SimpleMath::Vector3 GetScale()						{ return scale_; };											// スケーリングを取得
	const DirectX::SimpleMath::Vector3 GetRotate()						{ return rotate_; };										// 回転角を取得
	const DirectX::SimpleMath::Vector3 GetTranslate()					{ return translate_; };										// 平行移動の取得

	const DirectX::SimpleMath::Matrix GetWorldMatrix()					{ return world_; };											// ワールド行列の取得

	Object* GetParent()													{ return pParent_; };										// 親の３Ｄオブジェクトの取得

	void DisableLighting();
};