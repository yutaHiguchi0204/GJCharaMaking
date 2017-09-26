/* =====================================================================
//! @param		�uObject�vclass src
//! @create		Yuta Higuchi
//! @date		17/09/26
===================================================================== */

// including header
#include "Object.h"

// namespace
using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace std;

// static member
Microsoft::WRL::ComPtr<ID3D11Device>		Object::d3dDevice_;				// �f�o�C�X
Microsoft::WRL::ComPtr<ID3D11DeviceContext> Object::d3dContext_;			// �f�o�C�X�R���e�L�X�g
Camera*										Object::camera_;				// �J����
unique_ptr<CommonStates>					Object::states_;				// �ėp�`��X�e�[�g
unique_ptr<EffectFactory>					Object::factory_;				// �G�t�F�N�g�t�@�N�g��
ID3D11BlendState*							Object::blendStateSubtract_;	// ���Z�`��p

// method

// constructor
Object::Object()
{
	// �X�P�[���̏�����
	scale_ = Vector3(1.0f, 1.0f, 1.0f);

	// �e�̂R�c�I�u�W�F�N�g��������
	pParent_ = nullptr;
}

// =================================================
// @brief	�ÓI�����o�̏�����
// @param	�f�o�C�X�iID3D11Device�j�A�f�o�C�X�R���e�L�X�g�iID3D11DeviceContext�j�A�J�����iCamera*�j
// @return	none
// =================================================
void Object::InitializeStatic(Microsoft::WRL::ComPtr<ID3D11Device> d3dDevice, Microsoft::WRL::ComPtr<ID3D11DeviceContext> d3dContext, Camera* camera)
{
	d3dDevice_ = d3dDevice;
	d3dContext_ = d3dContext;
	camera_ = camera;

	// �ėp�`��X�e�[�g����
	states_ = make_unique<CommonStates>(d3dDevice_.Get());

	// �G�t�F�N�g�t�@�N�g������
	factory_ = make_unique<EffectFactory>(d3dDevice_.Get());
	factory_->SetDirectory(L"Resources/CMedia");

	// ���Z�`��p�̃u�����h�X�e�[�g���쐬
	D3D11_BLEND_DESC desc;
	desc.AlphaToCoverageEnable = false;
	desc.IndependentBlendEnable = false;
	desc.RenderTarget[0].BlendEnable = true;
	desc.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
	desc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
	desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_REV_SUBTRACT;
	desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ONE;
	desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_REV_SUBTRACT;
	desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	HRESULT ret = d3dDevice_->CreateBlendState(&desc, &blendStateSubtract_);
}

// =================================================
// @brief	�`�挸�Z�̐ݒ�
// @param	none
// @return	none
// =================================================
void Object::SetSubtractive()
{
	// ���Z�`���ݒ�
	d3dContext_->OMSetBlendState(blendStateSubtract_, nullptr, 0xffffff);
}

// =================================================
// @brief	update
// @param	none
// @return	none
// =================================================
void Object::Update()
{
	// �X�P�[�����O�s��
	Matrix scaleMat = Matrix::CreateScale(scale_);

	// ��]�s��
	Matrix rotMat;

	// �I�C���[�p�Ōv�Z
	Matrix rotMatZ = Matrix::CreateRotationZ(rotate_.z);
	Matrix rotMatX = Matrix::CreateRotationX(rotate_.x);
	Matrix rotMatY = Matrix::CreateRotationY(rotate_.y);
	rotMat = rotMatZ * rotMatX * rotMatY;

	// ���s�ړ��s��
	Matrix transMat = Matrix::CreateTranslation(translate_);

	// ���[���h�s��̍���
	world_ = scaleMat * rotMat * transMat;

	// �e�̍s���������i�q�̏ꍇ�j
	if (pParent_) world_ *= pParent_->GetWorldMatrix();
}

// =================================================
// @brief	draw
// @param	none
// @return	none
// =================================================
void Object::Draw()
{
	if (model_)
	{
		// �R�c���f���̕`��
		model_->Draw(
			d3dContext_.Get(),
			*states_,
			world_,
			camera_->GetViewMatrix(),
			camera_->GetProjectionMatrix()
		);
	}
}

// =================================================
// @brief	���Z�`�揈��
// @param	none
// @return	none
// =================================================
void Object::DrawSubtractive()
{
	if (model_)
	{
		// �R�c���f���̕`��
		model_->Draw(
			d3dContext_.Get(),
			*states_,
			world_,
			camera_->GetViewMatrix(),
			camera_->GetProjectionMatrix(),
			false,
			Object::SetSubtractive
		);
	}
}

// =================================================
// @brief	���f���̃��[�h
// @param	�t�@�C�����iwchar_t*�j
// @return	none
// =================================================
void Object::LoadModel(const wchar_t* fileName)
{
	// ���f���̓ǂݍ���
	model_ = Model::CreateFromCMO(
		d3dDevice_.Get(),
		fileName,
		*factory_
	);
}

// =================================================
// @brief	�I�u�W�F�N�g�̃��C�e�B���O�𖳌��ɂ���
// @param	none
// @return	none
// =================================================
void Object::DisableLighting()
{
	if (model_)
	{
		// ���f�����̑S���b�V������
		ModelMesh::Collection::const_iterator it_mesh = model_->meshes.begin();
		for (; it_mesh != model_->meshes.end(); it_mesh++)
		{
			ModelMesh* modelmesh = it_mesh->get();
			assert(modelmesh);

			// ���b�V�����̑S���b�V���p�[�c����
			std::vector<std::unique_ptr<ModelMeshPart>>::iterator it_meshpart = modelmesh->meshParts.begin();
			for (; it_meshpart != modelmesh->meshParts.end(); it_meshpart++)
			{
				ModelMeshPart* meshpart = it_meshpart->get();
				assert(meshpart);

				// ���b�V���p�[�c�ɃZ�b�g���ꂽ�G�t�F�N�g��BasicEffect�Ƃ��Ď擾
				std::shared_ptr<IEffect> ieff = meshpart->effect;
				BasicEffect* eff = dynamic_cast<BasicEffect*>(ieff.get());
				if (eff != nullptr)
				{
					// ���Ȕ������ő�l��
					eff->SetEmissiveColor(Vector3(1, 1, 1));

					// �G�t�F�N�g�Ɋ܂ޑS�Ă̕��s�������ɂ��ď�������
					for (int i = 0; i < BasicEffect::MaxDirectionalLights; i++)
					{
						// ���C�g�𖳌��ɂ���
						eff->SetLightEnabled(i, false);
					}
				}
			}
		}
	}
}