/* =====================================================================
//! @param		�uCharaData�vclass header
//! @create		Yuta Higuchi
//! @date		17/09/27
===================================================================== */
#pragma once

// including header
#include "SingletonDirector.h"
#include <map>
#include <string>
#include <vector>

// class
class CharaData : public SingletonDirector<CharaData>
{
private:
	enum CHARA_PARTS
	{
		HEAD,
		BODY,
		LEG,

		CHARA_PARTS_NUM
	};

	// �t�@�C����
	const std::wstring PARTS_DATA_FILE_NAME = L"Resources/CharaData/charaData.csv";

	// �L�����p�[�c�f�[�^
	std::vector<std::wstring> charaPartsData[CHARA_PARTS_NUM];

private:
	friend class SingletonDirector<CharaData>;

	// constructor
	CharaData() {};

public:
	// �p�[�c�f�[�^�̓ǂݍ���
	void ImportData();
};