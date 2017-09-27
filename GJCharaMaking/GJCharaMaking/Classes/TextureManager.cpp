/* =====================================================================
//! @param		�uTextureManager�v�N���X�̃\�[�X�t�@�C��
//! @create		����@�T��
//! @date		17/06/05
===================================================================== */

// �w�b�_�t�@�C���̃C���N���[�h
#include "TextureManager.h"

#include "DXTKManager.h"
#include "WICTextureLoader.h"

// ���O���
using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace std;

// �����o�֐��̒�`

/* =====================================================================
//! ���@�e		����������
//! ���@��		�f�o�C�X�iID3D11Device*�j�A�R���e�L�X�g�iID3D11DeviceContext*�j
//! �߂�l		�Ȃ�
===================================================================== */
void TextureManager::Initializer(ID3D11Device* device, ID3D11DeviceContext* context)
{
	m_device = device;
	m_context = context;

	// �u�����h�X�e�[�g�̐ݒ�
	SetBlendState();
}

/* =====================================================================
//! ���@�e		�e�N�X�`���̃��[�h
//! ���@��		�t�@�C�����iwchar_t*�j�A�e�N�X�`���iID3D11ShaderResourceView**�j
//! �߂�l		�Ȃ�
===================================================================== */
void TextureManager::Load(wstring file, ID3D11ShaderResourceView** texture)
{
	const wstring fileName = L"Resources/Texture2D/" + file + L".png";

	CreateWICTextureFromFile(m_device, fileName.c_str(), nullptr, texture);
}

/* =====================================================================
//! ���@�e		�u�����h�X�e�[�g�̐ݒ�
//! ���@��		�Ȃ�
//! �߂�l		�Ȃ�
===================================================================== */
void TextureManager::SetBlendState()
{
	D3D11_BLEND_DESC bd;
	ZeroMemory(&bd, sizeof(D3D11_BLEND_DESC));
	bd.IndependentBlendEnable = false;
	bd.AlphaToCoverageEnable = false;
	bd.RenderTarget[0].BlendEnable = true;
	bd.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	bd.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	bd.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	bd.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	bd.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	bd.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	bd.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	
	m_device->CreateBlendState(&bd, &m_blendState);

	float blendFactor[4] = { D3D11_BLEND_ZERO, D3D11_BLEND_ZERO, D3D11_BLEND_ZERO, D3D11_BLEND_ZERO };
	UINT mask = 0xffffffff;
	m_context->OMSetBlendState(m_blendState, blendFactor, mask);
}

/* =====================================================================
//! ���@�e		�e�N�X�`���̕`��i��`�Ȃ��j
//! ���@��		�e�N�X�`���n���h���iID3D11ShaderResourceView*�j�A�\�����W�iVector2�j�A��]�p�ifloat�j�A�e�N�X�`���T�C�Y�iVector2�j�A���]�����iSpriteEffects�j
//! �߂�l		�Ȃ�
===================================================================== */
void TextureManager::Draw(ID3D11ShaderResourceView* texture, Vector2 pos, float angle, Vector2 textureSize, SpriteEffects flip)
{
	DXTKManager& dxtk = DXTKManager::GetInstance();

	dxtk.m_spriteBatch->Begin(SpriteSortMode_Deferred, m_blendState);
	dxtk.m_spriteBatch->Draw(texture, pos, nullptr, Colors::White, angle, Vector2(textureSize.x / 2, textureSize.y / 2), 1.0f, flip);
	dxtk.m_spriteBatch->End();
}

/* =====================================================================
//! ���@�e		�e�N�X�`���̕`��i��`����j
//! ���@��		�e�N�X�`���n���h���iID3D11ShaderResourceView*�j�A�\�����W�iVector2�j�A�摜�̋�`�J�n���W�iVector2�j�A�摜�̋�`�T�C�Y�iVector2�j�A��]�p�ifloat�j�A�e�N�X�`���T�C�Y�iVector2�j�A���]�����iSpriteEffects�j
//! �߂�l		�Ȃ�
===================================================================== */
void TextureManager::Draw(ID3D11ShaderResourceView* texture, Vector2 pos, Vector2 rectPos, Vector2 rectSize, float angle, Vector2 textureSize, SpriteEffects flip)
{
	DXTKManager& dxtk = DXTKManager::GetInstance();

	// ��`�w��
	int left = rectPos.x, right = rectPos.x + rectSize.x;
	int top = rectPos.y, bottom = rectPos.y + rectSize.y;
	RECT rect = RECT{ left, top, right, bottom };

	dxtk.m_spriteBatch->Begin(SpriteSortMode_Deferred, m_blendState);
	dxtk.m_spriteBatch->Draw(texture, pos, &rect, Colors::White, angle, Vector2(textureSize.x / 2, textureSize.y / 2), 1.0f, flip);
	dxtk.m_spriteBatch->End();
}