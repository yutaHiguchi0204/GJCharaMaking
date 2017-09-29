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
// @return	none
// =================================================
void KeyboardDebuger::ChangeCharaParts()
{
	DXTKManager& dxtk = DXTKManager::GetInstance();
	Keyboard::State state = dxtk.keyTracker_->pressed;
	CharaData& data = CharaData::GetInstance();

	// �㉺�L�[�ŃW�������I��
	if (state.Up)
	{
		data.SetPartsGenre((CharaData::CHARA_PARTS)(data.GetPartsGenre() - 1));
		if (data.GetPartsGenre() < CharaData::HEAD)
		{
			data.SetPartsGenre((CharaData::CHARA_PARTS)(CharaData::CHARA_PARTS_NUM - 1));
		}
	}
	else if (state.Down)
	{
		data.SetPartsGenre((CharaData::CHARA_PARTS)(data.GetPartsGenre() + 1));
		if (data.GetPartsGenre() >= CharaData::CHARA_PARTS_NUM)
		{
			data.SetPartsGenre((CharaData::CHARA_PARTS)CharaData::HEAD);
		}
	}
	// ���E�L�[�Ńp�[�c�I��
	else if (state.Left)
	{
		
	}
	else if (state.Right)
	{

	}
}