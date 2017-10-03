/* =====================================================================
//! @param		「SingletonDirector」class header
//! @create		Yuta Higuchi
//! @date		17/09/26
===================================================================== */
#pragma once

// class
template <class T> class SingletonDirector
{
public:
	// インスタンスの生成
	static T& GetInstance()
	{
		static T object;
		return object;
	}

protected:
	// コンストラクタ
	SingletonDirector() {};

private:
	// コピーと代入防止
	SingletonDirector(const SingletonDirector &) = delete;
	SingletonDirector& operator=(const SingletonDirector &) = delete;
	SingletonDirector(SingletonDirector &&) = delete;
	SingletonDirector& operator=(SingletonDirector &&) = delete;
};