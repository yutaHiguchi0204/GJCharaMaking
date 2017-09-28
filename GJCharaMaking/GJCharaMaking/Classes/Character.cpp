/*===============================================================
// @param	[Character] class src
// @create	Yuki Matsumaru
// @date	17/09/26
================================================================*/

// including header
#include "Character.h"

// namespace
using namespace std;

// method

// =================================================
// @brief	initialize
// @param	none
// @return	none
// =================================================
void Character::Initialize(int partsNum)
{
	// �ϒ��z��̐ݒ�
	parts_.resize(partsNum);

	// �C���X�^���X�ݒ�
	for (int i = 0; i < partsNum; i++)
	{
		parts_.at(i) = make_shared<Object>();
	}

	// ���f���̓ǂݍ���
	this->LoadModel();

	// �p�[�c�̐e�q�֌W�̍\�z
	this->SetParentParts();

	// �p�[�c�̃��[�J�����W�̐ݒ�
	this->SetOffset();
}