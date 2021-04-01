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

		//マウス位置
		Point2D<int> m_MousePoint;

	public:
		//構築と破棄
		GameStage() :Stage(),
			m_StageSelect_image(L"cursor2.png"),
			m_MousePoint(0, 0)
		{}
		virtual ~GameStage() {}
		//初期化
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
		virtual void CreateCellMap();
		virtual void SetCellMapCost();

		Point2D<int> GetMousePoint()const {
			return m_MousePoint;
		}
		//マウスとカメラのレイの取得
		void GetMouseRay(Vec3& Near, Vec3& Far);
		//マウスによるオブジェクト選択のクリア
		void SelectClear();
		//マウスの左ボタン(押した瞬間)
		void OnLButtonEnter();
		//マウスの左ボタン(離した)
		void OnLButtonUp();
		//マウスの右ボタン(押した瞬間)
		void OnRButtonEnter();
	};



}
//end basecross

