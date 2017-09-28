/*===============================================================
// @param	[Character] class header
// @create	Yuki Matsumaru
// @date	17/09/26
================================================================*/
#pragma once

// including header
#include "IModel.h"

// class
class Character : public IModel
{
public:
	Character() {};
	~Character() {};

	virtual void Initialize(int partsNum);				// 初期化

	virtual void LoadModel() = 0;						// モデルデータの読み込み
	virtual void SetParentParts() = 0;					// パーツの親子関係を構築
	virtual void SetOffset() = 0;						// パーツのローカル座標の設定
};