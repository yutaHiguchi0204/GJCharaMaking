/* =====================================================================
//! @param		�uKeyboardDebuger�vclass header
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
	void Update();											// �L�[�{�[�h���̍X�V
	bool ChangeCharaParts();								// �p�[�c�ύX
	void MoveCamera(std::shared_ptr<Camera> camera);		// �J�����𓮂����i�v���C���[���j
};