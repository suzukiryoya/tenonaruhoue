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
	class TitleStage : public Stage {
		//�r���[�̍쐬
		void CreateViewLight();
		void CreateBackGround();
		void CreateBGM();
		void CreateUI();
	public:
		//�\�z�Ɣj��
		TitleStage() :Stage() {}
		virtual ~TitleStage() {}
		//������
		virtual void OnCreate()override;
	};


}
//end basecross

