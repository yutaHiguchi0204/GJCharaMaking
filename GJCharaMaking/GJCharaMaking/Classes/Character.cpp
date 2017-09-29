/*===============================================================
// @param	[Character] class src
// @create	Yuki Matsumaru
// @date	17/09/26
================================================================*/

// including header
#include "Character.h"

// namespace
using namespace DirectX;
using namespace DirectX::SimpleMath;
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

	// ��]�p�̐ݒ�
	rot = 0.0f;
	GetRootParts()->SetRotate(Vector3(0, rot, 0));
}

// =================================================
// @brief	�p�[�c�̕ύX
// @param	�p�[�c�W�������iCHARA_PARTS�j�A�p�[�c�f�[�^�iPartsData�j
// @return	none
// =================================================
void Character::ChangeParts(CharaData::CHARA_PARTS charaParts, CharaData::PartsData partsData)
{
	// �p�[�c�̍X�V
	CharaData& data = CharaData::GetInstance();
	data.SetModelData(charaParts, partsData);

	// ���f������U�j�����A�V�����o��
	parts_.clear();
	Initialize(CharaData::CHARA_PARTS_NUM);
}