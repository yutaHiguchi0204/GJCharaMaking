/* =====================================================================
//! @param		�uDXTKManager�v�N���X�̃w�b�_�t�@�C��
//! @create		����@�T��
//! @date		17/06/05
===================================================================== */
#pragma once

// �w�b�_�t�@�C���̃C���N���[�h
#include "SingletonDirector.h"

#include <CommonStates.h>
#include <SpriteBatch.h>
#include <Mouse.h>

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

	//�}�E�X
	std::unique_ptr<DirectX::Mouse> mouse_;
	std::unique_ptr<DirectX::Mouse::ButtonStateTracker> mouseTracker_;

private:
	friend class SingletonDirector<DXTKManager>;

	// �R���X�g���N�^
	DXTKManager() {}

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

		//�}�E�X
		mouse_ = std::make_unique<DirectX::Mouse>();
		mouseTracker_ = std::make_unique<DirectX::Mouse::ButtonStateTracker>();
	}

	// �X�e�[�g�̍X�V����
	void UpdateInputState()
	{
		// �}�E�X�����擾
		Mouse::State mouse = mouse_->GetState();
		mouseTracker_->Update(mouse);
	}
};