/*===============================================================
// @param	[Player] class header
// @create	Kazushi Shinohara
// @date	17/09/27
================================================================*/

#pragma once

// include
#include "Character.h"
#include <d3d11_1.h>
#include <SimpleMath.h>
#include <vector>

// class
class Player : public Character
{
private:	
	enum PARTS {
		PARTS_LEG,
		PARTS_BODY,
		PARTS_HEAD,

		PARTS_NUM,
	};

public:

	Player();
	~Player();

	void Initialize(); 
	void Update() override;
	void Draw() override;

};

