/*===============================================================
// @param	[Player] class src
// @create	Kazushi Shinohara
// @date	17/09/27
================================================================*/

// including header
#include "Player.h"

// namespace
using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace std;

// method

// =================================================
// @brief	モデルの読み込み
// @param	none
// @return	none
// =================================================
void Player::LoadModel()
{
	CharaData& data = CharaData::GetInstance();

	// モデル読込
	parts_.at(CharaData::HEAD)->LoadModel(data.GetModelData(CharaData::HEAD).modelFileData);
	parts_.at(CharaData::BODY)->LoadModel(data.GetModelData(CharaData::BODY).modelFileData);
	parts_.at(CharaData::LEG)->LoadModel(data.GetModelData(CharaData::LEG).modelFileData);
}

// =================================================
// @brief	パーツの親子関係の構築
// @param	none
// @return	none
// =================================================
void Player::SetParentParts()
{
	parts_.at(CharaData::BODY)->SetParent(parts_.at(CharaData::LEG).get());
	parts_.at(CharaData::HEAD)->SetParent(parts_.at(CharaData::BODY).get());
}

// =================================================
// @brief	パーツのローカル座標の設定
// @param	none
// @return	none
// =================================================
void Player::SetOffset()
{
	parts_.at(CharaData::BODY)->SetTranslate(Vector3(0, 0, 0));
	parts_.at(CharaData::HEAD)->SetTranslate(Vector3(0, 0, 0));
}