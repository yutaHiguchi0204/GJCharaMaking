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

	// �t�@�C�������
	ifs.close();

	// �f�[�^�o�^
	int partsNum = NONE;
	for (auto itr = tmp.begin(); itr != tmp.end();)
	{
		PartsData data;

		if (stoi(*itr) == 0)
		{
			// �p�l���ԍ���ݒ�
			partsNum++;
		}

		// ���f���A�p�[�c���ꂼ��̃t�@�C������ݒ�
		data.partsNo = stoi(*(itr++));
		data.modelFileData = (*(itr++));

		// �p�[�c�f�[�^�̓o�^
		charaPartsData_[partsNum].push_back(data);
		partsCount_[partsNum]++;
	}

	// �����f�[�^��o�^
	for (int i = 0; i < CHARA_PARTS_NUM; i++)
	{
		modelData_[i] = charaPartsData_[i].at(0);
	}
	charaParts_ = HEAD;
}

// =================================================
// @brief	�p�[�c�W�������f�[�^�̓ǂݍ���
// @param	none
// @return	none
// =================================================
void CharaData::ImportGenreData()
{
	// �t�@�C���ǂݍ���
	ifstream ifs(PARTS_GENRE_DATA_FILE_NAME);

	// �G���[����
	if (!ifs)
	{
		OutputDebugString(L"This csv file is unknown.");
		assert(0);
	}

	// �f�[�^�����R�[�h���ƂɎ擾
	string data;
	std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> cv;
	while (getline(ifs, data)) {
		string token;
		istringstream stream(data);

		// �J���}��؂�
		while (getline(stream, token, ',')) {
			partsGenreData_.push_back(cv.from_bytes(token));
		}
	}

	// �t�@�C�������
	ifs.close();
}