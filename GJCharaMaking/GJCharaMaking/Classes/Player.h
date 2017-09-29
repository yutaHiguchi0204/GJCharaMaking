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
public:
	Player() {};
	~Player() {};

	void LoadModel() override;				// モデルの読み込み
	void SetParentParts() override;			// パーツの親子関係の構築
	void SetOffset() override;				// パーツのローカル座標の設定
};

