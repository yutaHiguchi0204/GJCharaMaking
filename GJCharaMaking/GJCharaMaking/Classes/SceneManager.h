/* =====================================================================
//! @param		�uSceneManager�vclass header
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
	Microsoft::WRL::ComPtr<ID3D11Device> device_;											// �f�o�C�X
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> context_;									// �f�o�C�X�R���e�L�X�g

	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionNormal>> batch_;			// �v���~�e�B�u�o�b�`
	std::unique_ptr<DirectX::BasicEffect> effect_;											// �G�t�F�N�g
	Microsoft::WRL::ComPtr<ID3D11InputLayout> inputLayout_;									// �C���v�b�g���C�A�E�g
	std::unique_ptr<DirectX::EffectFactory> factory_;										// �G�t�F�N�g�t�@�N�g��

	DirectX::SimpleMath::Matrix world_;														// ���[���h�s��
	DirectX::SimpleMath::Matrix view_;														// �r���[�s��
	DirectX::SimpleMath::Matrix proj_;														// �v���W�F�N�V�����s��

	std::unique_ptr<Scene> scene_;		// �V�[��

private:
	friend class SingletonDirector<SceneManager>;

	// constructor
	SceneManager() {};

public:
	void Initialize(Microsoft::WRL::ComPtr<ID3D11Device> device, Microsoft::WRL::ComPtr<ID3D11DeviceContext> context);		// initialize
	void Update();								// update
	void Draw();								// draw

	void ChangeScene(Scene::SCENE scene);		// �V�[���؂�ւ�
};