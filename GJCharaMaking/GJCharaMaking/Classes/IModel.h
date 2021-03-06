/* =====================================================================
//! @param		「IModel」class header
//! @create		Yuta Higuchi
//! @date		17/09/27
===================================================================== */
#pragma once

// including header
#include <CommonStates.h>
#include <string>
#include <vector>
#include "Object.h"

// class
class IModel
{
protected:
	std::vector<std::shared_ptr<Object>> parts_;			// パーツ情報

public:
	IModel() {};
	virtual ~IModel() {};

	virtual void Initialize(const std::wstring file);		// initialize
	virtual void Update();									// update
	virtual void Draw();									// draw

	inline const std::shared_ptr<Object>& GetRootParts() { return parts_.back(); }
};