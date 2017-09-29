/*===============================================================
// @param	[PlayScene] class src 
// @create	Kazushi Shinohara
// @date	17/09/26
================================================================*/

// include 
#include "PlayScene.h"
#include "Constant.h"
#include "KeyboardDebuger.h"

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
}
