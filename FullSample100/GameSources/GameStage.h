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

		wstring m_StageSelect_image,m_StageClear_image,m_GameOver_image, m_GameOver_image2,m_LStick,m_RStick,m_Abutton;
		shared_ptr<GameObject> gameover;
		shared_ptr<GameObject> gameover2;

		Vec3 m_SoundPos;

		//マウス位置
		Point2D<int> m_MousePoint;

		//カメラ更新用
		float m_Speed = 5.0f;
		float m_time = 0;
		int m_check = 0;
		Vec3 m_Eye = Vec3(0.0f, 20.0f, 0.0f);
		Vec3 m_At = Vec3(0.0f, 0.0f, 15.0f);

	public:
		//構築と破棄
		GameStage() :Stage(),
			m_StageSelect_image(L"cursor2.png"),
			m_StageClear_image(L"StageClear.png"),
			m_GameOver_image(L"GameOver.png"),
			m_GameOver_image2(L"GameOver2.png"),
			m_LStick(L"Analog_Stick.png"),
			m_RStick(L"Analog_StickR.png"),
			m_Abutton(L"A_Button.png"),

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

		//カメラを右スティックで移動
		Vec3 GetInputState();

		//音の鳴った場所取得用
		void SetSoundPosition(Vec3 pos);
		Vec3 GetSoundPosition();

	};
}
//end basecross

