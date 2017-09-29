/*===============================================================
// @param	[PartsView] class src
// @create	Yuki Matsumaru
// @date	17/09/27
================================================================*/

// including header
#include "PartsView.h"

// namespace
using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace std;

// macro
#define SET_PARTS_GENRE_PANEL(pos)	(Vector2((80.0f + (((pos) % 2) * 144.0f)), (80.0f + (((pos) / 2) * 48.0f))))
#define SET_PARTS_PANEL(pos)		(Vector2((56.0f + (((pos) % 3) * 112.0f)), (256.0f + (((pos) / 3) * 112.0f))))

// method

// =================================================
// @brief	全パネルのロード
// @param	none
// @return	none
// =================================================
void PartsView::LoadPanel()
{
	CharaData& data = CharaData::GetInstance();

	// パーツジャンル
	vector<wstring> partsGenreData = data.GetPartsGenreData();
	for (auto tmpData : partsGenreData)
	{
		partsGenrePanel_.push_back(new PartsGenrePanel);

		wstring wstr = L"partsBanner" + (tmpData);
		partsGenrePanel_.back()->Initialize(wstr);
	}

	// パーツボタン
	for (int i = 0; i < CharaData::CHARA_PARTS_NUM; i++)
	{
		vector<CharaData::PartsData> partsData = data.GetPartsData((CharaData::CHARA_PARTS)i);
		for (auto tmpData : partsData)
		{
			partsPanel_[i].push_back(new PartsPanel);

			wstring wstr = tmpData.modelFileData + L"UI";
			partsPanel_[i].back()->Initialize(wstr);
		}
	}
}

// =================================================
// @brief	全パネルの描画
// @param	none
// @return	none
// =================================================
void PartsView::DrawPanel()
{
	// パーツジャンル
	for (auto itr = partsGenrePanel_.begin(); itr != partsGenrePanel_.end(); itr++)
	{
		(*itr)->Draw(SET_PARTS_GENRE_PANEL(itr - partsGenrePanel_.begin()));
	}

	// 現在選択しているジャンル
	CharaData& data = CharaData::GetInstance();
	CharaData::CHARA_PARTS partsGenre = data.GetPartsGenre();

	// パーツボタン
	for (auto itr = partsPanel_[partsGenre].begin(); itr != partsPanel_[partsGenre].end(); itr++)
	{
		(*itr)->Draw(SET_PARTS_PANEL(itr - partsPanel_[partsGenre].begin()));
	}
}