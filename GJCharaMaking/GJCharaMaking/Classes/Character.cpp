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
	// 可変長配列の設定
	parts_.resize(partsNum);

	// インスタンス設定
	for (int i = 0; i < partsNum; i++)
	{
		parts_.at(i) = make_shared<Object>();
	}

	// モデルの読み込み
	this->LoadModel();

	// パーツの親子関係の構築
	this->SetParentParts();

	// パーツのローカル座標の設定
	this->SetOffset();

	// 回転角の設定
	rot = 0.0f;
	GetRootParts()->SetRotate(Vector3(0, rot, 0));
}

// =================================================
// @brief	パーツの変更
// @param	パーツジャンル（CHARA_PARTS）、パーツデータ（PartsData）
// @return	none
// =================================================
void Character::ChangeParts(CharaData::CHARA_PARTS charaParts, CharaData::PartsData partsData)
{
	// パーツの更新
	CharaData& data = CharaData::GetInstance();
	data.SetModelData(charaParts, partsData);

	// モデルを一旦破棄し、新しく出す
	parts_.clear();
	Initialize(CharaData::CHARA_PARTS_NUM);
}