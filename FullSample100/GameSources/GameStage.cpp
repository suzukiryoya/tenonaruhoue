/*!-
@file GameStage.cpp
@brief ゲームステージ実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	ゲームステージクラス実体
	//--------------------------------------------------------------------------------------
	void GameStage::CreateViewLight() {

		const Vec3 eye(0.0f, 20.0f, -5.0f);
		const Vec3 at(0.0f,0.0f,0.0f);
		auto PtrView = CreateView<SingleView>();
		//ビューのカメラの設定
		auto PtrCamera = ObjectFactory::Create<MyCamera>();
		PtrView->SetCamera(PtrCamera);
		PtrCamera->SetEye(eye);
		PtrCamera->SetAt(at);
		//マルチライトの作成
		auto PtrMultiLight = CreateLight<MultiLight>();
		//デフォルトのライティングを指定
		PtrMultiLight->SetDefaultLighting();
	}

	void GameStage::CreateStage() {
		auto BoxesGroup = CreateSharedObjectGroup(L"StageObject");

		vector<wstring> LineVec1;  //床
		vector<wstring> LineVec2;  //
		vector<wstring> LineVec3;  //
		vector<wstring> LineVec4;  //
		vector<wstring> LineVec5;  //
		vector<wstring> LineVec6;  // 
		vector<wstring> LineVec7;  //
		vector<wstring> LineVec8;  // 
		vector<wstring> LineVec9;  //
		vector<wstring> LineVec10; //

		//床
		m_GameStageCsv.GetSelect(LineVec1, 0, L"Floor");
		for (auto& v : LineVec1)
		{
			//トークン（カラム）の配列
			vector<wstring> Tokens;
			//トークン（カラム）単位で文字列を抽出(L','をデリミタとして区分け)
			Util::WStrToTokenVector(Tokens, v, L',');
			//各トークン（カラム）をスケール、回転、位置に読み込む
			Vec3 Scale(
				(float)_wtof(Tokens[1].c_str()),
				(float)_wtof(Tokens[2].c_str()),
				(float)_wtof(Tokens[3].c_str())
			);
			Vec3 Rot;
			//回転はXM_PIDIV2の文字列になっている場合がある
			Rot.x = (Tokens[4] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[4].c_str());
			Rot.y = (Tokens[5] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[5].c_str());
			Rot.z = (Tokens[6] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[6].c_str());
			Vec3 Pos(
				(float)_wtof(Tokens[7].c_str()),
				(float)_wtof(Tokens[8].c_str()),
				(float)_wtof(Tokens[9].c_str())
			);

			auto floor = AddGameObject<Floor>(Scale, Rot, Pos, 1.0f, 1.0f);
			BoxesGroup->IntoGroup(floor);
		}
		//壁
		m_GameStageCsv.GetSelect(LineVec2, 0, L"Wall");
		for (auto& v : LineVec2)
		{
			//トークン（カラム）の配列
			vector<wstring> Tokens;
			//トークン（カラム）単位で文字列を抽出(L','をデリミタとして区分け)
			Util::WStrToTokenVector(Tokens, v, L',');
			//各トークン（カラム）をスケール、回転、位置に読み込む
			Vec3 Scale(
				(float)_wtof(Tokens[1].c_str()),
				(float)_wtof(Tokens[2].c_str()),
				(float)_wtof(Tokens[3].c_str())
			);
			Vec3 Rot;
			//回転はXM_PIDIV2の文字列になっている場合がある
			Rot.x = (Tokens[4] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[4].c_str());
			Rot.y = (Tokens[5] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[5].c_str());
			Rot.z = (Tokens[6] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[6].c_str());
			Vec3 Pos(
				(float)_wtof(Tokens[7].c_str()),
				(float)_wtof(Tokens[8].c_str()),
				(float)_wtof(Tokens[9].c_str())
			);

			auto wall = AddGameObject<Wall>(Scale, Rot, Pos, 1.0f, 1.0f);
			wall->AddTag(L"Wall");
			BoxesGroup->IntoGroup(wall);
		}
		//敵1
		m_GameStageCsv.GetSelect(LineVec3, 0, L"Enemy1");
		for (auto& v : LineVec3)
		{
			//トークン（カラム）の配列
			vector<wstring> Tokens;
			//トークン（カラム）単位で文字列を抽出(L','をデリミタとして区分け)
			Util::WStrToTokenVector(Tokens, v, L',');
			//各トークン（カラム）をスケール、回転、位置に読み込む
			Vec3 Scale(
				(float)_wtof(Tokens[1].c_str()),
				(float)_wtof(Tokens[2].c_str()),
				(float)_wtof(Tokens[3].c_str())
			);
			Vec3 Rot;
			//回転はXM_PIDIV2の文字列になっている場合がある
			Rot.x = (Tokens[4] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[4].c_str());
			Rot.y = (Tokens[5] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[5].c_str());
			Rot.z = (Tokens[6] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[6].c_str());
			Vec3 Pos(
				(float)_wtof(Tokens[7].c_str()),
				(float)_wtof(Tokens[8].c_str()),
				(float)_wtof(Tokens[9].c_str())
			);

			auto enemy1 = AddGameObject<Enemy1>(Scale, Rot, Pos);
			enemy1->AddTag(L"Enemy1");
			BoxesGroup->IntoGroup(enemy1);
		}
		//敵2
		//m_GameStageCsv.GetSelect(LineVec4, 0, L"Enemy2");
		//for (auto& v : LineVec4)
		//{
		//	//トークン（カラム）の配列
		//	vector<wstring> Tokens;
		//	//トークン（カラム）単位で文字列を抽出(L','をデリミタとして区分け)
		//	Util::WStrToTokenVector(Tokens, v, L',');
		//	//各トークン（カラム）をスケール、回転、位置に読み込む
		//	Vec3 Scale(
		//		(float)_wtof(Tokens[1].c_str()),
		//		(float)_wtof(Tokens[2].c_str()),
		//		(float)_wtof(Tokens[3].c_str())
		//	);
		//	Vec3 Rot;
		//	//回転はXM_PIDIV2の文字列になっている場合がある
		//	Rot.x = (Tokens[4] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[4].c_str());
		//	Rot.y = (Tokens[5] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[5].c_str());
		//	Rot.z = (Tokens[6] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[6].c_str());
		//	Vec3 Pos(
		//		(float)_wtof(Tokens[7].c_str()),
		//		(float)_wtof(Tokens[8].c_str()),
		//		(float)_wtof(Tokens[9].c_str())
		//	);

		//	auto enemy2 = AddGameObject<Enemy2>(Scale, Rot, Pos,1.0f, 1.0f);
		//	enemy2->AddTag(L"Enemy2");
		//	BoxesGroup->IntoGroup(enemy2);
		//}
		//扉
		m_GameStageCsv.GetSelect(LineVec5, 0, L"Door");
		for (auto& v : LineVec5) {
			//トークン（カラム）の配列
			vector<wstring> Tokens;
			//トークン（カラム）単位で文字列を抽出(L','をデリミタとして区分け)
			Util::WStrToTokenVector(Tokens, v, L',');
			//各トークン（カラム）をスケール、回転、位置に読み込む
			Vec3 Scale(
				(float)_wtof(Tokens[1].c_str()),
				(float)_wtof(Tokens[2].c_str()),
				(float)_wtof(Tokens[3].c_str())
			);
			Vec3 Rot;
			//回転はXM_PIDIV2の文字列になっている場合がある
			Rot.x = (Tokens[4] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[4].c_str());
			Rot.y = (Tokens[5] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[5].c_str());
			Rot.z = (Tokens[6] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[6].c_str());
			Vec3 Pos(
				(float)_wtof(Tokens[7].c_str()),
				(float)_wtof(Tokens[8].c_str()),
				(float)_wtof(Tokens[9].c_str())
			);

			auto door = AddGameObject<Door>(Scale, Rot, Pos, 1.0f, 1.0f);
			door->AddTag(L"Door");
			BoxesGroup->IntoGroup(door);
		}
		//ゴール
		m_GameStageCsv.GetSelect(LineVec6, 0, L"Goal");
		for (auto& v : LineVec6) {
			//トークン（カラム）の配列
			vector<wstring> Tokens;
			//トークン（カラム）単位で文字列を抽出(L','をデリミタとして区分け)
			Util::WStrToTokenVector(Tokens, v, L',');
			//各トークン（カラム）をスケール、回転、位置に読み込む
			Vec3 Scale(
				(float)_wtof(Tokens[1].c_str()),
				(float)_wtof(Tokens[2].c_str()),
				(float)_wtof(Tokens[3].c_str())
			);
			Vec3 Rot;
			//回転はXM_PIDIV2の文字列になっている場合がある
			Rot.x = (Tokens[4] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[4].c_str());
			Rot.y = (Tokens[5] == L"XM_PIDIV2") ? XM_PI : (float)_wtof(Tokens[5].c_str());
			Rot.z = (Tokens[6] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[6].c_str());
			Vec3 Pos(
				(float)_wtof(Tokens[7].c_str()),
				(float)_wtof(Tokens[8].c_str()),
				(float)_wtof(Tokens[9].c_str())
			);

			auto goal = AddGameObject<Goal>(Scale, Rot, Pos, 1.0f, 1.0f);
			goal->AddTag(L"Goal");
			BoxesGroup->IntoGroup(goal);
		}
		//スタート
		m_GameStageCsv.GetSelect(LineVec7, 0, L"Start");
		for (auto& v : LineVec7) {
			//トークン（カラム）の配列
			vector<wstring> Tokens;
			//トークン（カラム）単位で文字列を抽出(L','をデリミタとして区分け)
			Util::WStrToTokenVector(Tokens, v, L',');
			//各トークン（カラム）をスケール、回転、位置に読み込む
			Vec3 Scale(
				(float)_wtof(Tokens[1].c_str()),
				(float)_wtof(Tokens[2].c_str()),
				(float)_wtof(Tokens[3].c_str())
			);
			Vec3 Rot;
			//回転はXM_PIDIV2の文字列になっている場合がある
			Rot.x = (Tokens[4] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[4].c_str());
			Rot.y = (Tokens[5] == L"XM_PIDIV2") ? XM_PI : (float)_wtof(Tokens[5].c_str());
			Rot.z = (Tokens[6] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[6].c_str());
			Vec3 Pos(
				(float)_wtof(Tokens[7].c_str()),
				(float)_wtof(Tokens[8].c_str()),
				(float)_wtof(Tokens[9].c_str())
			);

			auto start = AddGameObject<Start>(Scale, Rot, Pos, 1.0f, 1.0f);
			start->AddTag(L"Start");
			BoxesGroup->IntoGroup(start);
		}
		//サウンドブロック
		m_GameStageCsv.GetSelect(LineVec8, 0, L"SoundBlock");
		for (auto& v : LineVec8) {
			//トークン（カラム）の配列
			vector<wstring> Tokens;
			//トークン（カラム）単位で文字列を抽出(L','をデリミタとして区分け)
			Util::WStrToTokenVector(Tokens, v, L',');
			//各トークン（カラム）をスケール、回転、位置に読み込む
			Vec3 Scale(
				(float)_wtof(Tokens[1].c_str()),
				(float)_wtof(Tokens[2].c_str()),
				(float)_wtof(Tokens[3].c_str())
			);
			Vec3 Rot;
			//回転はXM_PIDIV2の文字列になっている場合がある
			Rot.x = (Tokens[4] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[4].c_str());
			Rot.y = (Tokens[5] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[5].c_str());
			Rot.z = (Tokens[6] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[6].c_str());
			Vec3 Pos(
				(float)_wtof(Tokens[7].c_str()),
				(float)_wtof(Tokens[8].c_str()),
				(float)_wtof(Tokens[9].c_str())
			);

			auto soundBlock = AddGameObject<FixedBox>(Scale, Rot, Pos);
			soundBlock->AddTag(L"SoundBlock");
			BoxesGroup->IntoGroup(soundBlock);
		}
		//プレイヤー
		m_GameStageCsv.GetSelect(LineVec9, 0, L"Player");
		for (auto& v : LineVec9) {
			//トークン（カラム）の配列
			vector<wstring> Tokens;
			//トークン（カラム）単位で文字列を抽出(L','をデリミタとして区分け)
			Util::WStrToTokenVector(Tokens, v, L',');
			//各トークン（カラム）をスケール、回転、位置に読み込む
			Vec3 Scale(
				(float)_wtof(Tokens[1].c_str()),
				(float)_wtof(Tokens[2].c_str()),
				(float)_wtof(Tokens[3].c_str())
			);
			Vec3 Rot;
			//回転はXM_PIDIV2の文字列になっている場合がある
			Rot.x = (Tokens[4] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[4].c_str());
			Rot.y = (Tokens[5] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[5].c_str()) ||
					(Tokens[5] == L"ーXM_PIDIV2") ? -XM_PIDIV2 : (float)_wtof(Tokens[5].c_str());
			Rot.z = (Tokens[6] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[6].c_str());
			Vec3 Pos(
				(float)_wtof(Tokens[7].c_str()),
				(float)_wtof(Tokens[8].c_str()),
				(float)_wtof(Tokens[9].c_str())
			);
			auto ptrCellmap = GetSharedGameObject<StageCellMap>(L"StageCellMap");
			auto player = AddGameObject<Playerdummy>(Scale, Rot, Pos);
			player->AddTag(L"Player");
			//SetSharedGameObject(L"Player", player);

			BoxesGroup->IntoGroup(player);
		}
	}

	void GameStage::CreatePlayer()
	{
		//auto ptrCellmap = GetSharedGameObject<StageCellMap>(L"StageCellMap");
		//auto player =  AddGameObject<Player>(Vec3(1.0f), Vec3(0, 90,0), Vec3(-10.0f,2.0f,5.0f), ptrCellmap);
		////シェア配列にプレイヤーを追加
		//SetSharedGameObject(L"Player", player);

		//player->AddTag(L"Player");

	}

	void GameStage::CreateCellMap() {
		float PieceSize = 1.0f;

		auto Ptr = AddGameObject<StageCellMap>(Vec3(-15.5f, 1.0f, -15.5f), PieceSize, 30, 30);
		SetSharedGameObject(L"StageCellMap", Ptr);
		CreateStage();
		SetCellMapCost();
	}
	void GameStage::SetCellMapCost() {
		auto PtrCellMap = GetSharedGameObject<StageCellMap>(L"StageCellMap");
		auto BoxGroup = GetSharedObjectGroup(L"StageObject");
		auto& CellVec = PtrCellMap->GetCellVec();
		auto& BoxVec = BoxGroup->GetGroupVector();
		vector<AABB> ObjectAABBVec;
		for (auto& v : BoxVec)
		{
			auto FixedBoxPtr = dynamic_pointer_cast<Wall>(v.lock());
			if (FixedBoxPtr)
			{
				auto ColPtr = FixedBoxPtr->GetComponent<CollisionObb>();
				ObjectAABBVec.push_back(ColPtr->GetObb().GetWrappedAABB());
			}
		}
		for (auto& v : CellVec) {
			for (auto& v2 : v) {
				for (auto& vObj : ObjectAABBVec) {
					if (HitTest::AABB_AABB_NOT_EQUAL(v2.m_PieceRange, vObj)) {
						v2.m_Cost = -1;
						break;
					}
				}
			}
		}
	}

	void GameStage::OnCreate() {
		try {

			App::GetApp()->GetScene<Scene>()->SetUpdateBool(false);

			//物理計算有効
			SetPhysicsActive(true);

			wstring MediaDir;
			App::GetApp()->GetDataDirectory(MediaDir);

			//AddGameObject<FixedBox>(Vec3(1.0f),Vec3(0.0f),Vec3(0.0f,1.0f,0.0f));
			//AddGameObject<Kakuninn>(Vec3(1.0f), Vec3(0.0f), Vec3(0.0f, 0.5f, 0.0f));
			AddGameObject<ActivePsBox>(Vec3(1.0f), Vec3(0.0f), Vec3(0.0f, 3.0f, 0.0f));
			AddGameObject<Enemy1>(Vec3(1.0f), Vec3(0.0f), Vec3(4.0f, 1.2f, 0.0f));
			//AddGameObject<Playerdummy>(Vec3(1.0f), Vec3(0.0f), Vec3(-8.0f, 1.2f, 5.0f));
			AddGameObject<LineEffect>(Vec3(1.0f), Vec3(0.0f), Vec3(-8.0f, 0.8f, 5.0f));
			AddGameObject<CheckPointBox>(Vec3(1.0f), Vec3(0.0f), Vec3(0.0f, 0.0f, 5.0f));


			auto csvSet = App::GetApp()->GetScene<Scene>()->GetStageNum();
			switch (csvSet)
			{
			case 1:
				m_GameStageCsv.SetFileName(MediaDir + L"Stage1.csv");
				break;
			case 2:
				m_GameStageCsv.SetFileName(MediaDir + L"Stage2.csv");
				break;
			case 3:
				m_GameStageCsv.SetFileName(MediaDir + L"Stage3.csv");
				break;
			case 4:
				m_GameStageCsv.SetFileName(MediaDir + L"Stage4.csv");
				break;
			case 5:
				m_GameStageCsv.SetFileName(MediaDir + L"Stage5.csv");
				break;
			}

			
			m_GameStageCsv.ReadCsv();
			//ビューとライトの作成
			CreateViewLight();
			CreateCellMap();
			auto bgm = App::GetApp()->GetXAudio2Manager();
			m_bgm = bgm->Start(L"PlayBGM_Towards_the_Future.wav", XAUDIO2_LOOP_INFINITE, 0.1f);
			//App::GetApp()->GetScene<Scene>()->PlayBGM(L"PlayBGM_Towards_the_Future.wav", 0.1f);
			wstring dataDir;
			//サンプルのためアセットディレクトリを取得
			App::GetApp()->GetAssetsDirectory(dataDir);
			wstring strMovie = dataDir + L"cursor.png";
			AddGameObject<Clear>(
					Vec2(512.0f, 512.0f),
					Vec3(0.0f, 240.0f, 0.0f),
					Vec3(0.2f),
					10,
					Col4(1.0f),
				    m_StageSelect_image
				);

			gameover = AddGameObject<GameOverTitle_UI>(
				Vec2(512.0f, 512.0f),
				Vec3(0.0f, 8.0f, 0.0f),
				Vec3(1.3f),
				10,
				Col4(1.0f),
				m_GameOver_image
				);
			gameover2 = AddGameObject<GameOverTitle_UI>(
				Vec2(512.0f, 512.0f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(1.5f),
				10,
				Col4(1.0f),
				m_GameOver_image2
				);


			AddGameObject<GameOverTitle_UI>(
				Vec2(512.0f, 512.0f),
				Vec3(-450.0f, -325.0f, 0.0f),
				Vec3(1.0f),
				10,
				Col4(1.0f),
				m_LStick
				);

			AddGameObject<GameOverTitle_UI>(
				Vec2(512.0f, 512.0f),
				Vec3(450.0f, -325.0f, 0.0f),
				Vec3(1.0f),
				10,
				Col4(1.0f),
				m_RStick
				);
			AddGameObject<GameOverTitle_UI>(
				Vec2(512.0f, 512.0f),
				Vec3(450.0f, -150.0f, 0.0f),
				Vec3(1.0f),
				10,
				Col4(1.0f),
				m_Abutton
				);
			
			gameover->SetDrawActive(false);
			gameover2->SetDrawActive(false);
		}
		catch (...) {
			throw;
		}
	}

	Vec3 GameStage::GetInputState()
	{
		Vec3 ret(0, 0, 0);
		Vec3 angle(0, 0, 0);
		//コントローラの取得
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		WORD wButtons = 0;
		if (cntlVec[0].bConnected) {
			ret.x = cntlVec[0].fThumbRX;
			ret.z = cntlVec[0].fThumbRY;
			wButtons = cntlVec[0].wButtons;
		}
		float moveX = ret.x;
		float moveZ = ret.z;

		if (moveX != 0 || moveZ != 0) {
			float moveLength = 0;	//動いた時のスピード
			//コントローラの向き計算
			Vec2 moveVec(moveZ, moveX);
			float moveSize = moveVec.length();
			//コントローラの向きから角度を計算
			float cntlAngle = atan2(moveZ, moveX);
			//角度からベクトルを作成
			angle = Vec3(cos(cntlAngle), 0, sin(cntlAngle));
			//正規化する
			angle.normalize();
			//移動サイズを設定。
			angle *= moveSize;
			//Y軸は変化させない
			angle.y = 0;
		}
		return angle;
	}

	void GameStage::GameClearScene()
	{
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		//BGM用
		auto bgm = App::GetApp()->GetXAudio2Manager();
		//

		if (cntlVec[0].fThumbLX >= 0.8f)
		{
			m_Cursor->SetUpdatePosition(Vec3(m_RedMaskPos_2));
			App::GetApp()->GetScene<Scene>()->PlaySE(L"button01a.wav", 0.1f);
		}
		else if (cntlVec[0].fThumbLX <= -0.8f)
		{
			m_Cursor->SetUpdatePosition(Vec3(m_RedMaskPos_1));
			App::GetApp()->GetScene<Scene>()->PlaySE(L"button01a.wav", 0.1f);
		}
		else if (cntlVec[0].fThumbLX >= 0.8f && cntlVec[0].fThumbLX <= -0.8f)
		{

		}

		if (cntlVec[0].wPressedButtons && m_RedMaskPos_1 == m_Cursor->GetUpdatePosition())
		{
			auto StageNum = App::GetApp()->GetScene<Scene>()->GetStageNum();
			StageNum += 1;

			bgm->Stop(m_bgm);
			App::GetApp()->GetScene<Scene>()->PlaySE(L"button01b.wav", 0.1f);

			App::GetApp()->GetScene<Scene>()->SetStageNum(StageNum);
			App::GetApp()->GetScene<Scene>()->SetGameStage(GameStageKey::game);
		}
		else if (cntlVec[0].wPressedButtons && m_RedMaskPos_2 == m_Cursor->GetUpdatePosition())
		{
			bgm->Stop(m_bgm);
			App::GetApp()->GetScene<Scene>()->PlaySE(L"button01b.wav", 0.1f);

			App::GetApp()->GetScene<Scene>()->SetGameStage(GameStageKey::title);
		}

		//if (cntlVec[0].wPressedButtons && XINPUT_GAMEPAD_A)
		//{
		//	auto StageNum = App::GetApp()->GetScene<Scene>()->GetStageNum();
		//	StageNum += 1;

		//	bgm->Stop(m_bgm);

		//	App::GetApp()->GetScene<Scene>()->SetStageNum(StageNum);
		//	App::GetApp()->GetScene<Scene>()->SetGameStage(GameStageKey::game);
		//}
		//else if(cntlVec[0].wPressedButtons && XINPUT_GAMEPAD_B)
		//{
		//	App::GetApp()->GetScene<Scene>()->SetGameStage(GameStageKey::title);
		//}
	}

	void GameStage::GameClearBGM()
	{
		auto bgm = App::GetApp()->GetXAudio2Manager();
		m_bgm = bgm->Start(L"ClearBGM.wav", XAUDIO2_LOOP_INFINITE, 0.1f);
	}

	void GameStage::GameOverScene()
	{
		//GameOverBGM();
		if (m_GameOverSceneTime > 3.0f)
		{
			App::GetApp()->GetScene<Scene>()->SetGameStage(GameStageKey::title);
		}
	}

	void GameStage::OnUpdate()
	{
		//キーボード（マウス）の取得
		auto KeyState = App::GetApp()->GetInputDevice().GetKeyState();
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		auto CursorPos = App::GetApp()->GetScene<Scene>()->GetAngle();
		auto Check = App::GetApp()->GetScene<Scene>()->GetCheck();
		auto camera = GetView()->GetTargetCamera();
		auto elapsedTime = App::GetApp()->GetElapsedTime();

		m_Eye += GetInputState() * elapsedTime * m_Speed;
		m_At += GetInputState() * elapsedTime * m_Speed;

		camera->SetEye(m_Eye);
		camera->SetAt(m_At);

		m_MousePoint = KeyState.m_MouseClientPoint;

		m_SoundFlag = App::GetApp()->GetScene<Scene>()->GetSoundFlag();

		if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A && m_SoundFlag == true) {
			OnLButtonEnter();
		}
		else if (KeyState.m_bUpKeyTbl[VK_LBUTTON]) {
			OnLButtonUp();
		}
		else if (KeyState.m_bPressedKeyTbl[VK_RBUTTON]) {
			OnRButtonEnter();
		}

		//BGM用
		auto bgm = App::GetApp()->GetXAudio2Manager();
		//

		switch (Check)
		{
		case 0: //クリア用
			AddGameObject<Title_UI>(
				Vec2(512.0f, 512.0f),
				Vec3(0.0f, 120.0f, 0.0f),
				Vec3(1.0f),
				12,
				Col4(1.0f),
				m_StageClear_image
				);

			AddGameObject<Title_UI>(
				Vec2(324.0f, 324.0f),
				Vec3(-300.0f, -200.0f, 0.0f),
				Vec3(1.25f),
				15,
				Col4(1.0f),
				m_NextStageText_image
				);
			AddGameObject<Title_UI>(
				Vec2(324.0f, 324.0f),
				Vec3(300.0f, -200.0f, 0.0f),
				Vec3(1.25f),
				15,
				Col4(1.0f),
				m_TitleBackText_image2
				);
			m_Cursor = AddGameObject<GameClear_UI>(
				Vec2(80.0f),
				Vec3(m_RedMaskPos_1),
				Vec3(2.0f),
				15,
				Col4(1.0f),
				m_Cursor_image
				);
			AddGameObject<GameClear_UI>(
				Vec2(1920.0f, 1080.0f),
				Vec3(0.0f),
				Vec3(1.0f),
				10,
				Col4(1.0f,1.0f,1.0f,0.85f),
				m_Brack_image
				);
			bgm->Stop(m_bgm);
			GameClearBGM();
			//App::GetApp()->GetScene<Scene>()->PlaySE(L"ClearBGM.wav", 0.1f);
			App::GetApp()->GetScene<Scene>()->SetCheck(2);
			break;
		case 1: //ゲームオーバー用
			
			bgm->Stop(m_bgm);
			App::GetApp()->GetScene<Scene>()->PlaySE(L"GameOver.wav", 1.0f);

			//AddGameObject<Title_UI>(
			//	Vec2(512.0f, 512.0f),
			//	Vec3(0.0f, 80.0f, 0.0f),
			//	Vec3(1.5f),
			//	15,
			//	Col4(1.0f),
			//	m_TitleBackText_image1
			//	);
			gameover->SetDrawActive(true);
			App::GetApp()->GetScene<Scene>()->SetCheck(2);
			break;
		case 2:
			break;
		}

		if (m_ClearCheck == Check) {
			
			m_GameClearFlag = true;
		}
		else if (m_GameOverCheck == Check) {
			//ゲームオーバー用
			m_GameOverFlag = true;
			//
			//gameover->SetDrawActive(true);
		}

		if (m_GameClearFlag == true)
		{
			GameClearScene();
		}
		else if (m_GameClearFlag == false)
		{
		}

		if (m_GameOverFlag == true)
		{
			m_GameOverSceneTime += elapsedTime;
			GameOverScene();
		}
		else if (m_GameOverFlag == false)
		{
		}

		m_time += elapsedTime;

		if (m_time >= 3.0f&&m_check==0) {
		AddGameObject<LineEffect>(Vec3(1.0f), Vec3(0.0f), Vec3(-8.0f, 0.8f, 5.0f));

		AddGameObject<Enemy2>(Vec3(1.0f), Vec3(0.0f), Vec3(-8.0f, 1.2f, 5.0f));
		m_check = 1;
		}
	}

	void GameStage::GetMouseRay(Vec3& Near, Vec3& Far) {
		Mat4x4 world, view, proj;
		world.affineTransformation(
			Vec3(1.0f, 1.0f, 1.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f)
		);
		auto PtrCamera = GetView()->GetTargetCamera();
		view = PtrCamera->GetViewMatrix();
		proj = PtrCamera->GetProjMatrix();
		auto viewport = GetView()->GetTargetViewport();
		auto CursorPos= App::GetApp()->GetScene<Scene>()->GetAngle();

		//フルスクリーンだった時の対応
		App::GetApp()->GetDeviceResources()->GetD3DDevice();
		auto width = viewport.Width;
		auto height = viewport.Height;
		auto winLong = GetWindowLong(App::GetApp()->GetHWnd(), GWL_STYLE);
		if (!(winLong & WS_OVERLAPPEDWINDOW)) {
			//フルスクリーン
			width = (float)GetSystemMetrics(SM_CXSCREEN);
			height = (float)GetSystemMetrics(SM_CYSCREEN);
		}

		Near = XMVector3Unproject(
			Vec3((float)CursorPos.x+640, (float)CursorPos.y * -1 + 400, 0),
			viewport.TopLeftX,
			viewport.TopLeftY,
			width,
			height,
			viewport.MinDepth,
			viewport.MaxDepth,
			proj,
			view,
			world);

		Far = XMVector3Unproject(
			Vec3((float)CursorPos.x+640, (float)CursorPos.y * -1 + 400, 1.0),
			viewport.TopLeftX,
			viewport.TopLeftY,
			width,
			height,
			viewport.MinDepth,
			viewport.MaxDepth,
			proj,
			view,
			world);
	}

	void GameStage::SelectClear() {
		for (auto& v : GetGameObjectVec()) {
			auto PsPtr = dynamic_pointer_cast<ActivePsObject>(v);
			if (PsPtr) {
				PsPtr->SetSelected(false);
			}
		}
	}


	//マウスの左ボタン押した瞬間
	void GameStage::OnLButtonEnter() {
		SelectClear();
		auto PtrCamera = GetView()->GetTargetCamera();
		Vec3 Eye = PtrCamera->GetEye();

		vector<shared_ptr<ActivePsObject>> ObjVec;
		Vec3 NearPos, FarPos;
		GetMouseRay(NearPos, FarPos);
		for (auto& v : GetGameObjectVec()) {
			auto PsPtr = dynamic_pointer_cast<ActivePsObject>(v);
			if (PsPtr) {
				auto ColObb = PsPtr->GetComponent<CollisionObb>(false);
				auto ColSp = PsPtr->GetComponent<CollisionSphere>(false);
				auto ColCapsule = PsPtr->GetComponent<CollisionCapsule>(false);
				if (ColObb) {
					auto Obb = ColObb->GetObb();
					if (HitTest::SEGMENT_OBB(NearPos, FarPos, Obb)) {
						
						App::GetApp()->GetScene<Scene>()->SetSoundFlag(false);
						
						m_SoundFlag = App::GetApp()->GetScene<Scene>()->GetSoundFlag();

						auto a=Obb.m_Center;
						ObjVec.push_back(PsPtr);
						//AddGameObject<TriggerBox>(Vec3(10.0f, 2.0f, 10.0f), Vec3(0.0f), Vec3(a.x, 1.0f, a.z));
						AddGameObject<TriggerBox2>(Vec3(2.0f, 2.0f, 2.0f), Vec3(0), Vec3(a.x, 1.0f, a.z));
						SetSoundPosition(Vec3(a.x, 1.0f, a.z));
						App::GetApp()->GetScene<Scene>()->SetPosition(Vec3(a.x,1.0f,a.z));
						App::GetApp()->GetScene<Scene>()->SetSoundPosition(Vec3(a.x, 1.0f, a.z));
					}
				}
				else if (ColSp) {
					auto Sp = ColSp->GetSphere();
					if (HitTest::SEGMENT_SPHERE(NearPos, FarPos, Sp)) {
						ObjVec.push_back(PsPtr);
					}
				}
				else if (ColCapsule) {
					auto Cap = ColCapsule->GetCapsule();
					if (HitTest::SEGMENT_CAPSULE(NearPos, FarPos, Cap)) {
						ObjVec.push_back(PsPtr);
					}
				}
			}
		}
		if (ObjVec.size() > 0) {
			float MinSpan = 1000.0f;
			shared_ptr<ActivePsObject> SelectObj = nullptr;
			for (auto& v : ObjVec) {
				float Span = length(v->GetComponent<Transform>()->GetPosition() - Eye);
				if (Span < MinSpan) {
					MinSpan = Span;
					SelectObj = v;
				}
			}
			if (SelectObj) {
				SelectObj->SetSelected(true);
			}
		}
	}

	//マウスの左ボタン(離した)
	void GameStage::OnLButtonUp() {
		SelectClear();

	}

	//マウスの右ボタン(押した瞬間)
	void GameStage::OnRButtonEnter() {
		PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToTitleStage");
	}

	void GameStage::SetSoundPosition(Vec3 pos)
	{
		m_SoundPos = pos;
	}

	Vec3 GameStage::GetSoundPosition()
	{
		return m_SoundPos;
	}

}
//end basecross
