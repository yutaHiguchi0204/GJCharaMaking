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
// @brief	�S�p�l���̃��[�h
// @param	none
// @return	none
// =================================================
void PartsView::LoadPanel()
{
	CharaData& data = CharaData::GetInstance();

	// �p�[�c�W������
	vector<wstring> partsGenreData = data.GetPartsGenreData();
	for (auto itr = partsGenreData.begin(); itr != partsGenreData.end(); itr++)
	{
		partsGenrePanel_.push_back(new PartsGenrePanel);

		wstring wstr = L"partsBanner" + (*itr);
		partsGenrePanel_.back()->Initialize(wstr);
	}
}

// =================================================
// @brief	�S�p�l���̕`��
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