/* =====================================================================
//! @param		�uCustomizeScene�vclass header
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
	std::unique_ptr<Camera> camera_;						// �J����

	std::unique_ptr<IModel> skyDome_;						// �V��

	std::unique_ptr<Player> player_;						// �v���C���[
	float playerRot_;										// �v���C���[�̉�]�p

	std::unique_ptr<PartsView> partsView_;					// �p�[�c�r���[
	std::unique_ptr<SceneChangerButton> sceneChanger_;		// �V�[���J�ڗp�{�^��

public:
	CustomizeScene(Microsoft::WRL::ComPtr<ID3D11Device> device, Microsoft::WRL::ComPtr<ID3D11DeviceContext> context);
	virtual ~CustomizeScene() {};

	void Initialize() override;								// initialize
	void Update() override;									// update
	void Draw() override;									// draw

	void CheckCollision() override;							// �����蔻�菈��
};