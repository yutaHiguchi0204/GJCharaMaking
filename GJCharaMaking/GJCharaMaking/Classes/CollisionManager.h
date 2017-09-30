/* =====================================================================
//! @param		�uCollisionManager�vclass header
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
	// �}�E�X�|�C���^�ƃp�l���̓����蔻��
	bool IsPointerHit(const DirectX::SimpleMath::Vector2& mousePos, const DirectX::SimpleMath::Vector2& panelPos
	                 ,const DirectX::SimpleMath::Vector2& Size)
	{
		// ����
		if ((panelPos.x < mousePos.x  && mousePos.x  <= panelPos.x + Size.x) && 
			(panelPos.y < mousePos.y  && mousePos.y  <= panelPos.y + Size.y))
		{
			return true;
		}

		return false;
	}
};