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
public:
	enum CHARA_PARTS
	{
		HEAD,
		BODY,
		LEG,

		CHARA_PARTS_NUM
	};

	struct PartsData
	{
		int partsNo;						// パーツ番号
		std::wstring modelFileData;			// パーツモデルのファイル名
		std::wstring panelFileData;			// パネルのファイル名
	};

private:
	enum COLUMN_DATA
	{
		NONE = -1,
		PARTS_NO,
		MODEL_DATA,
		PANEL_DATA
	};

	// ファイル名
	const std::wstring PARTS_DATA_FILE_NAME = L"Resources/CharaData/charaData.csv";
	const std::wstring PARTS_GENRE_DATA_FILE_NAME = L"Resources/CharaData/partsGenreData.csv";

	// キャラパーツデータ
	std::vector<PartsData> charaPartsData[CHARA_PARTS_NUM];

	// パーツジャンルデータ
	std::vector<std::wstring> partsGenreData;

	// 現在のパーツデータ
	std::wstring modelData[CHARA_PARTS_NUM];

private:
	friend class SingletonDirector<CharaData>;

	// constructor
	CharaData() {};

public:
	// パーツデータの読み込み
	void ImportData();
	void ImportGenreData();

	// 全パーツデータの取得
	std::vector<PartsData>* GetPartsData() { return charaPartsData; }
	std::vector<std::wstring> GetPartsGenreData() { return partsGenreData; }

	// 現在のモデルデータ
	void SetModelData(CHARA_PARTS charaParts, std::wstring file) { modelData[charaParts] = file; }
	std::wstring GetModelData(CHARA_PARTS charaParts) { return modelData[charaParts]; }
};