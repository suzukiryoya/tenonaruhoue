#pragma once
#include "stdafx.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	セレクトステージ
	//--------------------------------------------------------------------------------------
	class SelectStage : public Stage {
		//ビューの作成
		void CreateViewLight();
		void CreateBGM();
		void CreateUI();

		void ChangeSelect(int num);
		vector<shared_ptr<Select_UI>> m_Select;
		int m_StageNum = 0;
		bool m_ControlLock;

		wstring m_title_image;
	public:
		//構築と破棄
		SelectStage() :Stage(),
			m_title_image(L"title.png")
		{}
		virtual ~SelectStage() {}
		//初期化
		virtual void OnCreate()override;
		virtual void OnUpdate()override;

		int GetStageNum() { return m_StageNum; }
		vector<shared_ptr<Select_UI>> GetSelectStage() const { return m_Select; }
	};


}
//end basecross

