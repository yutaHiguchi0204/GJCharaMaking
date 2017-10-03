/* =====================================================================
//! @param		「SceneManager」class header
//! @create		Yuta Higuchi
//! @date		17/09/26
===================================================================== */
#pragma once

// including header
#include "SingletonDirector.h"
#include <d3d11_1.h>
#include <Effects.h>
#include <PrimitiveBatch.h>
#include <SimpleMath.h>
#include <VertexTypes.h>
#include "Scene.h"

// class
class SceneManager : public SingletonDirector<SceneManager>
{
private:
	Microsoft::WRL::ComPtr<ID3D11Device> device_;											// デバイス
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> context_;									// デバイスコンテキスト

	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionNormal>> batch_;			// プリミティブバッチ
	std::unique_ptr<DirectX::BasicEffect> effect_;											// エフェクト
	Microsoft::WRL::ComPtr<ID3D11InputLayout> inputLayout_;									// インプットレイアウト
	std::unique_ptr<DirectX::EffectFactory> factory_;										// エフェクトファクトリ

	DirectX::SimpleMath::Matrix world_;														// ワールド行列
	DirectX::SimpleMath::Matrix view_;														// ビュー行列
	DirectX::SimpleMath::Matrix proj_;														// プロジェクション行列

	std::unique_ptr<Scene> scene_;		// シーン

private:
	friend class SingletonDirector<SceneManager>;

	// constructor
	SceneManager() {};

public:
	void Initialize(Microsoft::WRL::ComPtr<ID3D11Device> device, Microsoft::WRL::ComPtr<ID3D11DeviceContext> context);		// initialize
	void Update();								// update
	void Draw();								// draw

	void ChangeScene(Scene::SCENE scene);		// シーン切り替え
};