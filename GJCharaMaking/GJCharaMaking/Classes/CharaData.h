/* =====================================================================
//! @param		�uCharaData�vclass header
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
		int partsNo;						// �p�[�c�ԍ�
		std::wstring modelFileData;			// �p�[�c���f���̃t�@�C����
	};

private:
	enum COLUMN_DATA
	{
		NONE = -1,
		PARTS_NO,
		MODEL_DATA
	};

	// �t�@�C����
	const std::wstring PARTS_DATA_FILE_NAME = L"Resources/CharaData/charaData.csv";
	const std::wstring PARTS_GENRE_DATA_FILE_NAME = L"Resources/CharaData/partsGenreData.csv";

	// �L�����p�[�c�f�[�^
	std::vector<PartsData> charaPartsData_[CHARA_PARTS_NUM];

	// �p�[�c�W�������f�[�^
	std::vector<std::wstring> partsGenreData_;

	// �p�[�c��
	int partsCount_[CHARA_PARTS_NUM];

	// ���݂̃p�[�c�W������
	CHARA_PARTS charaParts_;

	// ���݂̃p�[�c�f�[�^
	PartsData modelData_[CHARA_PARTS_NUM];

private:
	friend class SingletonDirector<CharaData>;

	// constructor
	CharaData() {};

public:
	// �p�[�c�f�[�^�̓ǂݍ���
	void ImportData();
	void ImportGenreData();

	// �S�p�[�c�f�[�^�̎擾
	inline std::vector<PartsData> GetPartsData(CHARA_PARTS parts) const { return charaPartsData_[parts]; }
	inline std::vector<std::wstring> GetPartsGenreData() const { return partsGenreData_; }

	// �p�[�c���̎擾
	inline int GetPartsCount(CHARA_PARTS charaParts) const { return partsCount_[charaParts]; }

	// ���݂̃p�[�c�W������
	void SetPartsGenre(CHARA_PARTS charaParts) { charaParts_ = charaParts; }
	inline CHARA_PARTS GetPartsGenre() const { return charaParts_; }

	// ���݂̃��f���f�[�^
	void SetModelData(const CHARA_PARTS charaParts, const PartsData& data) { modelData_[charaParts] = data; }
	inline const PartsData& GetModelData(CHARA_PARTS charaParts) const { return modelData_[charaParts]; }
};