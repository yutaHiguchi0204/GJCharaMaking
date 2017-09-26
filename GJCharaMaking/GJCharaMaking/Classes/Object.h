/* =====================================================================
//! @param		�uObject�vclass header
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
	static Microsoft::WRL::ComPtr<ID3D11Device>            device_;			// �f�o�C�X
	static Microsoft::WRL::ComPtr<ID3D11DeviceContext>     context_;		// �f�o�C�X�R���e�L�X�g
	static Camera* camera_;													// �J����
	static std::unique_ptr<DirectX::CommonStates> states_;					// �ėp�`��X�e�[�g
	static std::unique_ptr<DirectX::EffectFactory> factory_;				// �G�t�F�N�g�t�@�N�g��
	static ID3D11BlendState* blendStateSubtract_;							// ���Z�`��p

	std::unique_ptr<DirectX::Model>		model_;																					// �R�c���f��

	DirectX::SimpleMath::Vector3		scale_;																					// �X�P�[�����O
	DirectX::SimpleMath::Vector3		rotate_;																					// ��]�p�i�I�C���[�p�j
	DirectX::SimpleMath::Vector3		translate_;																				// ���s�ړ�

	DirectX::SimpleMath::Matrix			world_;																					// ���[���h�s��
	Object*								pParent_;

public:
	Object();
	virtual ~Object() {};

	// �ÓI�����o�ϐ��̏�����
	static void InitializeStatic(
		Microsoft::WRL::ComPtr<ID3D11Device> device,
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> context,
		Camera* camera
	);

	// ���Z�`��̐ݒ�
	static void SetSubtractive();

	void Update();																													// �X�V
	void Draw();																													// �`��
	void DrawSubtractive();																											// ���Z�`��

	void LoadModel(const wchar_t* fileName);																						// ���f���̃��[�h

	void SetScale(const DirectX::SimpleMath::Vector3& scale)			{ scale_ = scale; };										// �X�P�[�����O�̐ݒ�
	void SetRotate(const DirectX::SimpleMath::Vector3& rotate)			{ rotate_ = rotate; };										// ��]�p�̐ݒ�i�I�C���[�p�j
	void SetTranslate(const DirectX::SimpleMath::Vector3& translate)	{ translate_ = translate; };								// ���s�ړ��̐ݒ�

	void SetWorldMatrix(const DirectX::SimpleMath::Matrix& mat)			{ world_ = mat; };											// ���[���h�s��̐ݒ�

	void SetParent(Object* obj)											{ pParent_ = obj; };										// �e�̂R�c�I�u�W�F�N�g��ݒ�

	const DirectX::SimpleMath::Vector3 GetScale()						{ return scale_; };											// �X�P�[�����O���擾
	const DirectX::SimpleMath::Vector3 GetRotate()						{ return rotate_; };										// ��]�p���擾
	const DirectX::SimpleMath::Vector3 GetTranslate()					{ return translate_; };										// ���s�ړ��̎擾

	const DirectX::SimpleMath::Matrix GetWorldMatrix()					{ return world_; };											// ���[���h�s��̎擾

	Object* GetParent()													{ return pParent_; };										// �e�̂R�c�I�u�W�F�N�g�̎擾

	void DisableLighting();
};