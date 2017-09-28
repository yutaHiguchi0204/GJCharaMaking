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

// �N���X�̒�`
class DXTKManager : public SingletonDirector<DXTKManager>
{
public:
	ID3D11Device* m_device;
	ID3D11DeviceContext* m_context;

	// �R�����X�e�[�g
	std::unique_ptr<DirectX::CommonStates> m_states;

	// �X�v���C�g�o�b�`
	std::unique_ptr<DirectX::SpriteBatch> m_spriteBatch;

private:
	friend class SingletonDirector<DXTKManager>;

	// �R���X�g���N�^
	DXTKManager() {}

public:

	// ����������
	void Initializer(ID3D11Device* device, ID3D11DeviceContext* context)
	{
		m_device = device;
		m_context = context;

		// �R�����X�e�[�g���쐬
		m_states = std::make_unique<DirectX::CommonStates>(device);

		// �X�v���C�g�o�b�`
		m_spriteBatch = std::make_unique<DirectX::SpriteBatch>(context);
	}

	// �X�e�[�g�̍X�V����
	void UpdateInputState()
	{
	}
};