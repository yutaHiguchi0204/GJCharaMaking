/* =====================================================================
//! @param		�uCustomizeScene�vclass src
//! @create		Yuta Higuchi
//! @date		17/09/26
===================================================================== */

// including header
#include "CustomizeScene.h"
#include "CharaData.h"
#include "Constant.h"
#include "DXTKManager.h"
#include "KeyboardDebuger.h"

// namespace
using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace std;

// method

// constructor
CustomizeScene::CustomizeScene(Microsoft::WRL::ComPtr<ID3D11Device> device, Microsoft::WRL::ComPtr<ID3D11DeviceContext> context)
	: Scene(device, context)
{
}

// =================================================
// @brief	initialize
// @param	none
// @return	none
// =================================================
void CustomizeScene::Initialize()
{
	// �J�����̐���
	camera_ = make_unique<Camera>(SIZE_WINDOW_WIDTH, SIZE_WINDOW_HEIGHT);

	// �ÓI�����o�̐ݒ�
	Object::InitializeStatic(device_, context_, camera_.get());

	// �p�[�c�f�[�^�̓ǂݍ���
	CharaData& data = CharaData::GetInstance();
	data.ImportData();
	data.ImportGenreData();

	// �V�����f���̓ǂݍ���
	skyDome_ = make_unique<IModel>();
	skyDome_->Initialize(L"skyDome");

	// �v���C���[�̓ǂݍ���
	player_ = make_unique<Player>();
	player_->Initialize(CharaData::CHARA_PARTS_NUM);

	// �p�[�c�r���[�̓ǂݍ���
	partsView_ = make_unique<PartsView>();
	partsView_->Initialize(L"customView");
	partsView_->LoadPanel();
}

// =================================================
// @brief	update
// @param	none
// @return	none
// =================================================
void CustomizeScene::Update()
{
	// �J�����̍X�V
	camera_->Update();

	// �V���̍X�V
	skyDome_->Update();

	// �v���C���[�̍X�V
	player_->Update();

	// �L�[�{�[�h�����i�f�o�b�O�p�j
	KeyboardDebuger& kd = KeyboardDebuger::GetInstance();
	kd.ChangeCharaParts();
}

// =================================================
// @brief	draw
// @param	none
// @return	none
// =================================================
void CustomizeScene::Draw()
{
	// �V���̕`��
	skyDome_->Draw();

	// �v���C���[�̕`��
	player_->Draw();

	// �p�[�c�r���[�̕`��
	partsView_->Draw();
	partsView_->DrawPanel();
}