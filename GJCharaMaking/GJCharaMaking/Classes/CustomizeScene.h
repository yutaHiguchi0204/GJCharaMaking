/* =====================================================================
//! @param		「CustomizeScene」class header
//! @create		Yuta Higuchi
//! @date		17/09/26
===================================================================== */

// including header
#include "Scene.h"
#include "Camera.h"
#include "Object.h"

// class
class CustomizeScene : public Scene
{
private:
	std::unique_ptr<Camera> camera_;				// カメラ

	std::unique_ptr<Object> skyDome_;				// 天球

public:
	CustomizeScene(Microsoft::WRL::ComPtr<ID3D11Device> device, Microsoft::WRL::ComPtr<ID3D11DeviceContext> context);
	virtual ~CustomizeScene() {};

	void Initialize() override;
	void Update() override;
	void Draw() override;
};