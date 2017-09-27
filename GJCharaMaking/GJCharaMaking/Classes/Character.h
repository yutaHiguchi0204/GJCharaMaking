/*===============================================================
// @param	[Character] class header
// @create	Yuki Matsumaru
// @date	17/09/26
================================================================*/
#pragma once

// including header
#include <string>
#include <vector>
#include "IModel.h"

// class
class Character : public IModel
{
public:
	Character() {};
	~Character() {};

	virtual void Initialize(const std::wstring file) override;
	virtual void Update() override;
	virtual void Draw() override;

	virtual void LoadModel() = 0;                     // ���f���f�[�^�̓ǂݍ���
	virtual void SetParentModel() = 0;                // ���f���̐e�q�֌W���\�z
	virtual void SetOffset() = 0;                     // ���f���̃I�t�Z�b�g���Z�b�g
};