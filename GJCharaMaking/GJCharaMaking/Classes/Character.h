/*===============================================================
// @param	[Character] class header
// @create	Yuki Matsumaru
// @date	17/09/26
================================================================*/
#pragma once

// including header
#include "IModel.h"
#include "CharaData.h"

// class
class Character : public IModel
{
protected:
	float rot;		// 回転角

public:
	Character() {};
	~Character() {};

	virtual void Initialize(int partsNum);																// 初期化

	virtual void LoadModel() = 0;																		// モデルデータの読み込み
	virtual void SetParentParts() = 0;																	// パーツの親子関係を構築
	virtual void SetOffset() = 0;																		// パーツのローカル座標の設定

	virtual void ChangeParts(CharaData::CHARA_PARTS charaParts, CharaData::PartsData partsData);		// パーツの変更
};