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
#include "SoundManager.h"

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

	// �V�[���J�ڗp�{�^���̓ǂݍ���
	sceneChanger_ = make_unique<SceneChangerButton>();
	sceneChanger_->Initialize(L"Play");
	sceneChanger_->SetPos(Vector2(SIZE_WINDOW_WIDTH - 112.0f, 16.0f));

	// BGM�̍Đ�
	SoundManager& sound = SoundManager::GetInstance();
	sound.PlayAudio(SoundManager::SOUND::CUSTOMIZE_BGM);
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

	// �v���C���[�����[�e�[�V����������
	playerRot_ -= 0.01f;
	player_->GetRootParts()->SetRotate(Vector3(0, playerRot_, 0));

	// �p�[�c�r���[�̍X�V
	partsView_->Update();

	// �}�E�X�̓����蔻��`�F�b�N
	CheckCollision();

	// �L�[�{�[�h�����i�f�o�b�O�p�j
	KeyboardDebuger& kd = KeyboardDebuger::GetInstance();
	CharaData& data = CharaData::GetInstance();
	if (kd.ChangeCharaParts())
	{
		player_->ChangeParts(data.GetPartsGenre(), data.GetModelData(data.GetPartsGenre()));
		playerRot_ = 0.0f;

		// SE�̍Đ�
		SoundManager& sound = SoundManager::GetInstance();
		sound.PlayAudio(SoundManager::SOUND::PARTS_CHANGE_SE);
	}
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

	// �V�[���J�ڗp�{�^���̕`��
	sceneChanger_->Draw();
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
	if (dxtk.mouseTracker_->leftButton == Mouse::ButtonStateTracker::PRESSED)
	{
		CharaData& data = CharaData::GetInstance();

		// �����蔻��p���C�u�����̐���
		CollisionManager& collision = CollisionManager::GetInstance();

		// �p�[�c�W������
		auto partsGenre = partsView_->GetPartsGenrePanel(); 
		for (auto parts : partsGenre)
		{
			// ���ݑI�𒆂̂��̂͒ʂ��Ă��Ӗ����Ȃ��̂ŏ������Ȃ�
			if (parts->GetPanelNo() != data.GetPartsGenre())
			{
				if (collision.IsPointerHit(Vector2(state.x, state.y), parts->GetPos(), SIZE_PARTS_GENREPANEL))
				{
					// �W�������p�l�����������Ƃ��̏���
					int genreNo = parts->GetPanelNo();
					data.SetPartsGenre((CharaData::CHARA_PARTS)(genreNo));
				}
			}
		}

		// �p�[�c�p�l��
		auto partsPanel = partsView_->GetPartsPanel(data.GetPartsGenre());
		for (auto parts : partsPanel)
		{
			// ���ݑI�𒆂̂��̂͒ʂ��Ă��Ӗ����Ȃ��̂ŏ������Ȃ�
			if (parts->GetPanelNo() != data.GetModelData(data.GetPartsGenre()).partsNo)
			{
				if (collision.IsPointerHit(Vector2(state.x, state.y), parts->GetPos(), SIZE_PARTS_PANEL))
				{
					// �p�[�c�p�l�����������Ƃ��̏���
					int panelNo = parts->GetPanelNo();

					data.SetModelData(
						data.GetPartsGenre(),
						(data.GetModelData(data.GetPartsGenre()).partsNo,
						(data.GetPartsData(data.GetPartsGenre()).at(panelNo)))
					);

					// �v���C���[�̃p�[�c�ύX
					player_->ChangeParts(data.GetPartsGenre(), data.GetModelData(data.GetPartsGenre()));
					playerRot_ = 0.0f;
				}
			}
		}

		// �V�[���J�ڗp�{�^��
		if (collision.IsPointerHit(Vector2(state.x, state.y), sceneChanger_->GetPos(), SIZE_SCENE_CHANGER_BUTTON))
		{
			// �v���C�V�[���ֈڍs
			ChangeScene(PLAY);

			// ���̒�~
			SoundManager& sound = SoundManager::GetInstance();
			sound.StopAudio();

			// �V�[���J�ڎ�SE
			sound.PlayAudio(SoundManager::SOUND::SCENE_CHANGE_SE);
		}
	}
}