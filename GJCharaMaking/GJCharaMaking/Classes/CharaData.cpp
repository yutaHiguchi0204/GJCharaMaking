/* =====================================================================
//! @param		「CharaData」class src
//! @create		Yuta Higuchi
//! @date		17/09/27
===================================================================== */

// including header
#include "CharaData.h"
#include <cassert>
#include <codecvt>
#include <d3d11_1.h>
#include <fstream>
#include <locale> 
#include <sstream>

// namespace
using namespace std;

// method

// =================================================
// @brief	パーツデータの読み込み
// @param	CSVファイル名（wstring）
// @return	none
// =================================================
void CharaData::ImportData()
{
	// ファイル読み込み
	ifstream ifs(PARTS_DATA_FILE_NAME);

	// エラー処理
	if (!ifs)
	{
		OutputDebugString(L"This csv file is unknown.");
		assert(0);
	}

	// データをレコードごとに取得
	string data;
	std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> cv;
	vector<wstring> tmp;
	while (getline(ifs, data)) {
		string token;
		istringstream stream(data);

		// カンマ区切り
		while (getline(stream, token, ',')) {
			tmp.push_back(cv.from_bytes(token));
		}
	}

	// ファイルを閉じる
	ifs.close();

	// データ登録
	int partsNum = NONE;
	for (auto itr = tmp.begin(); itr != tmp.end();)
	{
		PartsData data;

		if (stoi(*itr) == 0)
		{
			// パネル番号を設定
			partsNum++;
		}

		// モデル、パーツそれぞれのファイル名を設定
		data.partsNo = stoi(*(itr++));
		data.modelFileData = (*(itr++));

		// パーツデータの登録
		charaPartsData_[partsNum].push_back(data);
		partsCount_[partsNum]++;
	}

	// 初期データを登録
	for (int i = 0; i < CHARA_PARTS_NUM; i++)
	{
		modelData_[i] = charaPartsData_[i].at(0);
	}
	charaParts_ = HEAD;
}

// =================================================
// @brief	パーツジャンルデータの読み込み
// @param	none
// @return	none
// =================================================
void CharaData::ImportGenreData()
{
	// ファイル読み込み
	ifstream ifs(PARTS_GENRE_DATA_FILE_NAME);

	// エラー処理
	if (!ifs)
	{
		OutputDebugString(L"This csv file is unknown.");
		assert(0);
	}

	// データをレコードごとに取得
	string data;
	std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> cv;
	while (getline(ifs, data)) {
		string token;
		istringstream stream(data);

		// カンマ区切り
		while (getline(stream, token, ',')) {
			partsGenreData_.push_back(cv.from_bytes(token));
		}
	}

	// ファイルを閉じる
	ifs.close();
}