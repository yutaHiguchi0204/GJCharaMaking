/*===============================================================
// @param	[PlayScene] class header
// @create	Kazushi Shinohara
// @date	17/09/26
================================================================*/
#pragma once

// include
#include "Scene.h"

//class
class PlayScene : public Scene
{
public:
	PlayScene(Microsoft::WRL::ComPtr<ID3D11Device> device, Microsoft::WRL::ComPtr<ID3D11DeviceContext> context);
	~PlayScene() {};

	void Initialize() override;		// initialize
	void Update() override;			// update
	void Draw() override;			// draw
};

