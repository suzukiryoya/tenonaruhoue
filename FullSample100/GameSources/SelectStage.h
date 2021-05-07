#pragma once
#include "stdafx.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	�Z���N�g�X�e�[�W
	//--------------------------------------------------------------------------------------
	class SelectStage : public Stage {
		//�r���[�̍쐬
		void CreateViewLight();
		void CreateUI();

		void ChangeSelect(int num);
		vector<shared_ptr<Select_UI>> m_Select;
		int m_StageNum = 0;
		bool m_ControlLock;

		wstring m_Select_image;
		shared_ptr<SoundItem>m_BGM;
	public:
		//�\�z�Ɣj��
		SelectStage() :Stage(),
			m_Select_image(L"Choice screen background_2.png")
		{}
		virtual ~SelectStage() {}
		//������
		virtual void OnCreate()override;
		virtual void OnUpdate()override;

		int GetStageNum() { return m_StageNum; }
		vector<shared_ptr<Select_UI>> GetSelectStage() const { return m_Select; }
	};


}
//end basecross

