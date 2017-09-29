/* =====================================================================
//! @param		「CollisionManager」class header
//! @create		Yuta Higuchi
//! @date		17/09/29
===================================================================== */
#pragma once

// including header
#include "SingletonDirector.h"
#include <d3d11_1.h>
#include <SimpleMath.h>

// class
class CollisionManager : public SingletonDirector<CollisionManager>
{
private:
	friend class SingletonDirector<CollisionManager>;

	// constructor
	CollisionManager() {};

public:
	// マウスポインタとパネルの当たり判定
	bool IsPointerHit(const DirectX::SimpleMath::Vector2& mousePos, const DirectX::SimpleMath::Vector2& panelPos)
	{
		// 判定
		if (false/* ここで各座標を使ってチェック */)
		{
			return true;
		}

		return false;
	}
};