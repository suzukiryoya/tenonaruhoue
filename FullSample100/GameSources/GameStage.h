/*!
@file GameStage.h
@brief �Q�[���X�e�[�W
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	�Q�[���X�e�[�W�N���X
	//--------------------------------------------------------------------------------------
	class GameStage : public Stage {
		CsvFile m_GameStageCsv;
		//�r���[�̍쐬

		void CreateViewLight();
		void CreateStage();
		void CreatePlayer();

		wstring m_StageSelect_image,m_StageClear_image,m_GameOver_image, m_GameOver_image2,m_LStick,m_RStick,m_Abutton,m_NextStageText_image,m_TitleBackText_image1, m_TitleBackText_image2,m_Red120_image;
		//shared_ptr<GameObject> gameover;
		shared_ptr<GameOverTitle_UI> gameover;
		shared_ptr<GameObject> gameover2;

		Vec3 m_SoundPos;

		//�X�e�[�W�I��p
		int m_SelectNum = 0;
		Vec3 m_RedMaskPos_1 = Vec3(-300.0f, 50.0f, 0.0f);
		Vec3 m_RedMaskPos_2 = Vec3(300.0f, 50.0f, 0.0f);
		bool m_GameClearFlag = false;
		bool m_GameOverFlag = false; 
		shared_ptr<GameClear_UI> m_RedMask;
		shared_ptr<GameOverTitle_UI> m_TextUI;
		float m_GameOverSceneTime = 0;
		Col4 m_TestColor = Col4(0, 0, 0, 1.0f);

		//BGM�X�V�p
		shared_ptr<SoundItem> m_bgm;
		int m_ClearCheck = 0;
		int m_GameOverCheck = 1;

		//�}�E�X�ʒu
		Point2D<int> m_MousePoint;

		//�J�����X�V�p
		float m_Speed = 5.0f;
		float m_time = 0;
		int m_check = 0;
		Vec3 m_Eye = Vec3(0.0f, 20.0f, 0.0f);
		Vec3 m_At = Vec3(0.0f, 0.0f, 15.0f);

	public:
		//�\�z�Ɣj��
		GameStage() :Stage(),
			m_StageSelect_image(L"cursor2.png"),
			m_StageClear_image(L"StageClear.png"),
			m_GameOver_image(L"GameOver.png"),
			m_GameOver_image2(L"GameOver2.png"),
			m_LStick(L"Analog_Stick.png"),
			m_RStick(L"Analog_StickR.png"),
			m_Abutton(L"A_Button_3.png"),
			m_NextStageText_image(L"A_Button_5.png"),
			m_TitleBackText_image1(L"TitleText.png"),
			m_TitleBackText_image2(L"B_Button_1.png"),
			m_Red120_image(L"Red120.png"),
			m_MousePoint(0, 0)
		{}
		virtual ~GameStage() {}
		//������
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
		virtual void CreateCellMap();
		virtual void SetCellMapCost();

		Point2D<int> GetMousePoint()const {
			return m_MousePoint;
		}

		//�Q�[���N���A�p
		void GameClearScene();
		void GameClearBGM();

		//�Q�[���I�[�o�[�p
		void GameOverScene();
		void GameOverBGM();

		//�}�E�X�ƃJ�����̃��C�̎擾
		void GetMouseRay(Vec3& Near, Vec3& Far);
		//�}�E�X�ɂ��I�u�W�F�N�g�I���̃N���A
		void SelectClear();
		//�}�E�X�̍��{�^��(�������u��)
		void OnLButtonEnter();
		//�}�E�X�̍��{�^��(������)
		void OnLButtonUp();
		//�}�E�X�̉E�{�^��(�������u��)
		void OnRButtonEnter();

		//�J�������E�X�e�B�b�N�ňړ�
		Vec3 GetInputState();

		//���̖����ꏊ�擾�p
		void SetSoundPosition(Vec3 pos);
		Vec3 GetSoundPosition();

	};
}
//end basecross

