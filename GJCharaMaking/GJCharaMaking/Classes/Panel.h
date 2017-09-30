/*===============================================================
// @param	「Panel」class header
// @create	Yuta Higuchi
// @date	17/09/30
================================================================*/
#pragma once

// including header
#include "Resource2D.h"

// class
class Panel : public Resource2D
{
protected:
	int panelNo_;				// パーツパネル番号

public:
	Panel() {};
	virtual ~Panel() {};

	// パーツパネル番号
	virtual void SetPanelNo(int panelNo) { panelNo_ = panelNo; }
	virtual inline const int GetPanelNo() { return panelNo_; }
};