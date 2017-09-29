/* =====================================================================
//! @param		「KeyboardDebuger」class header
//! @create		Yuta Higuchi
//! @date		17/09/29
===================================================================== */
#pragma once

// including header
#include "SingletonDirector.h"
#include <CommonStates.h>
#include "Camera.h"

// class
class KeyboardDebuger : public SingletonDirector<KeyboardDebuger>
{
private:
	friend class SingletonDirector<KeyboardDebuger>;

	// constructor
	KeyboardDebuger() {};

public:
	void Update();											// キーボード情報の更新
	bool ChangeCharaParts();								// パーツ変更
	void MoveCamera(std::shared_ptr<Camera> camera);		// カメラを動かす（プレイヤー軸）
};