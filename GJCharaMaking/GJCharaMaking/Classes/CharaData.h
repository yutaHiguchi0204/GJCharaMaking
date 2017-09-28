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
public:
	enum CHARA_PARTS
	{
		HEAD,
		BODY,
		LEG,

		CHARA_PARTS_NUM
	};

private:
	enum COLUMN_DATA
	{
		NONE = -1,
		PARTS_NO,
		MODEL_DATA,
		PANEL_DATA
	};

	struct PartsData
	{
		int partsNo;						// �p�[�c�ԍ�
		std::wstring modelFileData;			// �p�[�c���f���̃t�@�C����
		std::wstring panelFileData;			// �p�l���̃t�@�C����
	};

	// �t�@�C����
	const std::wstring PARTS_DATA_FILE_NAME = L"Resources/CharaData/charaData.csv";

	// �L�����p�[�c�f�[�^
	std::vector<PartsData> charaPartsData[CHARA_PARTS_NUM];

private:
	friend class SingletonDirector<CharaData>;

	// constructor
	CharaData() {};

public:
	// �p�[�c�f�[�^�̓ǂݍ���
	void ImportData();
};