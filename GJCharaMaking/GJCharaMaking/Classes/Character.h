/*===============================================================
// @param	[Character] class header
// @create	Yuki Matsumaru
// @date	17/09/26
================================================================*/
#pragma once

// including header
#include <string>
#include <vector>
#include "IModel.h"

// class
class Character : public IModel
{
public:
	Character() {};
	~Character() {};

	virtual void Initialize(const std::wstring file) override;
	virtual void Update() override;
	virtual void Draw() override;

	virtual void LoadModel() = 0;                     // モデルデータの読み込み
	virtual void SetParentModel() = 0;                // モデルの親子関係を構築
	virtual void SetOffset() = 0;                     // モデルのオフセットをセット
};