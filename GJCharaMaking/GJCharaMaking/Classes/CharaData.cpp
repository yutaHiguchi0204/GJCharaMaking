/* =====================================================================
//! @param		�uCharaData�vclass src
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
// @brief	�p�[�c�f�[�^�̓ǂݍ���
// @param	CSV�t�@�C�����iwstring�j
// @return	none
// =================================================
void CharaData::ImportData()
{
	// �t�@�C���ǂݍ���
	ifstream ifs(PARTS_DATA_FILE_NAME);

	// �G���[����
	if (!ifs)
	{
		OutputDebugString(L"This csv file is unknown.");
		assert(0);
	}

	// �f�[�^�����R�[�h���ƂɎ擾
	string data;
	std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> cv;
	vector<wstring> tmp;
	while (getline(ifs, data)) {
		string token;
		istringstream stream(data);

		// �J���}��؂�
		while (getline(stream, token, ',')) {
			tmp.push_back(cv.from_bytes(token));
		}
	}

	// �f�[�^�o�^
	int partsNum = -1;
	for (auto itr = tmp.begin(); itr != tmp.end();)
	{
		if (stoi(*itr) == 1)
		{
			partsNum++;
		}

		charaPartsData[partsNum].push_back(*(++itr));
		itr++;
	}
}