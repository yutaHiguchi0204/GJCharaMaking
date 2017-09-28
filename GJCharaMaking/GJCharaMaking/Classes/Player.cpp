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
	for (auto itr = parts_.begin(); itr != parts_.end(); itr++)
	{
		(*itr)->Update();
	}

	// ローテーションさせる
	rot += 0.01f;
	GetRootParts()->SetRotate(Vector3(0, rot, 0));
}

// =================================================
// @brief	モデルの読み込み
// @param	none
// @return	none
// =================================================
void Player::LoadModel()
{
	// モデル読込
	parts_.at(CharaData::HEAD)->LoadModel(L"Head3");
	parts_.at(CharaData::BODY)->LoadModel(L"Body2");
	parts_.at(CharaData::LEG)->LoadModel(L"Leg2");
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