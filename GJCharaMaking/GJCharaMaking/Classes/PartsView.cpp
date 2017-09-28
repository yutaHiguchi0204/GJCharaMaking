/*===============================================================
// @param	[PartsView] class src
// @create	Yuki Matsumaru
// @date	17/09/27
================================================================*/

// including header
#include "PartsView.h"
#include "CharaData.h"

// namespace
using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace std;

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
	for (auto itr = partsGenreData.begin(); itr != partsGenreData.end(); itr++)
	{
		partsGenrePanel_.push_back(new PartsGenrePanel);

		wstring wstr = L"partsBanner" + (*itr);
		partsGenrePanel_.back()->Initialize(wstr);
	}
}

// =================================================
// @brief	全パネルの描画
// @param	none
// @return	none
// =================================================
void PartsView::DrawPanel()
{
	for (auto itr = partsGenrePanel_.begin(); itr != partsGenrePanel_.end(); itr++)
	{
		(*itr)->Draw(Vector2(80.0f + (itr - partsGenrePanel_.begin()) % 2 * 144.0f, 80.0f + (itr - partsGenrePanel_.begin()) / 2 * 48.0f));
	}
}