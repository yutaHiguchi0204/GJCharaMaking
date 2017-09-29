/* =====================================================================
//! @param		「Camera」class src
//! @create		Yuta Higuchi
//! @date		17/09/26
===================================================================== */

// including header
#include "Camera.h"

// namespace
using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace std;

// method

// constructor
Camera::Camera(int width, int height)
{
	// ビュー行列関係の初期設定
	eyePos_ = Vector3(9.0f, 10.0f, -25.0f);
	refPos_ = Vector3(9.0f, 10.0f, 0.0f);
	upVec_ = Vector3(0.0f, 1.0f, 0.0f);
	view_ = GetViewMatrix();

	// プロジェクション行列関係の初期設定
	fovY_ = XMConvertToRadians(60.0f);
	aspect_ = (float)width / height;
	nearClip_ = 0.1f;
	farClip_ = 1000.0f;
}

// =================================================
// @brief	update
// @param	none
// @return	none
// =================================================
void Camera::Update()
{
	// ビュー行列の取得
	view_ = Matrix::CreateLookAt(eyePos_, refPos_, upVec_);

	// プロジェクション行列の取得
	proj_ = Matrix::CreatePerspectiveFieldOfView(fovY_, aspect_, nearClip_, farClip_);
}