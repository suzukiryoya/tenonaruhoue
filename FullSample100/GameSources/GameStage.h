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

		wstring m_StageSelect_image,m_StageClear_image,m_GameOver_image, m_GameOver_image2,m_LStick,m_RStick,m_Abutton;
		shared_ptr<GameObject> gameover;
		shared_ptr<GameObject> gameover2;

		Vec3 m_SoundPos;

		//�}�E�X�ʒu
		Point2D<int> m_MousePoint;

	public:
		//�\�z�Ɣj��
		GameStage() :Stage(),
			m_StageSelect_image(L"cursor2.png"),
			m_StageClear_image(L"GameClear.png"),
			m_GameOver_image(L"GameOver.png"),
			m_GameOver_image2(L"GameOver2.png"),
			m_LStick(L"Analog_Stick.png"),
			m_RStick(L"Analog_StickR.png"),
			m_Abutton(L"A_Button.png"),

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

		//���̖����ꏊ�擾�p
		void SetSoundPosition(Vec3 pos);
		Vec3 GetSoundPosition();

	};



}
//end basecross

