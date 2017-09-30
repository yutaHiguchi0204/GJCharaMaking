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
// @brief	update
// @param	none
// @return	none
// =================================================
void PartsView::Update()
{
	CharaData& data = CharaData::GetInstance();

	// アクティブパネルの設定
	partsGenreFrame_->SetPos(partsGenrePanel_.at(data.GetPartsGenre())->GetPos());
	partsPanelFrame_->SetPos(partsPanel_[data.GetPartsGenre()].at(data.GetModelData(data.GetPartsGenre()).partsNo)->GetPos());
}

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

	// パーツジャンルの位置設定
	for (auto itr = partsGenrePanel_.begin(); itr != partsGenrePanel_.end(); itr++)
	{
		(*itr)->SetPos(SET_PARTS_GENRE_PANEL(itr - partsGenrePanel_.begin()));
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

		// 位置設定
		for (auto itr = partsPanel_[i].begin(); itr != partsPanel_[i].end(); itr++)
		{
			(*itr)->SetPos(SET_PARTS_PANEL(itr - partsPanel_[i].begin()));
		}
	}

	// アクティブパネル用枠の設定
	partsGenreFrame_ = make_unique<Resource2D>();
	partsGenreFrame_->Initialize(L"GenreFrame");
	partsPanelFrame_ = make_unique<Resource2D>();
	partsPanelFrame_->Initialize(L"PartsFrame");
}

// =================================================
// @brief	全パネルの描画
// @param	none
// @return	none
// =================================================
void PartsView::DrawPanel()
{
	// パーツジャンル
	for (auto parts : partsGenrePanel_)
	{
		parts->Draw();
	}

	// 現在選択しているジャンル
	CharaData& data = CharaData::GetInstance();
	CharaData::CHARA_PARTS partsGenre = data.GetPartsGenre();

	// パーツボタン
	for (auto parts : partsPanel_[partsGenre])
	{
		parts->Draw();
	}

	// アクティブパネルに枠を描画
	partsGenreFrame_->Draw();
	partsPanelFrame_->Draw();
}