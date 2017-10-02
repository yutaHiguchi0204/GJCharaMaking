/*===============================================================
// @param	ÅuSceneChangerButtonÅvclass header
// @create	Yuta Higuchi
// @date	17/10/02
================================================================*/
#pragma once

// including header
#include "Resource2D.h"
#include <string>

// class
class SceneChangerButton : public Resource2D
{
public:
	SceneChangerButton() {};
	virtual ~SceneChangerButton() {};

	void Initialize(const std::wstring file) override;
};