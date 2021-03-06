/* =====================================================================
//! @param		「CustomizeScene」class header
//! @create		Yuta Higuchi
//! @date		17/09/26
===================================================================== */
#pragma once

// including header
#include "Scene.h"
#include "Camera.h"
#include "IModel.h"
#include "Player.h"
#include "PartsView.h"
#include "SceneChangerButton.h"

// class
class CustomizeScene : public Scene
{
private:
	std::unique_ptr<Camera> camera_;						// カメラ

	std::unique_ptr<IModel> skyDome_;						// 天球

	std::unique_ptr<Player> player_;						// プレイヤー
	float playerRot_;										// プレイヤーの回転角

	std::unique_ptr<PartsView> partsView_;					// パーツビュー
	std::unique_ptr<SceneChangerButton> sceneChanger_;		// シーン遷移用ボタン

public:
	CustomizeScene(Microsoft::WRL::ComPtr<ID3D11Device> device, Microsoft::WRL::ComPtr<ID3D11DeviceContext> context);
	virtual ~CustomizeScene() {};

	void Initialize() override;								// initialize
	void Update() override;									// update
	void Draw() override;									// draw

	void CheckCollision() override;							// 当たり判定処理
};