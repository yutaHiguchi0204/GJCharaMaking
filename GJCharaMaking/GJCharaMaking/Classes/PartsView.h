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
	const DirectX::SimpleMath::Vector2 ViewPos = DirectX::SimpleMath::Vector2(32.0f, 32.0f);

private:
	std::vector<PartsGenrePanel*> partsGenrePanel_;								// �W�������{�^��
	std::vector<PartsPanel*> partsPanel_[CharaData::CHARA_PARTS_NUM];			// �p�[�c�{�^��
	std::unique_ptr<Resource2D> partsGenreFrame_;								// �W�������g
	std::unique_ptr<Resource2D> partsPanelFrame_;								// �p�[�c�p�l���g

public:
	PartsView() { pos_ = ViewPos; };
	virtual ~PartsView() {};

	void Update();				// update

	void LoadPanel();			// �S�p�l�������[�h
	void DrawPanel();			// �S�p�l����`��

	// �p�[�c���擾
	inline const std::vector<PartsGenrePanel*>& GetPartsGenrePanel() { return partsGenrePanel_; }
	inline const std::vector<PartsPanel*>& GetPartsPanel(CharaData::CHARA_PARTS charaParts) { return partsPanel_[charaParts]; }
};