/* =====================================================================
//! @param		「Scene」class header
//! @create		Yuta Higuchi
//! @date		17/09/26
===================================================================== */
#pragma once

// including header
#include "SingletonDirector.h"
#include <CommonStates.h>
#include <wrl\client.h>

// class
class Scene
{
public:
	// シーンの種類
	enum SCENE
	{
		CUSTOMIZE = 0,
		PLAY
	};

protected:
	Microsoft::WRL::ComPtr<ID3D11Device> device_;				// デバイス
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> context_;		// デバイスコンテキスト

private:
	SCENE sceneDirector_;										// シーン管理

public:
	Scene(Microsoft::WRL::ComPtr<ID3D11Device> device, Microsoft::WRL::ComPtr<ID3D11DeviceContext> context);
	virtual ~Scene() {};

	virtual void Initialize() = 0;						// initialize
	virtual void Update() = 0;							// update
	virtual void Draw() = 0;							// draw

	virtual void ChangeScene(Scene::SCENE scene);		// シーン切り替え

	virtual void CheckCollision() = 0;					// 当たり判定処理
};