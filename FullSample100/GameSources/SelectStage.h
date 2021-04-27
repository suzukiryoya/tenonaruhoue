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
	class SelectStage : public Stage {
		//�r���[�̍쐬
		void CreateViewLight();
		void CreateBGM();
		void CreateUI();
		wstring m_title_image;
	public:
		//�\�z�Ɣj��
		SelectStage() :Stage(),
			m_title_image(L"title.png")
		{}
		virtual ~SelectStage() {}
		//������
		virtual void OnCreate()override;
		virtual void OnUpdate() override;
	};


}
//end basecross

