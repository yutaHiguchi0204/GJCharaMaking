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
	};

private:
	enum COLUMN_DATA
	{
		NONE = -1,
		PARTS_NO,
		MODEL_DATA
	};

	// ファイル名
	const std::wstring PARTS_DATA_FILE_NAME = L"Resources/CharaData/charaData.csv";
	const std::wstring PARTS_GENRE_DATA_FILE_NAME = L"Resources/CharaData/partsGenreData.csv";

	// キャラパーツデータ
	std::vector<PartsData> charaPartsData_[CHARA_PARTS_NUM];

	// パーツジャンルデータ
	std::vector<std::wstring> partsGenreData_;

	// パーツ数
	int partsCount_[CHARA_PARTS_NUM];

	// 現在のパーツジャンル
	CHARA_PARTS charaParts_;

	// 現在のパーツデータ
	PartsData modelData_[CHARA_PARTS_NUM];

private:
	friend class SingletonDirector<CharaData>;

	// constructor
	CharaData() {};

public:
	// パーツデータの読み込み
	void ImportData();
	void ImportGenreData();

	// 全パーツデータの取得
	inline std::vector<PartsData> GetPartsData(CHARA_PARTS parts) const { return charaPartsData_[parts]; }
	inline std::vector<std::wstring> GetPartsGenreData() const { return partsGenreData_; }

	// パーツ数の取得
	inline int GetPartsCount(CHARA_PARTS charaParts) const { return partsCount_[charaParts]; }

	// 現在のパーツジャンル
	void SetPartsGenre(CHARA_PARTS charaParts) { charaParts_ = charaParts; }
	inline CHARA_PARTS GetPartsGenre() const { return charaParts_; }

	// 現在のモデルデータ
	void SetModelData(const CHARA_PARTS charaParts, const PartsData& data) { modelData_[charaParts] = data; }
	inline const PartsData& GetModelData(CHARA_PARTS charaParts) const { return modelData_[charaParts]; }
};