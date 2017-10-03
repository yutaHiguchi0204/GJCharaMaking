/* =====================================================================
//! @param		�uSingletonDirector�vclass header
//! @create		Yuta Higuchi
//! @date		17/09/26
===================================================================== */
#pragma once

// class
template <class T> class SingletonDirector
{
public:
	// �C���X�^���X�̐���
	static T& GetInstance()
	{
		static T object;
		return object;
	}

protected:
	// �R���X�g���N�^
	SingletonDirector() {};

private:
	// �R�s�[�Ƒ���h�~
	SingletonDirector(const SingletonDirector &) = delete;
	SingletonDirector& operator=(const SingletonDirector &) = delete;
	SingletonDirector(SingletonDirector &&) = delete;
	SingletonDirector& operator=(SingletonDirector &&) = delete;
};