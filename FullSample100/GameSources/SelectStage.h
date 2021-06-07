#pragma once
#include "stdafx.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	セレクトステージ
	//--------------------------------------------------------------------------------------
	class SelectStage : public Stage {
		//ビューの作成
		void CreateViewLight();
		void ChangeSelect(int num);
		vector<shared_ptr<Select_UI>> m_Select;
		//カーソル移動用
		shared_ptr<Select_UI> m_Cursor_UI;
		Vec3 m_CursorPos = Vec3(0);

		int m_StageNum = 0;
		// ステージ選択上限
		int m_NumMax = 6;
		int m_NumMin = 0;
		// 選択時のスティックの傾き具合
		float FlameSlope = 0.8f;

		float SEVol = 0.1f;
		float SelectVol = 1.0f;

		float StageUISize = 512.0f;

		bool m_ControlLock;

		wstring m_Select_image;
		wstring m_Cursor_image;
		wstring m_Stage1;
		wstring m_Stage2;
		wstring m_Stage3;
		wstring m_Stage4;
		wstring m_Stage5;
		shared_ptr<SoundItem>m_BGM;
	public:
		//構築と破棄
		SelectStage() :Stage(),
			m_Select_image(L"Choice_screen_background_3.png"),
			m_Cursor_image(L"Selection_triangle.png"),
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

