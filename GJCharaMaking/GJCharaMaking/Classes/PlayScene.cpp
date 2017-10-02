/*===============================================================
// @param	[PlayScene] class src 
// @create	Kazushi Shinohara
// @date	17/09/26
================================================================*/

// include 
#include "PlayScene.h"
#include "CollisionManager.h"
#include "Constant.h"
#include "DXTKManager.h"
#include "KeyboardDebuger.h"
#include "SoundManager.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace std;

// constructor
PlayScene::PlayScene(Microsoft::WRL::ComPtr<ID3D11Device> device, Microsoft::WRL::ComPtr<ID3D11DeviceContext> context)
	: Scene(device, context)
{
}

/*==============================================================
// @brief		initialize
// @param		none
// @return		none
===============================================================*/
void PlayScene::Initialize()
{
	// カメラの生成
	camera_ = make_shared<Camera>(SIZE_WINDOW_WIDTH, SIZE_WINDOW_HEIGHT);

	// カメラの初期化
	camera_->SetEyePos(Vector3(0.0f, 10.0f, -25.0f));
	camera_->SetRefPos(Vector3(0.0f, 10.0f, 0.0f));

	// 静的メンバの設定
	Object::InitializeStatic(device_, context_, camera_.get());

	// 天球モデルの読み込み
	skyDome_ = make_unique<IModel>();
	skyDome_->Initialize(L"skyDome");

	// 地面モデルの読み込み
	ground_ = make_unique<IModel>();
	ground_->Initialize(L"ground_200m");

	// プレイヤーの読み込み
	player_ = make_unique<Player>();
	player_->Initialize(CharaData::CHARA_PARTS_NUM);

	// シーン遷移用ボタンの読み込み
	sceneChanger_ = make_unique<SceneChangerButton>();
	sceneChanger_->Initialize(L"Custom");
	sceneChanger_->SetPos(Vector2(SIZE_WINDOW_WIDTH - 112.0f, 16.0f));

	// BGMの再生
	SoundManager& sound = SoundManager::GetInstance();
	sound.PlayAudio(SoundManager::SOUND::PLAY_BGM);
}

/*==============================================================
// @brief		update
// @param		none
// @return		none
===============================================================*/
void PlayScene::Update()
{
	// カメラの更新
	camera_->Update();

	// カメラをプレイヤー軸で動かす（キーボード操作）
	KeyboardDebuger& kd = KeyboardDebuger::GetInstance();
	kd.MoveCamera(camera_);

	// 天球の更新
	skyDome_->Update();

	// 地面の更新
	ground_->Update();

	// プレイヤーの更新
	player_->Update();

	// マウスの当たり判定チェック
	CheckCollision();
}

/*==============================================================
// @brief		draw
// @param		none
// @return		none
===============================================================*/
void PlayScene::Draw()
{
	// 天球の描画
	skyDome_->Draw();

	// 地面の描画
	ground_->Draw();

	// プレイヤーの描画
	player_->Draw();

	// シーン遷移用ボタンの描画
	sceneChanger_->Draw();
}

// =================================================
// @brief	当たり判定チェック
// @param	none
// @return	none
// =================================================
void PlayScene::CheckCollision()
{
	// マウス準備
	DXTKManager& dxtk = DXTKManager::GetInstance();
	Mouse::State state = dxtk.mouseTracker_->GetLastState();

	// 左クリックされたら
	if (dxtk.mouseTracker_->leftButton == Mouse::ButtonStateTracker::PRESSED)
	{
		// 当たり判定用ライブラリの生成
		CollisionManager& collision = CollisionManager::GetInstance();

		// シーン遷移用ボタン
		if (collision.IsPointerHit(Vector2(state.x, state.y), sceneChanger_->GetPos(), SIZE_SCENE_CHANGER_BUTTON))
		{
			// プレイシーンへ移行
			ChangeScene(CUSTOMIZE);

			// 音の停止
			SoundManager& sound = SoundManager::GetInstance();
			sound.StopAudio();

			// シーン遷移時SE
			sound.PlayAudio(SoundManager::SOUND::SCENE_CHANGE_SE);
		}
	}
}
