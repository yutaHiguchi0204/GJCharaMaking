/* =====================================================================
//! @param		�uCamera�vclass header
//! @create		Yuta Higuchi
//! @date		17/09/26
===================================================================== */
#pragma once

// including header
#include <d3d11_1.h>
#include <SimpleMath.h>

// class
class Camera
{
protected:
	// �r���[�s��֌W
	DirectX::SimpleMath::Matrix view_;								// �r���[�s��
	DirectX::SimpleMath::Vector3 eyePos_;							// ���_
	DirectX::SimpleMath::Vector3 refPos_;							// �����_�i�Q�Ɠ_�j
	DirectX::SimpleMath::Vector3 upVec_;							// ������x�N�g��

	// �v���W�F�N�V�����s��֌W
	DirectX::SimpleMath::Matrix proj_;								// �v���W�F�N�V�����s��
	float fovY_;													// ������������p
	float aspect_;													// �A�X�y�N�g��
	float nearClip_;												// ��O�̕\�����E����
	float farClip_;													// ���̕\�����E����

public:
	Camera(int width, int height);
	virtual ~Camera() {};

	virtual void Update();											// �X�V����

	inline const DirectX::SimpleMath::Matrix& GetViewMatrix()		{ return view_; };				// �r���[�s��̎擾
	inline const DirectX::SimpleMath::Matrix& GetProjectionMatrix()	{ return proj_; };				// �v���W�F�N�V�����s��̎擾

	void SetEyePos(const DirectX::SimpleMath::Vector3& pos)			{ eyePos_ = pos; };				// ���_�̐ݒ�
	void SetRefPos(const DirectX::SimpleMath::Vector3& pos)			{ refPos_ = pos; };				// �����_�̐ݒ�
	void SetUpVec(const DirectX::SimpleMath::Vector3& vec)			{ upVec_ = vec; };				// ������x�N�g���̐ݒ�

	void SetFovY(float fovY)										{ fovY_ = fovY; };				// ������������p�̐ݒ�
	void SetAspect(float aspect)									{ aspect_ = aspect; };			// �A�X�y�N�g��̐ݒ�
	void SetNearClip(float nearClip)								{ nearClip_ = nearClip; };		// ��O�̕\�����E�����̐ݒ�
	void SetFarClip(float farClip)									{ farClip_ = farClip; };		// ���̕\�����E�����̐ݒ�
};