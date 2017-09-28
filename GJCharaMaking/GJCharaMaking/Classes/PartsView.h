/*===============================================================
// @param	[PartsView] class header
// @create	Yuki Matsumaru
// @date	17/09/27
================================================================*/

#pragma once

// including header
#include <CommonStates.h>
#include <wrl\client.h>

// class
class PartsView
{
private:
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> partsBoard;	// �p�[�c�r���[�̃e�N�X�`���n���h��

public:
	PartsView() {};
	virtual ~PartsView() {};

	void Initialize();
	void Update();
	void Draw();
};