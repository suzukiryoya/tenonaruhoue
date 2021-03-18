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
		wstring m_StageSelect_image;

	public:
		//�\�z�Ɣj��
		GameStage() :Stage(),
			m_StageSelect_image(L"cursor.png")
		{}
		virtual ~GameStage() {}
		//������
		virtual void OnCreate() override;
		virtual void CreateCellMap();
		virtual void SetCellMapCost();
	};


}
//end basecross

