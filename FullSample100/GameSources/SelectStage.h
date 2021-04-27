/*!
@file GameStage.h
@brief ゲームステージ
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	ゲームステージクラス
	//--------------------------------------------------------------------------------------
	class SelectStage : public Stage {
		//ビューの作成
		void CreateViewLight();
		void CreateBGM();
		void CreateUI();
		wstring m_title_image;
	public:
		//構築と破棄
		SelectStage() :Stage(),
			m_title_image(L"title.png")
		{}
		virtual ~SelectStage() {}
		//初期化
		virtual void OnCreate()override;
		virtual void OnUpdate() override;
	};


}
//end basecross

