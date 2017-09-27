/* =====================================================================
//! @param		「Camera」class header
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
	// ビュー行列関係
	DirectX::SimpleMath::Matrix view_;								// ビュー行列
	DirectX::SimpleMath::Vector3 eyePos_;							// 視点
	DirectX::SimpleMath::Vector3 refPos_;							// 注視点（参照点）
	DirectX::SimpleMath::Vector3 upVec_;							// 上方向ベクトル

	// プロジェクション行列関係
	DirectX::SimpleMath::Matrix proj_;								// プロジェクション行列
	float fovY_;													// 垂直方向視野角
	float aspect_;													// アスペクト比
	float nearClip_;												// 手前の表示限界距離
	float farClip_;													// 奥の表示限界距離

public:
	Camera(int width, int height);
	virtual ~Camera() {};

	virtual void Update();											// 更新処理

	inline const DirectX::SimpleMath::Matrix& GetViewMatrix()		{ return view_; };				// ビュー行列の取得
	inline const DirectX::SimpleMath::Matrix& GetProjectionMatrix()	{ return proj_; };				// プロジェクション行列の取得

	void SetEyePos(const DirectX::SimpleMath::Vector3& pos)			{ eyePos_ = pos; };				// 視点の設定
	void SetRefPos(const DirectX::SimpleMath::Vector3& pos)			{ refPos_ = pos; };				// 注視点の設定
	void SetUpVec(const DirectX::SimpleMath::Vector3& vec)			{ upVec_ = vec; };				// 上方向ベクトルの設定

	void SetFovY(float fovY)										{ fovY_ = fovY; };				// 垂直方向視野角の設定
	void SetAspect(float aspect)									{ aspect_ = aspect; };			// アスペクト比の設定
	void SetNearClip(float nearClip)								{ nearClip_ = nearClip; };		// 手前の表示限界距離の設定
	void SetFarClip(float farClip)									{ farClip_ = farClip; };		// 奥の表示限界距離の設定
};