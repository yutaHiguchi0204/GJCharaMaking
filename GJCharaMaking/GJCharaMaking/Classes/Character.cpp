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
}