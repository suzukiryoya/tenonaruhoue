/*!
@file Player.cpp
@brief プレイヤーなど実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{
	Player::Player(const shared_ptr<Stage>& StagePtr,
		const Vec3& Scale,
		const Vec3& Rotation,
		const Vec3& Position,
		const shared_ptr<StageCellMap>& CellMap
		)
		: GameObject(StagePtr), m_Speed(25.0f), m_GoPointPos(-10.0f, 2.0f, 14.0f), m_Scale(Scale), m_Rotation(Rotation), m_Position(Position),
		m_CelMap(CellMap),
		m_StartPosition(Position),
		m_Force(0),
		m_Mesh(L"Protagonist_Robot_4.bmf")
	{
	}

	Player::~Player()
	{
	}

	void Player::OnCreate()
	{
		//初期位置などの設定
		auto PtrTrans = GetComponent<Transform>();
		PtrTrans->SetScale(m_Scale);
		PtrTrans->SetRotation(m_Rotation);
		PtrTrans->SetPosition(m_Position);

		//m_NowPosX = m_Position.x;
		m_NowPosZ = m_Position.z;

		//CollisionObb衝突判定を付ける
		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetAfterCollision(AfterCollision::None);
		auto MapPtr = m_CelMap.lock();
		if (MapPtr) {
			AddComponent<PathSearch>(MapPtr);
		}

		ptrColl->SetMakedSize(1.5f);

		GetStage()->SetCollisionPerformanceActive(true);
		GetStage()->SetUpdatePerformanceActive(true);
		GetStage()->SetDrawPerformanceActive(true);

		Mat4x4 SpanMat; // モデルとトランスフォームの間の差分行列
		SpanMat.affineTransformation(
			Vec3(1.0f, 1.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f));

		//影をつける（シャドウマップを描画する）
		auto ShadowPtr = AddComponent<Shadowmap>();
		//影の形（メッシュ）を設定
		ShadowPtr->SetMeshResource(m_Mesh);
		ShadowPtr->SetMeshToTransformMatrix(SpanMat);

		////文字列をつける
		//auto ptrString = AddComponent<StringSprite>();
		//ptrString->SetText(L"");
		//ptrString->SetTextRect(Rect2D<float>(16.0f, 16.0f, 640.0f, 480.0f));

		//描画コンポーネントの設定
		auto ptrDraw = AddComponent<BcPNTBoneModelDraw>();
		ptrDraw->SetFogEnabled(true);
		//描画するメッシュを設定
		ptrDraw->SetMeshResource(m_Mesh);
		ptrDraw->SetOwnShadowActive(true);

		////描画するテクスチャを設定
		ptrDraw->SetTextureResource(L"Tx_Protagonist_Robot_2.tga");

		//カメラを得る
		auto ptrCamera = dynamic_pointer_cast<Camera>(OnGetDrawCamera());
		if (ptrCamera) {
			//MyCameraである
			//MyCameraに注目するオブジェクト（プレイヤー）の設定
			//ptrCamera->SetTargetObject(GetThis<GameObject>());
			//ptrCamera->SetTargetToAt(GetComponent<Transform>()->GetPosition());
		}
	}

	void Player::OnUpdate()
	{
		auto trans = GetComponent<Transform>();
		auto newPos = trans->GetPosition();

		auto controller = App::GetApp()->GetInputDevice().GetControlerVec();
		if (controller[0].wPressedButtons & XINPUT_GAMEPAD_A)
		{
			SoundBoxSearch();
		}

		playerMove(m_HomingFlag, m_Speed);
	}

	void Player::playerMove(bool flag, float speed)
	{
		if (SeekBehavior(m_GoPointPos) == CellSearchFlg::Failed) {
			if (SeekBehavior(GetStartPosition()) == CellSearchFlg::Arrived) {
				ArriveBehavior(GetStartPosition());
			}
		}
		float ElapsedTime = App::GetApp()->GetElapsedTime();
		auto pos = GetComponent<Transform>()->GetPosition();
		//auto GoPointToNowPos = Vec3(0.0f, 2.0f, 0.0f);
		auto trans = GetComponent<Transform>();
		auto elapsedTime = App::GetApp()->GetElapsedTime();
		//if (length(pos - m_GoPointPos) <= 1.8f) {
		//	m_Velocity *= 0.95f;
		//}

		if (flag == true) // 左方向に移動するとき
		{
			m_Velocity -= speed * ElapsedTime;
			m_Position -= m_Velocity * ElapsedTime;


			////GoPointToNowPos.y = -XM_PI;
			//m_Rotation.y += GoPointToNowPos.y;

			//GoPointToNowPos.normalize();

			//m_Speed += 1.0f;

			trans->SetRotation(0, m_Rotation.y, 0);

			trans->SetPosition(m_Position.x, 2.0f, m_NowPosZ);

			m_Speed = 0;
		}
		else // 右方向に移動するとき
		{
			m_Velocity += speed * ElapsedTime;
			m_Position += m_Velocity * ElapsedTime;

			//GoPointToNowPos.x = m_Position.x + m_GoPointPos.x;
			//GoPointToNowPos.z = m_Position.z + m_GoPointPos.z;

			//GoPointToNowPos.normalize();

			//m_Position -= GoPointToNowPos * elapsedTime * m_Speed;


			trans->SetRotation(0, m_Rotation.y, 0);

			trans->SetPosition(m_Position.x, 2.0f, m_NowPosZ);

			m_Speed = 0;
		}
	}

	void Player::SoundBoxSearch()
	{
		auto& app = App::GetApp();
		auto scene = app->GetScene<Scene>();
		auto stage = scene->GetActiveStage();
		auto gameObjects = stage->GetChileStageVec();
		auto elapsedTime = App::GetApp()->GetElapsedTime();
		auto GoPointToNowPos = Vec3(0.0f, 2.0f, 0.0f);

		auto soundPosition = scene->GetPosition();

		m_GoPointPos = soundPosition;
		//m_Position = GetComponent<Transform>()->GetPosition();

		//GoPointToNowPos.x = m_Position.x - m_GoPointPos.x;
		GoPointToNowPos.z = m_Position.z - m_GoPointPos.z;

		GoPointToNowPos.normalize();

		if (GoPointToNowPos.length() <= 6.0f)
		{
			//m_Position.x = GoPointToNowPos.x * elapsedTime * m_Speed;
			m_Position.z += GoPointToNowPos.z * elapsedTime;

			m_Position.normalize();

			m_NowPosZ += m_Position.z += GoPointToNowPos.z * elapsedTime;
		}
		
		//if(m_NowPosZ == )
		//{
		//	return;
		//}
	}

	void Player::OnCollisionEnter(shared_ptr<GameObject>& other)
	{
		auto trans = GetComponent<Transform>();
		float elapsedTime = App::GetApp()->GetElapsedTime();

		if (other->FindTag(L"Wall") || other->FindTag(L"Enemy1") || other->FindTag(L"Enemy2"))
		{
			m_GoPointPos = other->GetComponent<Transform>()->GetPosition();
			m_Rotation.y += XM_PI;
			trans->SetRotation(m_Rotation);

			auto GoPointToNowPos = Vec3(0.0f, 2.0f, 0.0f);
			GoPointToNowPos.x -= m_Position.x + m_GoPointPos.x;

			GoPointToNowPos.normalize();

			m_Position += GoPointToNowPos * elapsedTime;
			
			if (m_HomingFlag == true)
			{
				m_HomingFlag = false;
			}
			else
			{
				m_HomingFlag = true;
			}
		}
		if (other->FindTag(L"SoundBox"))
		{
			auto pos = trans->GetPosition();

			m_GoPointPos = other->GetComponent<Transform>()->GetPosition();

			auto GoPointToNowPos = Vec3(0.0f, 2.0f, 0.0f);
			GoPointToNowPos.x -= m_Position.x + m_GoPointPos.x;
			GoPointToNowPos.z -= m_Position.z + m_GoPointPos.z;

			//m_Rotation.y += XM_PI;
			//trans->SetRotation(m_Rotation);

			GoPointToNowPos.normalize();

			//m_Speed += 1.0f;

			if (GoPointToNowPos.length() <= 6.0f)
			{
				m_Position.x += GoPointToNowPos.x * elapsedTime;
				m_Position.z += GoPointToNowPos.z * elapsedTime;

				m_Position.normalize();

				m_Position += GoPointToNowPos * elapsedTime;
				m_NowPosZ += m_Position.z * elapsedTime;
			}
		}
		if (other->FindTag(L"Goal"))
		{
			App::GetApp()->GetScene<Scene>()->SetCheck(true);
		}
	}

	bool Player::Search(const Vec3& TargetPos) {
		auto MapPtr = m_CelMap.lock();
		if (MapPtr) {
			auto PathPtr = GetComponent<PathSearch>();
			m_CellPath.clear();
			//パス検索をかける
			if (PathPtr->SearchCell(TargetPos, m_CellPath)) {
				//検索が成功した
				m_CellIndex = 0;
				m_TargetCellIndex = (int)(m_CellPath.size() - 1);
				if (m_CellIndex == m_TargetCellIndex) {
					//すでに同じセルにいる
					m_NextCellIndex = m_CellIndex;
				}
				else {
					//離れている
					m_NextCellIndex = m_CellIndex + 1;

				}
				return true;
			}
			else {
				//失敗した
				m_CellIndex = -1;
				m_NextCellIndex = -1;
				m_TargetCellIndex = -1;
			}
		}
		return false;
	}

	CellSearchFlg Player::SeekBehavior(const Vec3& TargetPos) {
		auto MyPos = GetComponent<Transform>()->GetPosition();
		auto MapPtr = m_CelMap.lock();
		if (!MapPtr) {
			return CellSearchFlg::Failed;
		}
		if (Search(TargetPos)) {
			auto PtrSeek = GetBehavior<SeekSteering>();
			auto PtrArrive = GetBehavior<ArriveSteering>();
			if (m_NextCellIndex == 0) {
				m_Force = PtrArrive->Execute(m_Force, m_Velocity, TargetPos);
				//到着した
				return CellSearchFlg::Arrived;
			}
			else {
				AABB ret;
				MapPtr->FindAABB(m_CellPath[m_NextCellIndex], ret);
				auto Pos = ret.GetCenter();
				Pos.y = TargetPos.y;
				m_Force = PtrSeek->Execute(m_Force, m_Velocity, Pos);
				return CellSearchFlg::Seek;
			}
		}
		else {
			auto PtrSeek = GetBehavior<SeekSteering>();
			CellIndex PlayerCell;
			if (MapPtr->FindCell(TargetPos, PlayerCell)) {
				AABB ret;
				MapPtr->FindAABB(PlayerCell, ret);
				auto Pos = ret.GetCenter();
				Pos.y = TargetPos.y;
				m_Force = PtrSeek->Execute(m_Force, m_Velocity, Pos);
				return CellSearchFlg::Seek;
			}
		}
		return CellSearchFlg::Failed;
	}

	void Player::ArriveBehavior(const Vec3& TargetPos) {
		auto PtrArrive = GetBehavior<ArriveSteering>();
		m_Force = PtrArrive->Execute(m_Force, m_Velocity, TargetPos);
	}
}
//end basecross

