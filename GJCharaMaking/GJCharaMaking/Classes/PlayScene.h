/*===============================================================
// @param	[PlayScene] class header
// @create	Kazushi Shinohara
// @date	17/09/26
================================================================*/
#pragma once

// include
#include "Scene.h"
#include "Camera.h"
#include "Player.h"

//class
class PlayScene : public Scene
{
private:
	std::shared_ptr<Camera> camera_;			// カメラ

	std::unique_ptr<IModel> skyDome_;			// 天球
	std::unique_ptr<IModel> ground_;			// 地面

	std::unique_ptr<Player> player_;			// プレイヤー

public:
	PlayScene(Microsoft::WRL::ComPtr<ID3D11Device> device, Microsoft::WRL::ComPtr<ID3D11DeviceContext> context);
	~PlayScene() {};

	void Initialize() override;		// initialize
	void Update() override;			// update
	void Draw() override;			// draw
};

