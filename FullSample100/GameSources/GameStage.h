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
	class GameStage : public Stage {
		CsvFile m_GameStageCsv;
		//ビューの作成
		void CreateViewLight();
		void CreateStage();
		void CreatePlayer();
		wstring m_StageSelect_image;

	public:
		//構築と破棄
		GameStage() :Stage(),
			m_StageSelect_image(L"cursor.png")
		{}
		virtual ~GameStage() {}
		//初期化
		virtual void OnCreate() override;
		virtual void CreateCellMap();
		virtual void SetCellMapCost();
	};


}
//end basecross

