#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	ゲームステージクラス実体
	//--------------------------------------------------------------------------------------
	void SelectStage::CreateViewLight() {
		const Vec3 eye(0.0f, 5.0f, -5.0f);
		const Vec3 at(0.0f);
		auto PtrView = CreateView<SingleView>();
		//ビューのカメラの設定
		auto PtrCamera = ObjectFactory::Create<MyCamera>();
		PtrView->SetCamera(PtrCamera);
		PtrCamera->SetEye(eye);
		PtrCamera->SetAt(at);
		//マルチライトの作成
		auto PtrMultiLight = CreateLight<MultiLight>();
		//デフォルトのライティングを指定
		PtrMultiLight->SetDefaultLighting();
	}

	void SelectStage::ChangeSelect(int num) {
		for (int i = 0; i < 5; i++) {
			auto sel = GetSelectStage();
			if ((i + 1) == num) {
				sel[i]->SetSelect(true);
			}
			else {
				sel[i]->SetSelect(false);
			}
		}
	}


	void SelectStage::OnCreate() {
		try {
			//ビューとライトの作成
			CreateViewLight();
			// セレクト画面の背景
			AddGameObject<Select_UI>(
				Vec2(640.0f, 400.0f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(StageUIScale),
				10,
				Col4(StageUIColor),
				m_Select_image
				);
			// ステージ選択時のカーソル
			m_Cursor_UI = AddGameObject<Select_UI>(
				Vec2(80.0f),
				Vec3(-125.0f, 300.0f, 0.0f),
				Vec3(StageUIScale),
				10,
				Col4(StageUIColor),
				m_Cursor_image
				);
			// ステージ選択時のUI
			AddGameObject<Select_UI>(
				Vec2(StageUISize, StageUISize),
				Vec3(200.0f, 240.0f, 1.0f),
				Vec3(StageUIScale),
				11,
				Col4(StageUIColor),
				m_Stage1
				);
			AddGameObject<Select_UI>(
				Vec2(StageUISize, StageUISize),
				Vec3(200.0f, 100.0f, 1.0f),
				Vec3(StageUIScale),
				11,
				Col4(StageUIColor),
				m_Stage2
				);
			AddGameObject<Select_UI>(
				Vec2(StageUISize, StageUISize),
				Vec3(200.0f, -40.0f, 1.0f),
				Vec3(StageUIScale),
				11,
				Col4(StageUIColor),
				m_Stage3
				);
			AddGameObject<Select_UI>(
				Vec2(StageUISize, StageUISize),
				Vec3(200.0f, -180.0f, 1.0f),
				Vec3(StageUIScale),
				11,
				Col4(StageUIColor),
				m_Stage4
				);
			AddGameObject<Select_UI>(
				Vec2(StageUISize, StageUISize),
				Vec3(200.0f, -320.0f, 1.0f),
				Vec3(StageUIScale),
				11,
				Col4(StageUIColor),
				m_Stage5
				);
			
		}
		catch (...) {
			throw;
		}

		auto &XAPtr = App::GetApp()->GetXAudio2Manager();
		m_BGM = XAPtr->Start(L"Select.wav", XAUDIO2_LOOP_INFINITE, SelectVol);
	}

	void SelectStage::OnUpdate() {
		auto &cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		auto &XAPtr = App::GetApp()->GetXAudio2Manager();

		// ステージへ
		if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A) {
			App::GetApp()->GetScene<Scene>()->SetGameStage(GameStageKey::game);
			App::GetApp()->GetScene<Scene>()->SetStageNum(m_StageNum);
			XAPtr->Stop(m_BGM);
			App::GetApp()->GetScene<Scene>()->PlaySE(L"button01b.wav", SEVol);
		}
		// タイトルに戻る
		if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_B) {
			App::GetApp()->GetScene<Scene>()->SetGameStage(GameStageKey::title);
			XAPtr->Stop(m_BGM);
			App::GetApp()->GetScene<Scene>()->PlaySE(L"button01b.wav", SEVol);
		}

		if (!m_ControlLock) {
			// 上移動
			if (cntlVec[0].fThumbLY >= FlameSlope) {
				if (m_StageNum != 1) {
					m_StageNum--;

					//カーソル移動更新
					m_CursorPos = m_Cursor_UI->GetUpdatePosition();
					m_CursorPos += Vec3(0.0f, CursorPosY, 0.0f);
					m_Cursor_UI->SetUpdatePosition(m_CursorPos);

					m_ControlLock = true;
					App::GetApp()->GetScene<Scene>()->PlaySE(L"button01a.wav", SEVol);
				}
			}
			// 下移動
			else if (cntlVec[0].fThumbLY <= -FlameSlope) {
				if (m_StageNum != 5) {
					m_StageNum++;

					//カーソル移動更新
					m_CursorPos = m_Cursor_UI->GetUpdatePosition();
					m_CursorPos += Vec3(0.0f, -CursorPosY, 0.0f);
					m_Cursor_UI->SetUpdatePosition(m_CursorPos);

					m_ControlLock = true;
					App::GetApp()->GetScene<Scene>()->PlaySE(L"button01a.wav", SEVol);
				}
			}
		}
		// スティックが一定以上倒されていない場合
		else {
			if (cntlVec[0].fThumbLY < FlameSlope && cntlVec[0].fThumbLY > -FlameSlope) {
				m_ControlLock = false;
			}
		}
		// ステージ選択上限
		if (m_StageNum >= m_NumMax) {
			m_StageNum = 5;
		}
		else if (m_StageNum <= m_NumMin) {
			m_StageNum = 1;
		}
	}

}
//end basecross
