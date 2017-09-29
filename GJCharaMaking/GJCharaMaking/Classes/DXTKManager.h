/* =====================================================================
//! @param		�uDXTKManager�v�N���X�̃w�b�_�t�@�C��
//! @create		����@�T��
//! @date		17/06/05
===================================================================== */
#pragma once

// �w�b�_�t�@�C���̃C���N���[�h
#include "SingletonDirector.h"

#include <CommonStates.h>
#include <Keyboard.h>
#include <SpriteBatch.h>

// �N���X�̒�`
class DXTKManager : public SingletonDirector<DXTKManager>
{
public:
	ID3D11Device* device_;
	ID3D11DeviceContext* context_;

	// �R�����X�e�[�g
	std::unique_ptr<DirectX::CommonStates> states_;

	// �X�v���C�g�o�b�`
	std::unique_ptr<DirectX::SpriteBatch> spriteBatch_;

	// �L�[�{�[�h�֌W
	std::unique_ptr<DirectX::Keyboard> keyboard_;
	std::unique_ptr<DirectX::Keyboard::KeyboardStateTracker> keyTracker_;

private:
	friend class SingletonDirector<DXTKManager>;

	// �R���X�g���N�^
	DXTKManager() 
	{
		// �L�[�{�[�h�֌W�̏�����
		keyboard_ = std::make_unique<DirectX::Keyboard>();
		keyTracker_ = std::make_unique <DirectX::Keyboard::KeyboardStateTracker>();
	}

public:

	// ����������
	void Initializer(ID3D11Device* device, ID3D11DeviceContext* context)
	{
		device_ = device;
		context_ = context;

		// �R�����X�e�[�g���쐬
		states_ = std::make_unique<DirectX::CommonStates>(device);

		// �X�v���C�g�o�b�`
		spriteBatch_ = std::make_unique<DirectX::SpriteBatch>(context);
	}

	// �X�e�[�g�̍X�V����
	void UpdateInputState()
	{
		// �L�[���͏����擾
		DirectX::Keyboard::State key = keyboard_->GetState();
		keyTracker_->Update(key);
	}
};