/* =====================================================================
//! @param		�uKeyboardDebuger�vclass src
//! @create		Yuta Higuchi
//! @date		17/09/29
===================================================================== */

// including header
#include "KeyboardDebuger.h"
#include "CharaData.h"
#include "DXTKManager.h"

// namespace
using namespace DirectX;
using namespace std;

// method

// =================================================
// @brief	update
// @param	none
// @return	none
// =================================================
void KeyboardDebuger::Update()
{
	DXTKManager& dxtk = DXTKManager::GetInstance();
	dxtk.UpdateInputState();
}

// =================================================
// @brief	�p�[�c�ύX
// @param	none
// @return	�p�[�c�̕ύX���������ǂ����ibool�j�@���W�������ύX��true�ɂȂ�Ȃ�
// =================================================
bool KeyboardDebuger::ChangeCharaParts()
{
	DXTKManager& dxtk = DXTKManager::GetInstance();
	Keyboard::State state = dxtk.keyTracker_->pressed;
	CharaData& data = CharaData::GetInstance();

	// �㉺�L�[�ŃW�������I��
	if (state.Up)
	{
		data.SetPartsGenre(
			(data.GetPartsGenre() - 1 < CharaData::HEAD)
			? (CharaData::CHARA_PARTS)(CharaData::CHARA_PARTS_NUM - 1)
			: (CharaData::CHARA_PARTS)(data.GetPartsGenre() - 1)
		);
	}
	else if (state.Down)
	{
		data.SetPartsGenre(
			(data.GetPartsGenre() + 1 >= CharaData::CHARA_PARTS_NUM)
			? CharaData::HEAD
			: (CharaData::CHARA_PARTS)(data.GetPartsGenre() + 1)
		);
	}
	// ���E�L�[�Ńp�[�c�I��
	else if (state.Left)
	{
		data.SetModelData(
			data.GetPartsGenre(),
			(data.GetModelData(data.GetPartsGenre()).partsNo - 1 <= 0)
			? (data.GetPartsData(data.GetPartsGenre()).at(data.GetPartsCount(data.GetPartsGenre()) - 1))
			: (data.GetPartsData(data.GetPartsGenre()).at(data.GetModelData(data.GetPartsGenre()).partsNo - 2))
		);

		return true;
	}
	else if (state.Right)
	{
		data.SetModelData(
			data.GetPartsGenre(),
			(data.GetModelData(data.GetPartsGenre()).partsNo + 1 > data.GetPartsCount(data.GetPartsGenre()))
			? (data.GetPartsData(data.GetPartsGenre()).at(0))
			: (data.GetPartsData(data.GetPartsGenre()).at(data.GetModelData(data.GetPartsGenre()).partsNo))
		);

		return true;
	}

	return false;
}

// =================================================
// @brief	�J�����𓮂����i�v���C���[���j
// @param	none
// @return	none
// =================================================
void KeyboardDebuger::MoveCamera(const shared_ptr<Camera>& camera)
{
	DXTKManager& dxtk = DXTKManager::GetInstance();
	Keyboard::State state = dxtk.keyTracker_->pressed;

	// ���E�L�[�ŃJ�����𓮂���
	if (state.Left)
	{
		// ��Œǉ��\��
	}
	else if (state.Right)
	{
		// ��Œǉ��\��
	}
}