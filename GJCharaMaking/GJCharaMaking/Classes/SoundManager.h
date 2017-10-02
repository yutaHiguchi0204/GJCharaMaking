/* =====================================================================
//! @param		�uSoundManager�v�N���X�̃w�b�_�t�@�C��
//! @create		Yuta Higuchi
//! @date		17/10/02
===================================================================== */
#pragma once
#pragma comment(lib, "cri_ware_pcx86_LE_import.lib")

// �w�b�_�t�@�C���̃C���N���[�h
#include "SingletonDirector.h"

#include "ADX2Le.h"

// �N���X�̒�`
class SoundManager : public SingletonDirector<SoundManager>
{
public:
	enum class SOUND
	{
		CUSTOMIZE_BGM,
		PLAY_BGM,
		PARTS_CHANGE_SE,
	};

private:
	friend class SingletonDirector<SoundManager>;

	// �R���X�g���N�^
	SoundManager() {};

public:
	// ������
	void Initializer()
	{
		ADX2Le::Initialize("Audio/GJCharaMaking.acf");
		ADX2Le::LoadAcb("Audio/soundCue.acb", "Audio/soundCue.awb");
	}

	// �X�V
	void Update()
	{
		ADX2Le::Update();
	}

	// ���̍Đ�
	void PlayAudio(int audioID)
	{
		ADX2Le::Play(audioID);
	}

	// ���̒�~
	void StopAudio()
	{
		ADX2Le::Stop();
	}

	// �I������
	void Dispose()
	{
		ADX2Le::Finalize();
	}
};