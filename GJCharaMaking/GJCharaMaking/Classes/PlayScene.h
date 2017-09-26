/*===============================================================
// @param	[PlayScene] class header
// @create	Kazushi Shinohara
// @date	17/09/26
================================================================*/
#pragma once

// include
#include "Scene.h"

//class
class PlayScene : public Scene
{
public:
	PlayScene() {};
	~PlayScene() {};

	void Update();			// update
	void Draw();			// draw
};

