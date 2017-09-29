/* =====================================================================
//! @param		�uKeyboardDebuger�vclass header
//! @create		Yuta Higuchi
//! @date		17/09/29
===================================================================== */
#pragma once

// including header
#include "SingletonDirector.h"

// class
class KeyboardDebuger : public SingletonDirector<KeyboardDebuger>
{
private:
	friend class SingletonDirector<KeyboardDebuger>;

	// constructor
	KeyboardDebuger() {};

public:
	void Update();						// �L�[�{�[�h���̍X�V
	bool ChangeCharaParts();			// �p�[�c�ύX
};