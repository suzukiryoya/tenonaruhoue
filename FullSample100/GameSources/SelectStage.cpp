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

	void SelectStage::CreateUI() {

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

	void SelectStage::CreateBGM() {
		App::GetApp()->GetScene<Scene>()->PlayBGM(L"ClearBGM.wav", 0.1f);
	}

	void SelectStage::OnCreate() {
		try {
			//ビューとライトの作成
			CreateViewLight();
			CreateBGM();
			CreateUI();
			AddGameObject<Select_UI>(
				Vec2(512.0f, 512.0f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(2.0f),
				10,
				Col4(1.0f),
				m_title_image
				);
		}
		catch (...) {
			throw;
		}
	}

	void SelectStage::OnUpdate() {
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();

		// ステージへ
		if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A) {
			App::GetApp()->GetScene<Scene>()->SetGameStage(GameStageKey::game);
		}
		// タイトルに戻る
		if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_B) {
			App::GetApp()->GetScene<Scene>()->SetGameStage(GameStageKey::title);
		}

		if (!m_ControlLock) {
			// 右移動
			if (cntlVec[0].fThumbLX >= 0.8f) {
				if (m_StageNum != 5) {
					m_StageNum++;
					m_ControlLock = true;
				}
				ChangeSelect(m_StageNum);
			}
			// 左移動
			else if (cntlVec[0].fThumbLX <= -0.8f) {
				if (m_StageNum != 1) {
					m_StageNum--;
					m_ControlLock = true;
				}
				ChangeSelect(m_StageNum);
			}
		}
		// スティックが一定以上倒されていない場合
		else {
			if (cntlVec[0].fThumbLX < 0.8f && cntlVec[0].fThumbLX > -0.8f) {
				m_ControlLock = false;
			}
		}
		// ステージ選択上限
		if (m_StageNum >= 6) {
			m_StageNum = 5;
		}
		else if (m_StageNum <= 0) {
			m_StageNum = 1;
		}
	}

}
//end basecross
