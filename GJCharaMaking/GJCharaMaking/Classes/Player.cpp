/*===============================================================
// @param	[Player] class src
// @create	Kazushi Shinohara
// @date	17/09/27
================================================================*/

// including header
#include "Player.h"
#include "CharaData.h"

// namespace
using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace std;

// method

// =================================================
// @brief	update
// @param	none
// @return	none
// =================================================
void Player::Update()
{
	for (auto parts : parts_)
	{
		parts->Update();
	}

	// ���[�e�[�V����������
	rot -= 0.01f;
	GetRootParts()->SetRotate(Vector3(0, rot, 0));
}

// =================================================
// @brief	���f���̓ǂݍ���
// @param	none
// @return	none
// =================================================
void Player::LoadModel()
{
	CharaData& data = CharaData::GetInstance();

	// ���f���Ǎ�
	parts_.at(CharaData::HEAD)->LoadModel(data.GetModelData(CharaData::HEAD));
	parts_.at(CharaData::BODY)->LoadModel(data.GetModelData(CharaData::BODY));
	parts_.at(CharaData::LEG)->LoadModel(data.GetModelData(CharaData::LEG));
}

// =================================================
// @brief	�p�[�c�̐e�q�֌W�̍\�z
// @param	none
// @return	none
// =================================================
void Player::SetParentParts()
{
	parts_.at(CharaData::BODY)->SetParent(parts_.at(CharaData::LEG).get());
	parts_.at(CharaData::HEAD)->SetParent(parts_.at(CharaData::BODY).get());
}

// =================================================
// @brief	�p�[�c�̃��[�J�����W�̐ݒ�
// @param	none
// @return	none
// =================================================
void Player::SetOffset()
{
	parts_.at(CharaData::BODY)->SetTranslate(Vector3(0, 0, 0));
	parts_.at(CharaData::HEAD)->SetTranslate(Vector3(0, 0, 0));
}