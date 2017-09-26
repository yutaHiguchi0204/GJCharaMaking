/* =====================================================================
//! @param		ÅuCustomizeSceneÅvclass header
//! @create		Yuta Higuchi
//! @date		17/09/26
===================================================================== */

// including header
#include "Scene.h"

// class
class CustomizeScene : public Scene
{
public:
	CustomizeScene() {};
	~CustomizeScene() {};

	void Update() override;
	void Draw() override;
};