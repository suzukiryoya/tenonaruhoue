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
	class ResultStage : public Stage {
		//ビューの作成
		void CreateViewLight();
		void CreateBGM();
		void CreateUI();

		wstring m_Texture;

		vector<UI_Base> m_Select;

	public:
		//構築と破棄
		ResultStage() :Stage()
		{}
		virtual ~ResultStage() {}
		//初期化
		virtual void OnCreate()override;
		virtual void OnUpdate()override;
		void GameOverScene(wstring texture);
	};
}
//end basecross

