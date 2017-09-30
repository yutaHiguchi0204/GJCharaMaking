/*===============================================================
// @param	�uPanel�vclass header
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
	int panelNo_;				// �p�[�c�p�l���ԍ�

public:
	Panel() {};
	virtual ~Panel() {};

	// �p�[�c�p�l���ԍ�
	virtual void SetPanelNo(int panelNo) { panelNo_ = panelNo; }
	virtual inline const int GetPanelNo() { return panelNo_; }
};