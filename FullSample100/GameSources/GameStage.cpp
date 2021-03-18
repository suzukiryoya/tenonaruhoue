/*!
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
		const Vec3 eye(0.0f, 30.0f, -10.0f);
		const Vec3 at(0.0f);
		auto PtrView = CreateView<SingleView>();
		//ビューのカメラの設定
		auto PtrCamera = ObjectFactory::Create<Camera>();
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

		vector<wstring> LineVec1;
		vector<wstring> LineVec2;


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
			BoxesGroup->IntoGroup(wall);
		}
	}

	void GameStage::CreatePlayer()
	{
		AddGameObject<Player>(Vec3(1), Vec3(0), Vec3(1.0f,1.0f,0));
	}

	void GameStage::CreateCellMap() {
		float PieceSize = 1.0f;
		auto Ptr = AddGameObject<StageCellMap>(Vec3(-15.5f, 0.0f, -15.5f), PieceSize, 31, 31);
		Ptr->SetDrawActive(false);
		SetSharedGameObject(L"StageCellMap", Ptr);
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
			wstring MediaDir;
			App::GetApp()->GetDataDirectory(MediaDir);
			AddGameObject<FixedBox>(Vec3(1.0f),Vec3(0.0f),Vec3(0.0f,1.0f,0.0f));
			m_GameStageCsv.SetFileName(MediaDir + L"Stage0.csv");
			m_GameStageCsv.ReadCsv();
			//ビューとライトの作成
			CreateViewLight();
			CreateStage();
			CreatePlayer();
			wstring dataDir;
			//サンプルのためアセットディレクトリを取得
			App::GetApp()->GetAssetsDirectory(dataDir);
			wstring strMovie = dataDir + L"cursor.png";
			AddGameObject<Clear>(
					Vec2(512.0f, 512.0f),
					Vec3(0.0f, 200.0f, 0.0f),
					Vec3(0.5f),
					10,
					Col4(1.0f),
				    m_StageSelect_image
				);
		}
		catch (...) {
			throw;
		}
	}

}
//end basecross
