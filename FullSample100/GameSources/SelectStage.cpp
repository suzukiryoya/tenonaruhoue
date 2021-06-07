#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	�Q�[���X�e�[�W�N���X����
	//--------------------------------------------------------------------------------------
	void SelectStage::CreateViewLight() {
		const Vec3 eye(0.0f, 5.0f, -5.0f);
		const Vec3 at(0.0f);
		auto PtrView = CreateView<SingleView>();
		//�r���[�̃J�����̐ݒ�
		auto PtrCamera = ObjectFactory::Create<MyCamera>();
		PtrView->SetCamera(PtrCamera);
		PtrCamera->SetEye(eye);
		PtrCamera->SetAt(at);
		//�}���`���C�g�̍쐬
		auto PtrMultiLight = CreateLight<MultiLight>();
		//�f�t�H���g�̃��C�e�B���O���w��
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
			//�r���[�ƃ��C�g�̍쐬
			CreateViewLight();
			AddGameObject<Select_UI>(
				Vec2(640.0f, 400.0f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(2.0f),
				10,
				Col4(1.0f),
				m_Select_image
				);
			m_Cursor_UI = AddGameObject<Select_UI>(
				Vec2(80.0f),
				Vec3(-125.0f, 300.0f, 0.0f),
				Vec3(2.0f),
				10,
				Col4(1.0f),
				m_Cursor_image
				);

			AddGameObject<Select_UI>(
				Vec2(512.0f, 512.0f),
				Vec3(200.0f, 240.0f, 1.0f),
				Vec3(2.0f),
				11,
				Col4(1.0f),
				m_Stage1
				);
			AddGameObject<Select_UI>(
				Vec2(512.0f, 512.0f),
				Vec3(200.0f, 100.0f, 1.0f),
				Vec3(2.0f),
				11,
				Col4(1.0f),
				m_Stage2
				);
			AddGameObject<Select_UI>(
				Vec2(512.0f, 512.0f),
				Vec3(200.0f, -40.0f, 1.0f),
				Vec3(2.0f),
				11,
				Col4(1.0f),
				m_Stage3
				);
			AddGameObject<Select_UI>(
				Vec2(512.0f, 512.0f),
				Vec3(200.0f, -180.0f, 1.0f),
				Vec3(2.0f),
				11,
				Col4(1.0f),
				m_Stage4
				);
			AddGameObject<Select_UI>(
				Vec2(512.0f, 512.0f),
				Vec3(200.0f, -320.0f, 1.0f),
				Vec3(2.0f),
				11,
				Col4(1.0f),
				m_Stage5
				);
			
		}
		catch (...) {
			throw;
		}

		auto XAPtr = App::GetApp()->GetXAudio2Manager();
		m_BGM = XAPtr->Start(L"Select.wav", XAUDIO2_LOOP_INFINITE, 1.0f);
	}

	void SelectStage::OnUpdate() {
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		auto XAPtr = App::GetApp()->GetXAudio2Manager();

		// �X�e�[�W��
		if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A) {
			App::GetApp()->GetScene<Scene>()->SetGameStage(GameStageKey::game);
			App::GetApp()->GetScene<Scene>()->SetStageNum(m_StageNum);
			XAPtr->Stop(m_BGM);
			App::GetApp()->GetScene<Scene>()->PlaySE(L"button01b.wav", 0.1f);
		}
		// �^�C�g���ɖ߂�
		if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_B) {
			App::GetApp()->GetScene<Scene>()->SetGameStage(GameStageKey::title);
			XAPtr->Stop(m_BGM);
			App::GetApp()->GetScene<Scene>()->PlaySE(L"button01b.wav", 0.1f);
		}

		if (!m_ControlLock) {
			// ��ړ�
			if (cntlVec[0].fThumbLY >= 0.8f) {
				if (m_StageNum != 1) {
					m_StageNum--;

					//�J�[�\���ړ��X�V
					m_CursorPos = m_Cursor_UI->GetUpdatePosition();
					m_CursorPos += Vec3(0.0f, 140.0f, 0.0f);
					m_Cursor_UI->SetUpdatePosition(m_CursorPos);

					m_ControlLock = true;
					App::GetApp()->GetScene<Scene>()->PlaySE(L"button01a.wav", 0.1f);
				}
			}
			// ���ړ�
			else if (cntlVec[0].fThumbLY <= -0.8f) {
				if (m_StageNum != 5) {
					m_StageNum++;

					//�J�[�\���ړ��X�V
					m_CursorPos = m_Cursor_UI->GetUpdatePosition();
					m_CursorPos += Vec3(0.0f, -140.0f, 0.0f);
					m_Cursor_UI->SetUpdatePosition(m_CursorPos);

					m_ControlLock = true;
					App::GetApp()->GetScene<Scene>()->PlaySE(L"button01a.wav", 0.1f);
				}
			}
		}
		// �X�e�B�b�N�����ȏ�|����Ă��Ȃ��ꍇ
		else {
			if (cntlVec[0].fThumbLY < 0.8f && cntlVec[0].fThumbLY > -0.8f) {
				m_ControlLock = false;
			}
		}
		// �X�e�[�W�I�����
		if (m_StageNum >= 6) {
			m_StageNum = 5;
		}
		else if (m_StageNum <= 0) {
			m_StageNum = 1;
		}
	}

}
//end basecross
