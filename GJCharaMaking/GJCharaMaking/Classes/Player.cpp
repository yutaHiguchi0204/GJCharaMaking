/*===============================================================
// @param	[Player] class src
// @create	Kazushi Shinohara
// @date	17/09/27
================================================================*/

// including header
#include "Player.h"

// namespace
using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace std;

// method

Player::Player()
{
	Initialize();
}

Player::~Player()
{
}

// =================================================
// @brief	Initialize
// @param	none
// @return	none
// =================================================
void Player::Initialize()
{
	//
	parts_.resize(PARTS_NUM);
	parts_[PARTS_LEG]->LoadModel(L"Resources/CMedia/Leg.cmo");
	parts_[PARTS_BODY]->LoadModel(L"Resources/CMedia/Body.cmo");
	parts_[PARTS_HEAD]->LoadModel(L"Resources/CMedia/Head.cmo");

	// 親子関係の構築(子供に親をセット)
	parts_[PARTS_BODY]->SetParent(&parts_[PARTS_LEG]);
	parts_[PARTS_HEAD]->SetParent(&parts_[PARTS_BODY]);
	
	// 親からのオフセット(ローカルの座標ずれ)
	parts_[PARTS_BODY]->SetTranslate(Vector3(0, 0.4f, 0.1f));
	parts_[PARTS_HEAD]->SetTranslate(Vector3(0, 0.5f, 0));
}

// =================================================
// @brief	Update
// @param	none
// @return	none
// =================================================
void Player::Update()
{
	
}

// =================================================
// @brief	Draw
// @param	none
// @return	none
// =================================================
void Player::Draw()
{
	
}

