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
			//�r���[�ƃ��C�g�̍쐬
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

		// �X�e�[�W��
		if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A) {
			App::GetApp()->GetScene<Scene>()->SetGameStage(GameStageKey::game);
		}
		// �^�C�g���ɖ߂�
		if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_B) {
			App::GetApp()->GetScene<Scene>()->SetGameStage(GameStageKey::title);
		}

		if (!m_ControlLock) {
			// �E�ړ�
			if (cntlVec[0].fThumbLX >= 0.8f) {
				if (m_StageNum != 5) {
					m_StageNum++;
					m_ControlLock = true;
				}
				ChangeSelect(m_StageNum);
			}
			// ���ړ�
			else if (cntlVec[0].fThumbLX <= -0.8f) {
				if (m_StageNum != 1) {
					m_StageNum--;
					m_ControlLock = true;
				}
				ChangeSelect(m_StageNum);
			}
		}
		// �X�e�B�b�N�����ȏ�|����Ă��Ȃ��ꍇ
		else {
			if (cntlVec[0].fThumbLX < 0.8f && cntlVec[0].fThumbLX > -0.8f) {
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
