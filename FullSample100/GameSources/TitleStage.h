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
		void CreateUI();
		wstring m_title_image;
		wstring m_Push_image;

		//BGM
		shared_ptr<SoundItem>m_BGM;
	public:
		//�\�z�Ɣj��
		TitleStage() :Stage(),
			m_title_image(L"title.png"),
			m_Push_image(L"ButtonPush.png")
		{}
		virtual ~TitleStage() {}
		//������
		virtual void OnCreate()override;
		virtual void OnUpdate() override;
		virtual void OnDestroy();
	};


}
//end basecross

