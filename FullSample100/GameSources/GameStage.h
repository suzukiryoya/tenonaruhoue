/*!
@file GameStage.h
@brief �Q�[���X�e�[�W
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	enum class CameraSelect {
		startCamera,
		myCamera
	};

	//--------------------------------------------------------------------------------------
	//	�Q�[���X�e�[�W�N���X
	//--------------------------------------------------------------------------------------
	class GameStage : public Stage {
		CsvFile m_GameStageCsv;

		//StartCamera�p�̃r���[
		shared_ptr<SingleView> m_StartCameraView;
		//MyCamera�p�̃r���[
		shared_ptr<SingleView> m_MyCameraView;
		////ObjCamera�p�̃r���[
		//shared_ptr<SingleView> m_ObjCameraView;
		CameraSelect m_CameraSelect;
		//���̓n���h���[
		//InputHandler<GameStage> m_InputHandler;
		//�r���[�̍쐬
		void CreateViewLight();
		//�{�b�N�X�̍쐬
		void CreateFixedBox();
		//�S�[���I�u�W�F�N�g�̍쐬
		void CreateGoalObject();
		//�v���C���[�̍쐬
		void CreatePlayer();
		//�J�����}���̍쐬
		void CreateCameraman();
		//�J�����؂�ւ��p
		void CameraChangeSelect();
		//�r���[�̍쐬
		void CreateStage();

		wstring m_StageSelect_image,m_StageClear_image,m_GameOver_image, m_GameOver_image2,m_LStick,m_RStick,m_Abutton,m_NextStageText_image,m_TitleBackText_image1, m_TitleBackText_image2,m_Cursor_image,m_Brack_image;
		//shared_ptr<GameObject> gameover;
		shared_ptr<GameOverTitle_UI> gameover;
		shared_ptr<GameObject> gameover2;

		Vec3 m_SoundPos;

		//�X�e�[�W�I��p
		int m_SelectNum = 0;
		Vec3 m_RedMaskPos_1 = Vec3(-525.0f, -200.0f, 0.0f);
		Vec3 m_RedMaskPos_2 = Vec3(75.0f, -200.0f, 0.0f);
		bool m_GameClearFlag = false;
		bool m_GameOverFlag = false; 
		shared_ptr<GameClear_UI> m_Cursor;
		shared_ptr<GameOverTitle_UI> m_TextUI;
		float m_GameOverSceneTime = 0;
		Col4 m_TestColor = Col4(0, 0, 0, 1.0f);
		Vec3 m_PlayerPos;

		//BGM�X�V�p
		shared_ptr<SoundItem> m_bgm;
		int m_ClearCheck = 0;
		int m_GameOverCheck = 1;

		//���̊Ǘ��p
		bool m_SoundFlag = true;

		//�}�E�X�ʒu
		Point2D<int> m_MousePoint;

		//�X�^�[�g�J�����X�V�p
		float m_Speed = 5.0f;
		float m_time = 0;
		int m_check = 0;
		Vec3 m_Eye;
		Vec3 m_At;
	public:
		shared_ptr<Camera> m_ptrMyCamera;

		//�\�z�Ɣj��
		GameStage() :Stage(),
			m_StageSelect_image(L"cursor2.png"),
			m_StageClear_image(L"StageClear.png"),
			m_GameOver_image(L"GameOver.png"),
			m_GameOver_image2(L"GameOver2.png"),
			m_LStick(L"�J�[�\���̈ړ�.png"),
			m_RStick(L"�J�����ړ�.png"),
			m_Abutton(L"���u�̋N��.png"),
			m_NextStageText_image(L"���̃X�e�[�W��.png"),
			m_TitleBackText_image1(L"TitleText.png"),
			m_TitleBackText_image2(L"�^�C�g���ɖ߂�.png"),
			m_Cursor_image(L"Selection_triangle.png"),
			m_Brack_image(L"black.jpg"),
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

		//�X�^�[�g�J�����p
		void ToMyCamera();
		void SetStartCameraPos(Vec3 startCameraPos);
		Vec3 GetStartCameraPos();

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
		//void SetSoundPosition(Vec3 pos);
		//Vec3 GetSoundPosition();

	};
}
//end basecross

