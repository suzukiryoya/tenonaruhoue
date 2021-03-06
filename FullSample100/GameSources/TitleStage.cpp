/*!
@file GameStage.cpp
@brief ゲームステージ実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	ゲームステージクラス実体
	//--------------------------------------------------------------------------------------
	void TitleStage::CreateViewLight() {
		const Vec3 eye(0.0f, 5.0f, -5.0f);
		const Vec3 at(0.0f);
		auto PtrView = CreateView<SingleView>();
		//ビューのカメラの設定
		auto PtrCamera = ObjectFactory::Create<Camera>();
		PtrView->SetCamera(PtrCamera);
		PtrCamera->SetEye(eye);
		PtrCamera->SetAt(at);
		//マルチライトの作成
		auto PtrMultiLight = CreateLight<MultiLight>();
		//デフォルトのライティングを指定
		PtrMultiLight->SetDefaultLighting();
	}

	void TitleStage::OnCreate() {
		try {
			//ビューとライトの作成
			CreateViewLight();
			AddGameObject<Title_UI>(
				Vec2(TitleUISizeX, TitleUISizeY),
				Vec3(0.0f, -75.0f, 0.0f),
				Vec3(2.0f),
				10,
				Col4(TitleUIColor),
				m_title_image
				);

			AddGameObject<Title_UI>(
				Vec2(TitleUISizeX, TitleUISizeY),
				Vec3(0.0f, -250.0f, 0.0f),
				Vec3(1.3f),
				10,
				Col4(TitleUIColor),
				m_Push_image
				);
		}
		catch (...) {
			throw;
		}

		//BGM
		auto &XAPtr = App::GetApp()->GetXAudio2Manager();
		m_BGM = XAPtr->Start(L"titleBGM_Electronic_Circuit.wav",XAUDIO2_LOOP_INFINITE,0.15f);
	}

	//BGM停止
	void TitleStage::OnDestroy() {
		auto &XAPtr = App::GetApp()->GetXAudio2Manager();
		XAPtr->Stop(m_BGM);
	}

	void TitleStage::OnUpdate() {
		auto &cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();

		if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A) {
			App::GetApp()->GetScene<Scene>()->SetGameStage(GameStageKey::stageSelect);
		}
	}

}
//end basecross
