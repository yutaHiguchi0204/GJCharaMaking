/* =====================================================================
//! @param		�uScene�vclass header
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
	// �V�[���̎��
	enum SCENE
	{
		CUSTOMIZE = 0,
		PLAY
	};

protected:
	Microsoft::WRL::ComPtr<ID3D11Device> device_;				// �f�o�C�X
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> context_;		// �f�o�C�X�R���e�L�X�g

private:
	SCENE sceneDirector_;										// �V�[���Ǘ�

public:
	Scene(Microsoft::WRL::ComPtr<ID3D11Device> device, Microsoft::WRL::ComPtr<ID3D11DeviceContext> context);
	virtual ~Scene() {};

	virtual void Initialize() = 0;						// initialize
	virtual void Update() = 0;							// update
	virtual void Draw() = 0;							// draw

	virtual void ChangeScene(Scene::SCENE scene);		// �V�[���؂�ւ�

	virtual void CheckCollision() = 0;					// �����蔻�菈��
};