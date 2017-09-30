/* =====================================================================
//! @param		�uCustomizeScene�vclass src
//! @create		Yuta Higuchi
//! @date		17/09/26
===================================================================== */

// including header
#include "CustomizeScene.h"
#include "CharaData.h"
#include "CollisionManager.h"
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

	// �J�����̏�����
	camera_->SetEyePos(Vector3(9.0f, 10.0f, -25.0f));
	camera_->SetRefPos(Vector3(9.0f, 10.0f, 0.0f));

	// �ÓI�����o�̐ݒ�
	Object::InitializeStatic(device_, context_, camera_.get());

	// �V�����f���̓ǂݍ���
	skyDome_ = make_unique<IModel>();
	skyDome_->Initialize(L"skyDome");

	// �v���C���[�̓ǂݍ���
	player_ = make_unique<Player>();
	player_->Initialize(CharaData::CHARA_PARTS_NUM);

	// �v���C���[�̉�]�p�̏�����
	playerRot_ = 0.0f;

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

	// �p�[�c�r���[�̍X�V
	partsView_->Update();

	// �v���C���[�̍X�V
	player_->Update();

	// �v���C���[�����[�e�[�V����������
	playerRot_ -= 0.01f;
	player_->GetRootParts()->SetRotate(Vector3(0, playerRot_, 0));

	// �L�[�{�[�h�����i�f�o�b�O�p�j
	KeyboardDebuger& kd = KeyboardDebuger::GetInstance();
	CharaData& data = CharaData::GetInstance();
	if (kd.ChangeCharaParts())
	{
		player_->ChangeParts(data.GetPartsGenre(), data.GetModelData(data.GetPartsGenre()));
		playerRot_ = 0.0f;
	}

	// �}�E�X�̓����蔻��`�F�b�N
	CheckCollision();
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

// =================================================
// @brief	�����蔻��`�F�b�N
// @param	none
// @return	none
// =================================================
void CustomizeScene::CheckCollision()
{
	// �}�E�X����
	DXTKManager& dxtk = DXTKManager::GetInstance();
	Mouse::State state = dxtk.mouseTracker_->GetLastState();

	// ���N���b�N���ꂽ��
	if (state.leftButton)
	{
		// �����蔻��p���C�u�����̐���
		CollisionManager& collision = CollisionManager::GetInstance();

		// �p�[�c�W������
		auto partsGenre = partsView_->GetPartsGenrePanel();
		for (auto parts : partsGenre)
		{
			if (collision.IsPointerHit(Vector2(state.x, state.y), parts->GetPos(),Vector2(PARTS_GENREPANEL)))
			{
				// �W�������p�l�����������Ƃ��̏���
				OutputDebugString(TEXT("PartsGenre\n"));
			}
		}

		// �p�[�c�p�l��
		CharaData& data = CharaData::GetInstance();
		auto partsPanel = partsView_->GetPartsPanel(data.GetPartsGenre());
		for (auto parts : partsPanel)
		{
			if (collision.IsPointerHit(Vector2(state.x, state.y), parts->GetPos(),Vector2(PARTS_PANEL)))
			{
				// �p�[�c�p�l�����������Ƃ��̏���
				OutputDebugString(TEXT("PartsPanel\n"));
			}
		}
	}
}