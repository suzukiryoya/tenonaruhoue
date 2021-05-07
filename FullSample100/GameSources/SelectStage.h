#pragma once
#include "stdafx.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	セレクトステージ
	//--------------------------------------------------------------------------------------
	class SelectStage : public Stage {
		//ビューの作成
		void CreateViewLight();
		void CreateUI();

		void ChangeSelect(int num);
		vector<shared_ptr<Select_UI>> m_Select;
		int m_StageNum = 0;
		bool m_ControlLock;

		wstring m_Select_image;
		wstring m_Stage1;
		wstring m_Stage2;
		wstring m_Stage3;
		wstring m_Stage4;
		wstring m_Stage5;
		shared_ptr<SoundItem>m_BGM;
	public:
		//構築と破棄
		SelectStage() :Stage(),
			m_Select_image(L"Choice screen background_2.png"),
			m_Stage1(L"FirstStage.png"),
			m_Stage2(L"SecondStage.png"),
			m_Stage3(L"ThirdStage.png"),
			m_Stage4(L"FourthStage.png"),
			m_Stage5(L"FifthStage.png")
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

