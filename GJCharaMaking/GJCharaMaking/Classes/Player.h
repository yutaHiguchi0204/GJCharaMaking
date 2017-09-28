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
private:
	float rot = 180.0f;						// ��]�p

public:
	Player() {};
	~Player() {};

	void Update() override;					// �X�V����

	void LoadModel() override;				// ���f���̓ǂݍ���
	void SetParentParts() override;			// �p�[�c�̐e�q�֌W�̍\�z
	void SetOffset() override;				// �p�[�c�̃��[�J�����W�̐ݒ�
};

