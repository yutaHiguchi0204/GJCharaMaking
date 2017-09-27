/* =====================================================================
//! @param		�uIModel�vclass src
//! @create		Yuta Higuchi
//! @date		17/09/27
===================================================================== */

// including header
#include "IModel.h"

// namespace
using namespace std;

// method

// =================================================
// @brief	initialize
// @param	�t�@�C�����iwstring�j
// @return	none
// =================================================
void IModel::Initialize(const wstring file)
{
	parts_.push_back(make_unique<Object>());
	parts_.back()->LoadModel(file);

	// ���C�e�B���O����
	parts_.back()->DisableLighting();
}

/*==============================================================
// @brief		update
// @param		none
// @return		none
===============================================================*/
void IModel::Update()
{
	for (auto itr = parts_.begin(); itr != parts_.end(); itr++)
	{
		(*itr)->Update();
	}
}

/*==============================================================
// @brief		draw
// @param		none
// @return		none
===============================================================*/
void IModel::Draw()
{
	for (auto itr = parts_.begin(); itr != parts_.end(); itr++)
	{
		(*itr)->Draw();
	}
}