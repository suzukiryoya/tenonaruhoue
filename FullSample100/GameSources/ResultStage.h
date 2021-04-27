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
	class ResultStage : public Stage {
		//�r���[�̍쐬
		void CreateViewLight();
		void CreateBGM();
		void CreateUI();

		wstring m_Texture;

	public:
		//�\�z�Ɣj��
		ResultStage() :Stage() {}
		virtual ~ResultStage() {}
		//������
		virtual void OnCreate()override;
		virtual void OnUpdate()override;
		void GameOverStage(wstring texture);
	};
}
//end basecross

