/* =====================================================================
//! @param		「SoundManager」クラスのヘッダファイル
//! @create		Yuta Higuchi
//! @date		17/10/02
===================================================================== */
#pragma once
#pragma comment(lib, "cri_ware_pcx86_LE_import.lib")

// ヘッダファイルのインクルード
#include "SingletonDirector.h"

#include "ADX2Le.h"

// クラスの定義
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

	// コンストラクタ
	SoundManager() {};

public:
	// 初期化
	void Initializer()
	{
		ADX2Le::Initialize("Audio/GJCharaMaking.acf");
		ADX2Le::LoadAcb("Audio/soundCue.acb", "Audio/soundCue.awb");
	}

	// 更新
	void Update()
	{
		ADX2Le::Update();
	}

	// 音の再生
	void PlayAudio(int audioID)
	{
		ADX2Le::Play(audioID);
	}

	// 音の停止
	void StopAudio()
	{
		ADX2Le::Stop();
	}

	// 終了処理
	void Dispose()
	{
		ADX2Le::Finalize();
	}
};