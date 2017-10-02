/* =====================================================================
//! @param		「CustomizeScene」class src
//! @create		Yuta Higuchi
//! @date		17/09/26
===================================================================== */

// including header
#include "CustomizeScene.h"
#include "CharaData.h"
#include "CollisionManager.h"
#include "Constant.h"
#include "DXTKManager.h"
#include "KeyboardDebuger.h"
#include "SoundManager.h"

// namespace
using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace std;

// method

// constructor
CustomizeScene::CustomizeScene(Microsoft::WRL::ComPtr<ID3D11Device> device, Microsoft::WRL::ComPtr<ID3D11DeviceContext> context)
	: Scene(device, context)
{
}

// =================================================
// @brief	initialize
// @param	none
// @return	none
// =================================================
void CustomizeScene::Initialize()
{
	// カメラの生成
	camera_ = make_unique<Camera>(SIZE_WINDOW_WIDTH, SIZE_WINDOW_HEIGHT);

	// カメラの初期化
	camera_->SetEyePos(Vector3(9.0f, 10.0f, -25.0f));
	camera_->SetRefPos(Vector3(9.0f, 10.0f, 0.0f));

	// 静的メンバの設定
	Object::InitializeStatic(device_, context_, camera_.get());

	// 天球モデルの読み込み
	skyDome_ = make_unique<IModel>();
	skyDome_->Initialize(L"skyDome");

	// プレイヤーの読み込み
	player_ = make_unique<Player>();
	player_->Initialize(CharaData::CHARA_PARTS_NUM);

	// プレイヤーの回転角の初期化
	playerRot_ = 0.0f;

	// パーツビューの読み込み
	partsView_ = make_unique<PartsView>();
	partsView_->Initialize(L"customView");
	partsView_->LoadPanel();

	// シーン遷移用ボタンの読み込み
	sceneChanger_ = make_unique<SceneChangerButton>();
	sceneChanger_->Initialize(L"Play");
	sceneChanger_->SetPos(Vector2(SIZE_WINDOW_WIDTH - 112.0f, 16.0f));

	// BGMの再生
	SoundManager& sound = SoundManager::GetInstance();
	sound.PlayAudio(SoundManager::SOUND::CUSTOMIZE_BGM);
}

// =================================================
// @brief	update
// @param	none
// @return	none
// =================================================
void CustomizeScene::Update()
{
	// カメラの更新
	camera_->Update();

	// 天球の更新
	skyDome_->Update();

	// プレイヤーの更新
	player_->Update();

	// プレイヤーをローテーションさせる
	playerRot_ -= 0.01f;
	player_->GetRootParts()->SetRotate(Vector3(0, playerRot_, 0));

	// パーツビューの更新
	partsView_->Update();

	// マウスの当たり判定チェック
	CheckCollision();

	// キーボード処理（デバッグ用）
	KeyboardDebuger& kd = KeyboardDebuger::GetInstance();
	CharaData& data = CharaData::GetInstance();
	if (kd.ChangeCharaParts())
	{
		player_->ChangeParts(data.GetPartsGenre(), data.GetModelData(data.GetPartsGenre()));
		playerRot_ = 0.0f;

		// SEの再生
		SoundManager& sound = SoundManager::GetInstance();
		sound.PlayAudio(SoundManager::SOUND::PARTS_CHANGE_SE);
	}
}

// =================================================
// @brief	draw
// @param	none
// @return	none
// =================================================
void CustomizeScene::Draw()
{
	// 天球の描画
	skyDome_->Draw();

	// プレイヤーの描画
	player_->Draw();

	// パーツビューの描画
	partsView_->Draw();
	partsView_->DrawPanel();

	// シーン遷移用ボタンの描画
	sceneChanger_->Draw();
}

// =================================================
// @brief	当たり判定チェック
// @param	none
// @return	none
// =================================================
void CustomizeScene::CheckCollision()
{
	// マウス準備
	DXTKManager& dxtk = DXTKManager::GetInstance();
	Mouse::State state = dxtk.mouseTracker_->GetLastState();

	// 左クリックされたら
	if (dxtk.mouseTracker_->leftButton == Mouse::ButtonStateTracker::PRESSED)
	{
		CharaData& data = CharaData::GetInstance();

		// 当たり判定用ライブラリの生成
		CollisionManager& collision = CollisionManager::GetInstance();

		// パーツジャンル
		auto partsGenre = partsView_->GetPartsGenrePanel(); 
		for (auto parts : partsGenre)
		{
			// 現在選択中のものは通っても意味がないので処理しない
			if (parts->GetPanelNo() != data.GetPartsGenre())
			{
				if (collision.IsPointerHit(Vector2(state.x, state.y), parts->GetPos(), SIZE_PARTS_GENREPANEL))
				{
					// ジャンルパネルを押したときの処理
					int genreNo = parts->GetPanelNo();
					data.SetPartsGenre((CharaData::CHARA_PARTS)(genreNo));
				}
			}
		}

		// パーツパネル
		auto partsPanel = partsView_->GetPartsPanel(data.GetPartsGenre());
		for (auto parts : partsPanel)
		{
			// 現在選択中のものは通っても意味がないので処理しない
			if (parts->GetPanelNo() != data.GetModelData(data.GetPartsGenre()).partsNo)
			{
				if (collision.IsPointerHit(Vector2(state.x, state.y), parts->GetPos(), SIZE_PARTS_PANEL))
				{
					// パーツパネルを押したときの処理
					int panelNo = parts->GetPanelNo();

					data.SetModelData(
						data.GetPartsGenre(),
						(data.GetModelData(data.GetPartsGenre()).partsNo,
						(data.GetPartsData(data.GetPartsGenre()).at(panelNo)))
					);

					// プレイヤーのパーツ変更
					player_->ChangeParts(data.GetPartsGenre(), data.GetModelData(data.GetPartsGenre()));
					playerRot_ = 0.0f;
				}
			}
		}

		// シーン遷移用ボタン
		if (collision.IsPointerHit(Vector2(state.x, state.y), sceneChanger_->GetPos(), SIZE_SCENE_CHANGER_BUTTON))
		{
			// プレイシーンへ移行
			ChangeScene(PLAY);

			// 音の停止
			SoundManager& sound = SoundManager::GetInstance();
			sound.StopAudio();

			// シーン遷移時SE
			sound.PlayAudio(SoundManager::SOUND::SCENE_CHANGE_SE);
		}
	}
}