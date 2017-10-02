/*===============================================================
// @param	[PlayScene] class src 
// @create	Kazushi Shinohara
// @date	17/09/26
================================================================*/

// include 
#include "PlayScene.h"
#include "CollisionManager.h"
#include "Constant.h"
#include "DXTKManager.h"
#include "KeyboardDebuger.h"
#include "SoundManager.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace std;

// constructor
PlayScene::PlayScene(Microsoft::WRL::ComPtr<ID3D11Device> device, Microsoft::WRL::ComPtr<ID3D11DeviceContext> context)
	: Scene(device, context)
{
}

/*==============================================================
// @brief		initialize
// @param		none
// @return		none
===============================================================*/
void PlayScene::Initialize()
{
	// �J�����̐���
	camera_ = make_shared<Camera>(SIZE_WINDOW_WIDTH, SIZE_WINDOW_HEIGHT);

	// �J�����̏�����
	camera_->SetEyePos(Vector3(0.0f, 10.0f, -25.0f));
	camera_->SetRefPos(Vector3(0.0f, 10.0f, 0.0f));

	// �ÓI�����o�̐ݒ�
	Object::InitializeStatic(device_, context_, camera_.get());

	// �V�����f���̓ǂݍ���
	skyDome_ = make_unique<IModel>();
	skyDome_->Initialize(L"skyDome");

	// �n�ʃ��f���̓ǂݍ���
	ground_ = make_unique<IModel>();
	ground_->Initialize(L"ground_200m");

	// �v���C���[�̓ǂݍ���
	player_ = make_unique<Player>();
	player_->Initialize(CharaData::CHARA_PARTS_NUM);

	// �V�[���J�ڗp�{�^���̓ǂݍ���
	sceneChanger_ = make_unique<SceneChangerButton>();
	sceneChanger_->Initialize(L"Custom");
	sceneChanger_->SetPos(Vector2(SIZE_WINDOW_WIDTH - 112.0f, 16.0f));

	// BGM�̍Đ�
	SoundManager& sound = SoundManager::GetInstance();
	sound.PlayAudio(SoundManager::SOUND::PLAY_BGM);
}

/*==============================================================
// @brief		update
// @param		none
// @return		none
===============================================================*/
void PlayScene::Update()
{
	// �J�����̍X�V
	camera_->Update();

	// �J�������v���C���[���œ������i�L�[�{�[�h����j
	KeyboardDebuger& kd = KeyboardDebuger::GetInstance();
	kd.MoveCamera(camera_);

	// �V���̍X�V
	skyDome_->Update();

	// �n�ʂ̍X�V
	ground_->Update();

	// �v���C���[�̍X�V
	player_->Update();

	// �}�E�X�̓����蔻��`�F�b�N
	CheckCollision();
}

/*==============================================================
// @brief		draw
// @param		none
// @return		none
===============================================================*/
void PlayScene::Draw()
{
	// �V���̕`��
	skyDome_->Draw();

	// �n�ʂ̕`��
	ground_->Draw();

	// �v���C���[�̕`��
	player_->Draw();

	// �V�[���J�ڗp�{�^���̕`��
	sceneChanger_->Draw();
}

// =================================================
// @brief	�����蔻��`�F�b�N
// @param	none
// @return	none
// =================================================
void PlayScene::CheckCollision()
{
	// �}�E�X����
	DXTKManager& dxtk = DXTKManager::GetInstance();
	Mouse::State state = dxtk.mouseTracker_->GetLastState();

	// ���N���b�N���ꂽ��
	if (dxtk.mouseTracker_->leftButton == Mouse::ButtonStateTracker::PRESSED)
	{
		// �����蔻��p���C�u�����̐���
		CollisionManager& collision = CollisionManager::GetInstance();

		// �V�[���J�ڗp�{�^��
		if (collision.IsPointerHit(Vector2(state.x, state.y), sceneChanger_->GetPos(), SIZE_SCENE_CHANGER_BUTTON))
		{
			// �v���C�V�[���ֈڍs
			ChangeScene(CUSTOMIZE);

			// ���̒�~
			SoundManager& sound = SoundManager::GetInstance();
			sound.StopAudio();

			// �V�[���J�ڎ�SE
			sound.PlayAudio(SoundManager::SOUND::SCENE_CHANGE_SE);
		}
	}
}
