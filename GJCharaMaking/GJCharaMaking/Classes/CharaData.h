/* =====================================================================
//! @param		「CharaData」class header
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

	// ファイル名
	const std::wstring PARTS_DATA_FILE_NAME = L"Resources/CharaData/charaData.csv";

	// キャラパーツデータ
	std::vector<std::wstring> charaPartsData[CHARA_PARTS_NUM];

private:
	friend class SingletonDirector<CharaData>;

	// constructor
	CharaData() {};

public:
	// パーツデータの読み込み
	void ImportData();
};