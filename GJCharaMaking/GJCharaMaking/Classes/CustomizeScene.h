/* =====================================================================
//! @param		「CustomizeScene」class header
//! @create		Yuta Higuchi
//! @date		17/09/26
===================================================================== */

// including header
#include "Scene.h"
#include "Camera.h"
#include "IModel.h"

// class
class CustomizeScene : public Scene
{
private:
	std::unique_ptr<Camera> camera_;				// カメラ

	std::unique_ptr<IModel> skyDome_;				// 天球
	std::unique_ptr<IModel> ground_;				// 地面

public:
	CustomizeScene(Microsoft::WRL::ComPtr<ID3D11Device> device, Microsoft::WRL::ComPtr<ID3D11DeviceContext> context);
	virtual ~CustomizeScene() {};

	void Initialize() override;
	void Update() override;
	void Draw() override;
};