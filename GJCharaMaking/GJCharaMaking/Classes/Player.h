/*===============================================================
// @param	[Player] class header
// @create	Kazushi Shinohara
// @date	17/09/27
================================================================*/
#pragma once

// include
#include "Character.h"

// class
class Player : public Character
{
private:
	float rot = 180.0f;						// 回転角

public:
	Player() {};
	~Player() {};

	void Update() override;					// 更新処理

	void LoadModel() override;				// モデルの読み込み
	void SetParentParts() override;			// パーツの親子関係の構築
	void SetOffset() override;				// パーツのローカル座標の設定
};

