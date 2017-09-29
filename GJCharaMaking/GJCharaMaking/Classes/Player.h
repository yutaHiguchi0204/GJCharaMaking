/*===============================================================
// @param	[Player] class header
// @create	Kazushi Shinohara
// @date	17/09/27
================================================================*/
#pragma once

// include
#include "Character.h"

// class
class Player : public Character
{
public:
	Player() {};
	~Player() {};

	void LoadModel() override;				// ���f���̓ǂݍ���
	void SetParentParts() override;			// �p�[�c�̐e�q�֌W�̍\�z
	void SetOffset() override;				// �p�[�c�̃��[�J�����W�̐ݒ�
};

