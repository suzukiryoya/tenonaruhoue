/*!
@file GameStage.h
@brief ゲームステージ
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	enum class CameraSelect {
		startCamera,
		myCamera
	};

	//--------------------------------------------------------------------------------------
	//	ゲームステージクラス
	//--------------------------------------------------------------------------------------
	class GameStage : public Stage {
		CsvFile m_GameStageCsv;

		//StartCamera用のビュー
		shared_ptr<SingleView> m_StartCameraView;
		//MyCamera用のビュー
		shared_ptr<SingleView> m_MyCameraView;
		////ObjCamera用のビュー
		//shared_ptr<SingleView> m_ObjCameraView;
		CameraSelect m_CameraSelect;
		//入力ハンドラー
		//InputHandler<GameStage> m_InputHandler;
		//ビューの作成
		void CreateViewLight();
		//ボックスの作成
		void CreateFixedBox();
		//ゴールオブジェクトの作成
		void CreateGoalObject();
		//プレイヤーの作成
		void CreatePlayer();
		//カメラマンの作成
		void CreateCameraman();
		//カメラ切り替え用
		void CameraChangeSelect();
		//ビューの作成
		void CreateStage();

		wstring m_StageSelect_image,m_StageClear_image,m_GameOver_image, m_GameOver_image2,m_LStick,m_RStick,m_Abutton,m_NextStageText_image,m_TitleBackText_image1, m_TitleBackText_image2,m_Cursor_image,m_Brack_image;
		//shared_ptr<GameObject> gameover;
		shared_ptr<GameOverTitle_UI> gameover;
		shared_ptr<GameObject> gameover2;

		Vec3 m_SoundPos;

		//ステージ選択用
		int m_SelectNum = 0;
		Vec3 m_RedMaskPos_1 = Vec3(-525.0f, -200.0f, 0.0f);
		Vec3 m_RedMaskPos_2 = Vec3(75.0f, -200.0f, 0.0f);
		bool m_GameClearFlag = false;
		bool m_GameOverFlag = false; 
		shared_ptr<GameClear_UI> m_Cursor;
		shared_ptr<GameOverTitle_UI> m_TextUI;
		float m_GameOverSceneTime = 0;
		Col4 m_TestColor = Col4(0, 0, 0, 1.0f);
		Vec3 m_PlayerPos;

		//BGM更新用
		shared_ptr<SoundItem> m_bgm;
		int m_ClearCheck = 0;
		int m_GameOverCheck = 1;

		//音の管理用
		bool m_SoundFlag = true;

		//マウス位置
		Point2D<int> m_MousePoint;

		//スタートカメラ更新用
		float m_Speed = 5.0f;
		float m_time = 0;
		int m_check = 0;
		Vec3 m_Eye;
		Vec3 m_At;
	public:
		shared_ptr<Camera> m_ptrMyCamera;

		//構築と破棄
		GameStage() :Stage(),
			m_StageSelect_image(L"cursor2.png"),
			m_StageClear_image(L"StageClear.png"),
			m_GameOver_image(L"GameOver.png"),
			m_GameOver_image2(L"GameOver2.png"),
			m_LStick(L"カーソルの移動.png"),
			m_RStick(L"カメラ移動.png"),
			m_Abutton(L"装置の起動.png"),
			m_NextStageText_image(L"次のステージへ.png"),
			m_TitleBackText_image1(L"TitleText.png"),
			m_TitleBackText_image2(L"タイトルに戻る.png"),
			m_Cursor_image(L"Selection_triangle.png"),
			m_Brack_image(L"black.jpg"),
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

		//スタートカメラ用
		void ToMyCamera();
		void SetStartCameraPos(Vec3 startCameraPos);
		Vec3 GetStartCameraPos();

		//ゲームクリア用
		void GameClearScene();
		void GameClearBGM();

		//ゲームオーバー用
		void GameOverScene();
		void GameOverBGM();

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
		//void SetSoundPosition(Vec3 pos);
		//Vec3 GetSoundPosition();

	};
}
//end basecross

