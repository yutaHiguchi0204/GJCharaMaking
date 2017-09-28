/* =====================================================================
//! @param		�uCustomizeScene�vclass header
//! @create		Yuta Higuchi
//! @date		17/09/26
===================================================================== */

// including header
#include "Scene.h"
#include "Camera.h"
#include "IModel.h"
#include "PartsView.h"

// class
class CustomizeScene : public Scene
{
private:
	std::unique_ptr<Camera> camera_;				// �J����

	std::unique_ptr<IModel> skyDome_;				// �V��
	std::unique_ptr<IModel> ground_;				// �n��
	std::unique_ptr<PartsView> partsView_;			// �p�[�c�r���[

public:
	CustomizeScene(Microsoft::WRL::ComPtr<ID3D11Device> device, Microsoft::WRL::ComPtr<ID3D11DeviceContext> context);
	virtual ~CustomizeScene() {};

	void Initialize() override;
	void Update() override;
	void Draw() override;
};