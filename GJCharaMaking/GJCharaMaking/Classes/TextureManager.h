/* =====================================================================
//! @param		�uTextureManager�v�N���X�̃w�b�_�t�@�C��
//! @create		����@�T��
//! @date		17/06/05
===================================================================== */
#pragma once

// �w�b�_�t�@�C���̃C���N���[�h
#include "SingletonDirector.h"

#include <CommonStates.h>
#include <d3d11_1.h>
#include <SimpleMath.h>
#include <SpriteBatch.h>
#include <string>
#include "Constant.h"

// �N���X�̒�`
class TextureManager : public SingletonDirector<TextureManager>
{
public:
	ID3D11Device* device_;
	ID3D11DeviceContext* context_;
	ID3D11BlendState* blendState_;

private:
	friend class SingletonDirector<TextureManager>;

	// �R���X�g���N�^
	TextureManager() { blendState_ = NULL; };

public:

	// ����������
	void Initializer(ID3D11Device* device, ID3D11DeviceContext* context);

	// �e�N�X�`���̃��[�h
	void Load(std::wstring file, ID3D11ShaderResourceView** texture);

	// �u�����h�X�e�[�g�̐ݒ�
	void SetBlendState();

	// �e�N�X�`���̕`��
	void Draw(
		ID3D11ShaderResourceView* texture,													// �e�N�X�`���n���h��
		DirectX::SimpleMath::Vector2 pos,													// �\�����W
		float angle = 0.0f,																	// ��]�p
		DirectX::SimpleMath::Vector2 textureSize = DirectX::SimpleMath::Vector2(0, 0),		// �e�N�X�`���T�C�Y
		DirectX::SpriteEffects flip = DirectX::SpriteEffects::SpriteEffects_None			// ���]����
	);
	void Draw(
		ID3D11ShaderResourceView* texture,													// �e�N�X�`���n���h��
		DirectX::SimpleMath::Vector2 pos,													// �\�����W
		DirectX::SimpleMath::Vector2 rectPos,												// �؂����`�̊J�n�ʒu
		DirectX::SimpleMath::Vector2 rectSize,												// �؂����`�T�C�Y
		float angle = 0.0f,																	// ��]�p
		DirectX::SimpleMath::Vector2 textureSize = DirectX::SimpleMath::Vector2(0, 0),		// �e�N�X�`���T�C�Y
		DirectX::SpriteEffects flip = DirectX::SpriteEffects::SpriteEffects_None			// ���]����
	);
};