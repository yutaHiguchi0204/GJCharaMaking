/*===============================================================
// @param	[PlayScene] class src 
// @create	Kazushi Shinohara
// @date	17/09/26
================================================================*/

// include 
#include "PlayScene.h"
#include "Constant.h"

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
	camera_ = make_unique<Camera>(SIZE_WINDOW_WIDTH, SIZE_WINDOW_HEIGHT);

	// �ÓI�����o�̐ݒ�
	Object::InitializeStatic(device_, context_, camera_.get());

	// �V�����f���̓ǂݍ���
	skyDome_ = make_unique<Object>();
	skyDome_->LoadModel(L"Resources/CMedia/skyDome.cmo");

	//�n�`�ƓV�����C�e�B���O�𖳌��ɂ���
	skyDome_->DisableLighting();
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

	// �V���̍X�V
	skyDome_->Update();
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
}
