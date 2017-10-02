/* =====================================================================
//! @param		�uSceneManager�vclass src
//! @create		Yuta Higuchi
//! @date		17/09/26
===================================================================== */

// including header
#include "SceneManager.h"
#include <cassert>
#include "Constant.h"
#include "CustomizeScene.h"
#include "PlayScene.h"

// namespace
using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace std;

// method

// =================================================
// @brief	initialize
// @param	�f�o�C�X�iID3D11Device�j�A�f�o�C�X�R���e�L�X�g�iID3D11DeviceContext�j
// @return	none
// =================================================
void SceneManager::Initialize(Microsoft::WRL::ComPtr<ID3D11Device> device, Microsoft::WRL::ComPtr<ID3D11DeviceContext> context)
{
	device_ = device;
	context_ = context;

	// �v���~�e�B�u�o�b�`�̐ݒ�
	batch_ = make_unique<PrimitiveBatch<VertexPositionNormal>>(context_.Get());

	// �G�t�F�N�g����
	effect_ = make_unique<BasicEffect>(device_.Get());
	effect_->SetVertexColorEnabled(true);

	// �s��̏�����
	view_ = Matrix::CreateLookAt(Vector3(0.f, 2.f, 2.f), Vector3::Zero, Vector3::UnitY);
	proj_ = Matrix::CreatePerspectiveFieldOfView(XM_PI / 4.f, float(SIZE_WINDOW_WIDTH) / float(SIZE_WINDOW_HEIGHT), 0.1f, 500.f);

	// �G�t�F�N�g�̏�����
	effect_->SetView(view_);
	effect_->SetProjection(proj_);

	void const* shaderByteCode;
	size_t byteCodeLength;

	// �V�F�[�_�[�o�C�g�R�[�h�̏���
	effect_->GetVertexShaderBytecode(&shaderByteCode, &byteCodeLength);

	// �f�o�C�X�ݒ�
	device_->CreateInputLayout(VertexPositionColor::InputElements,
		VertexPositionColor::InputElementCount,
		shaderByteCode, byteCodeLength,
		inputLayout_.GetAddressOf());

	// �G�t�F�N�g�t�@�N�g���̐���
	factory_ = std::make_unique<EffectFactory>(device_.Get());

	// �e�N�X�`���̓ǂݎ��p�X�w��
	factory_->SetDirectory(L"Resources/CMedia");

	// �����V�[�����J�X�^����ʂɐݒ�
	scene_ = make_unique<CustomizeScene>(device_, context_);
	scene_->Initialize();
}

// =================================================
// @brief	update
// @param	none
// @return	none
// =================================================
void SceneManager::Update()
{
	scene_->Update();
}

// =================================================
// @brief	draw
// @param	none
// @return	none
// =================================================
void SceneManager::Draw()
{
	scene_->Draw();
}

// =================================================
// @brief	�V�[���؂�ւ�
// @param	�V�[���iSCENE�j
// @return	none
// =================================================
void SceneManager::ChangeScene(Scene::SCENE scene)
{
	// �V�[���؂�ւ�
	switch (scene)
	{
	case Scene::CUSTOMIZE:
		scene_ = make_unique<CustomizeScene>(device_, context_);
		break;

	case Scene::PLAY:
		scene_ = make_unique<PlayScene>(device_, context_);
		break;

	default:
		OutputDebugString(L"This scene is unknown.");
		assert(0);
		break;
	}

	scene_->Initialize();
}