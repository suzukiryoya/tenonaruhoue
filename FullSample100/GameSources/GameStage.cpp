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
		const Vec3 eye(0.0f, 40.0f, -5.0f);
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
		vector<wstring> LineVec3;
		vector<wstring> LineVec4;
		vector<wstring> LineVec5;

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
			wall->AddTag(L"Wall");
			BoxesGroup->IntoGroup(wall);
		}

		//m_GameStageCsv.GetSelect(LineVec3, 0, L"Enemy1");
		//for (auto& v : LineVec3)
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

		//	auto enemy1 = AddGameObject<Enemy1>(Scale, Rot, Pos, 1.0f, 1.0f);
		//	enemy1->AddTag(L"Enemy1");
		//	BoxesGroup->IntoGroup(enemy1);
		//}

		//m_GameStageCsv.111GetSelect(LineVec4, 0, L"Enemy2");
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

		//	auto enemy2 = AddGameObject<Enemy2>(Scale, Rot, Pos, 1.0f, 1.0f);
		//	enemy2->AddTag(L"Enemy2");
		//	BoxesGroup->IntoGroup(enemy2);
		//}

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
	}

	void GameStage::CreatePlayer()
	{
		auto player =  AddGameObject<Player>(Vec3(1.0f), Vec3(0, XM_PIDIV2,0), Vec3(-14.0f,2.0f,5.0f));
		player->AddTag(L"Player");

	}

	void GameStage::CreateCellMap() {
		float PieceSize = 1.0f;

		auto Ptr = AddGameObject<StageCellMap>(Vec3(-15.5f, 1.0f, -15.5f), PieceSize, 30, 30);
		Ptr->SetDrawActive(true);
		SetSharedGameObject(L"StageCellMap", Ptr);
		//SetCellMapCost();
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
			//物理計算有効
			SetPhysicsActive(true);

			wstring MediaDir;
			App::GetApp()->GetDataDirectory(MediaDir);

			AddGameObject<FixedBox>(Vec3(1.0f),Vec3(0.0f),Vec3(0.0f,3.0f,0.0f));
			AddGameObject<Kakuninn>(Vec3(1.0f), Vec3(0.0f), Vec3(0.0f, 3.0f, 0.0f));
			AddGameObject<ActivePsBox>(Vec3(1.0f), Vec3(0.0f), Vec3(0.0f, 3.0f, 0.0f));


			m_GameStageCsv.SetFileName(MediaDir + L"Stage1_1.csv");
			m_GameStageCsv.ReadCsv();
			//ビューとライトの作成
			CreateViewLight();
			CreateStage();
			CreatePlayer();
			CreateCellMap();
			wstring dataDir;
			//サンプルのためアセットディレクトリを取得
			App::GetApp()->GetAssetsDirectory(dataDir);
			wstring strMovie = dataDir + L"cursor.png";
			AddGameObject<Clear>(
					Vec2(512.0f, 512.0f),
					Vec3(0.0f, 200.0f, 0.0f),
					Vec3(0.2f),
					10,
					Col4(1.0f),
				    m_StageSelect_image
				);
		}
		catch (...) {
			throw;
		}
	}

	void GameStage::OnUpdate()
	{
		//キーボード（マウス）の取得
		auto KeyState = App::GetApp()->GetInputDevice().GetKeyState();
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		auto CursorPos = App::GetApp()->GetScene<Scene>()->GetAngle();

		m_MousePoint = KeyState.m_MouseClientPoint;
		if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A) {
			OnLButtonEnter();
		}
		else if (KeyState.m_bUpKeyTbl[VK_LBUTTON]) {
			OnLButtonUp();
		}
		else if (KeyState.m_bPressedKeyTbl[VK_RBUTTON]) {
			OnRButtonEnter();
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
						auto a=Obb.m_Center;
						ObjVec.push_back(PsPtr);
						AddGameObject<TriggerBox>(Vec3(3.0f), Vec3(0.0f), Vec3(a.x, 1.0f, a.z));

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



}
//end basecross
