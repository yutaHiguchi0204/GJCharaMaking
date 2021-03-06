/* =====================================================================
//! @param		「KeyboardDebuger」class src
//! @create		Yuta Higuchi
//! @date		17/09/29
===================================================================== */

// including header
#include "KeyboardDebuger.h"
#include "CharaData.h"
#include "DXTKManager.h"
#include "SoundManager.h"

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
void KeyboardDebuger::Update()
{
	DXTKManager& dxtk = DXTKManager::GetInstance();
	dxtk.UpdateInputState();
}

// =================================================
// @brief	パーツ変更
// @param	none
// @return	パーツの変更をしたかどうか（bool）　※ジャンル変更はtrueにならない
// =================================================
bool KeyboardDebuger::ChangeCharaParts()
{
	DXTKManager& dxtk = DXTKManager::GetInstance();
	Keyboard::State state = dxtk.keyTracker_->pressed;
	CharaData& data = CharaData::GetInstance();

	// 上下キーでジャンル選択
	if (state.Up)
	{
		data.SetPartsGenre(
			(data.GetPartsGenre() - 1 < CharaData::ACCESSORY)
			? (CharaData::CHARA_PARTS)(CharaData::CHARA_PARTS_NUM - 1)
			: (CharaData::CHARA_PARTS)(data.GetPartsGenre() - 1)
		);

		// SEの再生
		SoundManager& sound = SoundManager::GetInstance();
		sound.PlayAudio(SoundManager::SOUND::PARTS_CHANGE_SE);
	}
	else if (state.Down)
	{
		data.SetPartsGenre(
			(data.GetPartsGenre() + 1 >= CharaData::CHARA_PARTS_NUM)
			? CharaData::ACCESSORY
			: (CharaData::CHARA_PARTS)(data.GetPartsGenre() + 1)
		);

		// SEの再生
		SoundManager& sound = SoundManager::GetInstance();
		sound.PlayAudio(SoundManager::SOUND::PARTS_CHANGE_SE);
	}
	// 左右キーでパーツ選択
	else if (state.Left)
	{
		data.SetModelData(
			data.GetPartsGenre(),
			(data.GetModelData(data.GetPartsGenre()).partsNo - 1 < 0)
			? (data.GetPartsData(data.GetPartsGenre()).at(data.GetPartsCount(data.GetPartsGenre()) - 1))
			: (data.GetPartsData(data.GetPartsGenre()).at(data.GetModelData(data.GetPartsGenre()).partsNo - 1))
		);

		return true;
	}
	else if (state.Right)
	{
		data.SetModelData(
			data.GetPartsGenre(),
			(data.GetModelData(data.GetPartsGenre()).partsNo + 1 >= data.GetPartsCount(data.GetPartsGenre()))
			? (data.GetPartsData(data.GetPartsGenre()).at(0))
			: (data.GetPartsData(data.GetPartsGenre()).at(data.GetModelData(data.GetPartsGenre()).partsNo + 1))
		);

		return true;
	}

	return false;
}

// =================================================
// @brief	カメラを動かす（プレイヤー軸）
// @param	none
// @return	none
// =================================================
void KeyboardDebuger::MoveCamera(const shared_ptr<Camera>& camera)
{
	DXTKManager& dxtk = DXTKManager::GetInstance();
	Keyboard::State state = dxtk.keyboard_->GetState();

	// 左右キーでカメラを動かす
	if (state.Left)
	{
		camera->SetAngle(camera->GetAngle() + 0.02f);
	}
	else if (state.Right)
	{
		camera->SetAngle(camera->GetAngle() - 0.02f);
	}

	// カメラの更新
	float cameraAngle = camera->GetAngle();
	camera->SetEyePos(Vector3(cosf(cameraAngle) * 25.0f, 10.0f, sinf(cameraAngle) * 25.0f));
}