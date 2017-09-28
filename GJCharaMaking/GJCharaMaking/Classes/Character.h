/*===============================================================
// @param	[Character] class header
// @create	Yuki Matsumaru
// @date	17/09/26
================================================================*/
#pragma once

// including header
#include "IModel.h"

// class
class Character : public IModel
{
public:
	Character() {};
	~Character() {};

	virtual void Initialize(int partsNum);				// ������

	virtual void LoadModel() = 0;						// ���f���f�[�^�̓ǂݍ���
	virtual void SetParentParts() = 0;					// �p�[�c�̐e�q�֌W���\�z
	virtual void SetOffset() = 0;						// �p�[�c�̃��[�J�����W�̐ݒ�
};