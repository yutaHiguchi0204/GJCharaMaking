/*===============================================================
// @param	[PartsView] class header
// @create	Yuki Matsumaru
// @date	17/09/27
================================================================*/
#pragma once

// including header
#include "Resource2D.h"
#include <vector>
#include "CharaData.h"
#include "PartsGenrePanel.h"
#include "PartsPanel.h"

// class
class PartsView : public Resource2D
{
private:
	std::vector<PartsGenrePanel*> partsGenrePanel_;								// �W�������{�^��
	std::vector<PartsPanel*> partsPanel_[CharaData::CHARA_PARTS_NUM];			// �p�[�c�{�^��

public:
	PartsView() {};
	virtual ~PartsView() {};

	void LoadPanel();			// �S�p�l�������[�h
	void DrawPanel();			// �S�p�l����`��
};