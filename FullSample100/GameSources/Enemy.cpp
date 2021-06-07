#include "stdafx.h"
#include "Project.h"

namespace basecross {
	Enemy1::Enemy1(const shared_ptr<Stage>& StagePtr,
		const Vec3& Scale,
		const Vec3& Rotation,
		const Vec3& Position
	) :
		GameObject(StagePtr),
		m_Scale(Scale),
		m_Rotation(Rotation),
		m_Position(Position),
		m_Mesh(L"SecurityRobot_Animation_0002.bmf"),
		m_Texture(L"Tx_SecurityRobot.png")
	{}
	Enemy1::~Enemy1() {}

	void Enemy1::OnCreate() {
		auto PtrTransform = GetComponent<Transform>();

		PtrTransform->SetScale(m_Scale);
		PtrTransform->SetRotation(m_Rotation);
		PtrTransform->SetPosition(m_Position);


		AddTag(L"Enemy1");

		auto PtrGra = AddComponent<Gravity>();

		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetMakedSize(1.0f);

		GetStage()->SetCollisionPerformanceActive(true);
		GetStage()->SetUpdatePerformanceActive(true);
		GetStage()->SetDrawPerformanceActive(true);


		Mat4x4 SpanMat; // モデルとトランスフォームの間の差分行列
		SpanMat.affineTransformation(
			Vec3(1.0f, 1.0f, 1.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f));

		//影をつける（シャドウマップを描画する）
		auto ShadowPtr = AddComponent<Shadowmap>();
		//影の形（メッシュ）を設定
		ShadowPtr->SetMeshResource(m_Mesh);
		ShadowPtr->SetMeshToTransformMatrix(SpanMat);

		//描画するメッシュを設定
		auto ptrDraw = AddComponent<BcPNTBoneModelDraw>();
		ptrDraw->SetDiffuse(Col4(1.0f, 1.0f, 1.0f, 1.0f));
		ptrDraw->SetFogEnabled(true);
		ptrDraw->SetOwnShadowActive(true);
		ptrDraw->SetMeshResource(m_Mesh);
		ptrDraw->SetTextureResource(m_Texture);

		ptrDraw->AddAnimation(L"Move", 25, 30, true, 25);
		ptrDraw->AddAnimation(L"Die",  51, 70, true, 6);

		ptrDraw->ChangeCurrentAnimation(L"Move");
		//ステートマシンの構築
		m_StateMachine.reset(new StateMachine<Enemy1>(GetThis<Enemy1>()));
		//最初のステートをSeekFarStateに設定
		m_StateMachine->ChangeState(SeekFarState::Instance());

	}

	void Enemy1::OnUpdate() {
		//ステートマシンのUpdateを行う
		//この中でステートの切り替えが行われる
		m_StateMachine->Update();
		auto ptrUtil = GetBehavior<UtilBehavior>();
		ptrUtil->RotToHead(1.0f);
		auto elapsedTime = App::GetApp()->GetElapsedTime();

		auto ptrDraw = GetComponent<BcPNTBoneModelDraw>();
		ptrDraw->UpdateAnimation(elapsedTime);

		if (m_SaveNum == 1)
		{
			m_DieTime += elapsedTime;
		}


		auto UpdateCheck = App::GetApp()->GetScene<Scene>()->GetUpdateBool();
		if (UpdateCheck == true) {
			SetUpdateActive(false);

		}
		if (m_DieTime > 1.0f)
		{
			SetUpdateActive(false);
			SetDrawActive(false);
			DeleteObject(this);
		}


	}

	void Enemy1::AnimeManager(int num)
	{
		auto ptrDraw = GetComponent<BcPNTBoneModelDraw>();

		if (m_SaveNum != num) {
			switch (num)
			{
			case 0:
				ptrDraw->ChangeCurrentAnimation(L"Move");
				break;
			case 1:
				ptrDraw->ChangeCurrentAnimation(L"Die");
				break;
			default:
				break;
			}
			m_SaveNum = num;
		}
	}

	void Enemy1::OnCollisionEnter(shared_ptr<GameObject>& Other) {
		if (Other->FindTag(L"SoundBox")) {
		m_StateMachine->ChangeState(SoundBoxState::Instance());
		}

		if (Other->FindTag(L"Enemy2")) {
			AnimeManager(1);
		}

	}
	void Enemy1::OnCollisionExit(shared_ptr<GameObject>& Other) {
		if (Other->FindTag(L"SoundBox")) {
			m_switch = 0;
		}
	}

	Vec3 Enemy1::GetTargetPos()const {
		auto ptrTarget = GetStage()->GetSharedObject(L"Player");
		return ptrTarget->GetComponent<Transform>()->GetPosition();
	}


	void Enemy1::ApplyForce() {
		auto pos = GetComponent<Transform>()->GetPosition();
		auto posxcount = m_SoundPos.x - pos.x;
		auto poszcount = m_SoundPos.z - pos.z;
		auto Pos = GetComponent<Transform>()->GetPosition();
		float ElapsedTime = App::GetApp()->GetElapsedTime();
		auto m_Speed = 1.0f;
		Pos += m_Angle * ElapsedTime * m_Speed;
		GetComponent<Transform>()->SetPosition(Pos);

		switch (m_switch) {
		case 0:
			if (m_SoundPos.x - Pos.x < -0.1f) {
				m_Angle = Vec3(-1.0f, 0.0f, 0.0f);
			}

			else if (m_SoundPos.x - Pos.x > 0.1f) {
				m_Angle = Vec3(1.0f, 0.0f, 0.0f);
			}

			else{
				m_Angle = Vec3(0.0f, 0.0f, 0.0f);

				m_switch = 1;
			}


			break;
		case 1:
			if (m_SoundPos.z - Pos.z > 0) {
				m_Angle = Vec3(0.0f, 0.0f, 1.0f);
			}
			else if (m_SoundPos.z - Pos.z < 0) {
				m_Angle = Vec3(0.0f, 0.0f, -1.0f);
			}
			break;

		}
		m_time += ElapsedTime;



		if (m_time > 3.0f) {
			m_StateMachine->ChangeState(SeekNearState::Instance());

		}
	}


	void Enemy1::ApplyForce2() {
	}





	//敵２
	Enemy2::Enemy2(const shared_ptr<Stage>& StagePtr,
		const Vec3& Scale,
		const Vec3& Rotation,
		const Vec3& Position
	) :
		GameObject(StagePtr),
		m_Scale(Scale),
		m_Rotation(Rotation),
		m_Position(Position),
		m_Mesh(L"Enemy_robot_4.bmf"),
		m_Texture(L"Tx_Enemy_robot_1.tga")
	{}
	Enemy2::~Enemy2() {}

	void Enemy2::OnCreate() {
		auto PtrTransform = GetComponent<Transform>();

		PtrTransform->SetScale(m_Scale);
		PtrTransform->SetRotation(m_Rotation);
		PtrTransform->SetPosition(m_Position);

		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetAfterCollision(AfterCollision::None);

		ptrColl->SetMakedSize(1.2f);


		GetStage()->SetCollisionPerformanceActive(true);
		GetStage()->SetUpdatePerformanceActive(true);
		GetStage()->SetDrawPerformanceActive(true);
		AddTag(L"Enemy2");

		vector<VertexPositionNormalTexture> vertices;
		vector<uint16_t> indices;
		MeshUtill::CreateCube(1.0f, vertices, indices);
		float UCount = m_Scale.x / m_UPic;
		float VCount = m_Scale.z / m_VPic;
		for (size_t i = 0; i < vertices.size(); i++) {
			if (vertices[i].textureCoordinate.x >= 1.0f) {
				vertices[i].textureCoordinate.x = UCount;
			}
			if (vertices[i].textureCoordinate.y >= 1.0f) {
				float FrontBetween = bsm::angleBetweenNormals(vertices[i].normal, Vec3(0, 1, 0));
				float BackBetween = bsm::angleBetweenNormals(vertices[i].normal, Vec3(0, -1, 0));
				if (FrontBetween < 0.01f || BackBetween < 0.01f) {
					vertices[i].textureCoordinate.y = VCount;
				}
			}
		}

		Mat4x4 SpanMat; // モデルとトランスフォームの間の差分行列
		SpanMat.affineTransformation(
			Vec3(1.0f, 1.0f, 1.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f));

		//影をつける（シャドウマップを描画する）
		auto ShadowPtr = AddComponent<Shadowmap>();
		//影の形（メッシュ）を設定
		ShadowPtr->SetMeshResource(m_Mesh);
		ShadowPtr->SetMeshToTransformMatrix(SpanMat);

		//描画するメッシュを設定
		auto ptrDraw = AddComponent <BcPNTBoneModelDraw> ();
		ptrDraw->SetDiffuse(Col4(1.0f, 1.0f, 1.0f, 1.0f));
		ptrDraw->SetFogEnabled(true);
		ptrDraw->SetOwnShadowActive(true);
		ptrDraw->SetMeshResource(m_Mesh);
		ptrDraw->SetTextureResource(m_Texture);
		ptrDraw->AddAnimation(L"Move", 0, 30, true, 25);
		ptrDraw->AddAnimation(L"Attack", 30, 70, true, 25);
		ptrDraw->ChangeCurrentAnimation(L"Move");

		auto CreateCheck = App::GetApp()->GetScene<Scene>()->GetStageNum();
		auto qt = GetComponent<Transform>()->GetQuaternion();

		switch (CreateCheck) {
		case 1:
			m_Angle = Vec3(1.0f, 0.0f, 0.0f);
			qt *= m_spanQtXm;
			GetComponent<Transform>()->SetQuaternion(qt);
			break;
		case 2:
			m_Angle = Vec3(-1.0f, 0.0f, 0.0f);
			m_spanQtXm = Quat(Vec3(0, 1.0, 0), 77.0f);
			qt *= m_spanQtXm;
			GetComponent<Transform>()->SetQuaternion(qt);

			break;
		case 3:
			m_Angle = Vec3(0.0f, 0.0f, -1.0f);
			break;

		}

	}

	void Enemy2::OnUpdate()
	{
		auto elapsedTime = App::GetApp()->GetElapsedTime();
		auto UpdateCheck= App::GetApp()->GetScene<Scene>()->GetUpdateBool();

		auto ptrDraw = GetComponent<BcPNTBoneModelDraw>();
		ptrDraw->UpdateAnimation(elapsedTime);
		m_time += elapsedTime;
		auto ptrUtil = GetBehavior<UtilBehavior>();
		ptrUtil->RotToHead(1.0f);
		auto Pos = GetComponent<Transform>()->GetPosition();
		float ElapsedTime = App::GetApp()->GetElapsedTime();
		auto m_Speed = 1.15f;
		Pos += m_Angle * ElapsedTime * m_Speed;
		GetComponent<Transform>()->SetPosition(Pos);
		if (m_time < 3.0f && m_MotionTime > 3.0f) {
			m_Angle = Vec3(0.0f, 0.0f, 0.0f);
			m_MotionTime = 0;
			App::GetApp()->GetScene<Scene>()->SetUpdateBool(true);
		}
		
		if (UpdateCheck == true) {
			SetUpdateActive(false);
		}

		if (m_SaveNum == 2)
		{
			AnimeManager(2);
			m_MotionTime += elapsedTime;
		}

		if (m_MoveCheck == 1) {
			a += elapsedTime;

			if (a >= 1.0f) {
				AnimeManager(0);
				m_Angle = m_AngleSave;
				a = 0;
				m_MoveCheck = 0;
			}
		}
	}

	void Enemy2::AnimeManager(int num)
	{
		auto ptrDraw = GetComponent<BcPNTBoneModelDraw>();

		if (m_SaveNum != num) {
			switch (num)
			{
			case 0:
				ptrDraw->ChangeCurrentAnimation(L"Move");
				break;
			case 1:
				ptrDraw->ChangeCurrentAnimation(L"Die");
				break;
			case 2:
				ptrDraw->ChangeCurrentAnimation(L"Attack");
				break;
			default:
				break;
			}
			m_SaveNum = num;
		}
	}

	void Enemy2::OnCollisionEnter(shared_ptr<GameObject>& other)
	{
		if (other->FindTag(L"CheckPointBox")) {
			auto csvSet = App::GetApp()->GetScene<Scene>()->GetStageNum();

			switch (csvSet) {
			case 1:
				if (m_CheckPointCount == 0) {

					m_Angle = Vec3(0.0f, 0.0f, -1.0f);
					m_CheckPointCount = 1;

					Quat spanQtXm(Vec3(0, 1.0, 0), -77.0f);
					auto qt = GetComponent<Transform>()->GetQuaternion();
					qt *= spanQtXm;
					GetComponent<Transform>()->SetQuaternion(qt);

				}
				else if (m_CheckPointCount == 1) {
					m_Angle = Vec3(1.0f, 0.0f, 0.0f);
					Quat spanQtXm(Vec3(0, 1.0, 0), 77.0f);
					auto qt = GetComponent<Transform>()->GetQuaternion();
					qt *= spanQtXm;
					GetComponent<Transform>()->SetQuaternion(qt);

				}
				break;

			case 2:

				if (m_CheckPointCount == 0) {

					m_Angle = Vec3(-1.0f, 0.0f, 0.0f);
					m_CheckPointCount = 1;

					Quat spanQtXm(Vec3(0, 1.0, 0), -77.0f);
					auto qt = GetComponent<Transform>()->GetQuaternion();
					qt *= spanQtXm;
					GetComponent<Transform>()->SetQuaternion(qt);

				}
				else if (m_CheckPointCount == 1) {
					m_Angle = Vec3(0.0f, 0.0f, 1.0f);
					Quat spanQtXm(Vec3(0, 1.0, 0), 77.0f);
					auto qt = GetComponent<Transform>()->GetQuaternion();
					qt *= spanQtXm;
					GetComponent<Transform>()->SetQuaternion(qt);

				}
				break;

			}
		}

		if (other->FindTag(L"Enemy1"))
		{	
			m_AngleSave = m_Angle;
			m_Angle = Vec3(0.0f, 0.0f, 0.0f);
			m_MoveCheck = 1;

			AnimeManager(2);
			//m_time = 0;
		}

		if (other->FindTag(L"Player"))
		{
			AnimeManager(2);
		}
	}


//--------------------------------------------------------------------------------------
//	プレイヤーから遠いときの移動
//--------------------------------------------------------------------------------------
	shared_ptr<SeekFarState> SeekFarState::Instance() {
		static shared_ptr<SeekFarState> instance(new SeekFarState);
		return instance;
	}
	void SeekFarState::Enter(const shared_ptr<Enemy1>& Obj) {
	}
	void SeekFarState::Execute(const shared_ptr<Enemy1>& Obj) {
	}

	void SeekFarState::Exit(const shared_ptr<Enemy1>& Obj) {
	}

	//--------------------------------------------------------------------------------------
	//	プレイヤーから近いときの移動
	//--------------------------------------------------------------------------------------
	shared_ptr<SeekNearState> SeekNearState::Instance() {
		static shared_ptr<SeekNearState> instance(new SeekNearState);
		return instance;
	}
	void SeekNearState::Enter(const shared_ptr<Enemy1>& Obj) {
	}
	void SeekNearState::Execute(const shared_ptr<Enemy1>& Obj) { 
	}
	void SeekNearState::Exit(const shared_ptr<Enemy1>& Obj) {
	}



	shared_ptr<SoundBoxState> SoundBoxState::Instance() {
		static shared_ptr<SoundBoxState> instance(new SoundBoxState);
		return instance;
	}
	void SoundBoxState::Enter(const shared_ptr<Enemy1>& Obj) {
	}
	void SoundBoxState::Execute(const shared_ptr<Enemy1>& Obj) {
		auto pos = App::GetApp()->GetScene<Scene>()->GetSoundPosition();
		Obj->SetPosition(pos);
		Obj->ApplyForce();
	}
	void SoundBoxState::Exit(const shared_ptr<Enemy1>& Obj) {
		Obj->SetTimer();

	}


	Playerdummy::Playerdummy(const shared_ptr<Stage>& StagePtr,
		const Vec3& Scale,
		const Vec3& Rotation,
		const Vec3& Position
	): GameObject(StagePtr),
		m_Scale(Scale),
		m_Rotation(Rotation),
		m_Position(Position),
		m_Mesh(L"Protagonist_Robot_5.bmf")
	{
	}

	Playerdummy::~Playerdummy()
	{
	}

	void Playerdummy::OnCreate()
	{
		//初期位置などの設定
		auto PtrTrans = GetComponent<Transform>();
		PtrTrans->SetScale(m_Scale);
		PtrTrans->SetRotation(m_Rotation);
		PtrTrans->SetPosition(m_Position);


		//CollisionObb衝突判定を付ける
		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetAfterCollision(AfterCollision::None);

		ptrColl->SetMakedSize(1.2f);

		GetStage()->SetCollisionPerformanceActive(true);
		GetStage()->SetUpdatePerformanceActive(true);
		GetStage()->SetDrawPerformanceActive(true);

		Mat4x4 SpanMat; // モデルとトランスフォームの間の差分行列
		SpanMat.affineTransformation(
			Vec3(1.0f, 1.0f, 1.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f));

		//影をつける（シャドウマップを描画する）
		auto ShadowPtr = AddComponent<Shadowmap>();
		//影の形（メッシュ）を設定
		ShadowPtr->SetMeshResource(m_Mesh);
		ShadowPtr->SetMeshToTransformMatrix(SpanMat);
		AddTag(L"Player");

		//描画コンポーネントの設定
		auto ptrDraw = AddComponent<BcPNTBoneModelDraw>();
		//描画するメッシュを設定
		ptrDraw->SetMeshResource(m_Mesh);
		ptrDraw->SetOwnShadowActive(true);
		ptrDraw->AddAnimation(L"Move", 0, 20, true, 25);
		ptrDraw->AddAnimation(L"Die", 20, 40, true, 25);
		m_CheckPointCount = 0;

		////描画するテクスチャを設定
		ptrDraw->SetTextureResource(L"Tx_Protagonist_Robot_2.tga");


		auto CreateCheck = App::GetApp()->GetScene<Scene>()->GetStageNum();
		auto qt = GetComponent<Transform>()->GetQuaternion();

		switch (CreateCheck) {
		case 1:
			m_Angle = Vec3(1.0f, 0.0f, 0.0f);
			qt *= m_spanQtXm;
			GetComponent<Transform>()->SetQuaternion(qt);
			break;
		case 2:
			m_Angle = Vec3(0.0f, 0.0f, 1.0f);
			m_spanQtXm=Quat(Vec3(0, 1.0, 0), 154.0f);
			qt *= m_spanQtXm;
			GetComponent<Transform>()->SetQuaternion(qt);

			break;
		case 3:
			m_Angle = Vec3(0.0f, 0.0f, -1.0f);
			break;
		}
	}
	void Playerdummy::OnUpdate() {
		auto elapsedTime = App::GetApp()->GetElapsedTime();

		auto ptrDraw = GetComponent<BcPNTBoneModelDraw>();
		ptrDraw->UpdateAnimation(elapsedTime);

		auto Pos = GetComponent<Transform>()->GetPosition();
		float ElapsedTime = App::GetApp()->GetElapsedTime();
		auto m_Speed = 1.0f;
		Pos += m_Angle * ElapsedTime * m_Speed;
		GetComponent<Transform>()->SetPosition(Pos);

		if (m_SaveNum == 1)
		{
			m_MotionTime += elapsedTime;
		}

		if (m_MotionTime > 0.9f)
		{
			App::GetApp()->GetScene<Scene>()->SetCheck(1);
			SetUpdateActive(false);
		}
	}
	void Playerdummy::AnimeManager(int num)
	{
		auto ptrDraw = GetComponent<BcPNTBoneModelDraw>();

		if (m_SaveNum != num) {
			switch (num)
			{
			case 0:
				ptrDraw->ChangeCurrentAnimation(L"Move");
				break;
			case 1:
				ptrDraw->ChangeCurrentAnimation(L"Die");
				break;
			default:
				break;
			}
			m_SaveNum = num;
		}
	}

	void Playerdummy::OnCollisionEnter(shared_ptr<GameObject>& other)
	{
		auto elapsedTime = App::GetApp()->GetElapsedTime();
		if (other->FindTag(L"CheckPointBox")) {
			auto csvSet = App::GetApp()->GetScene<Scene>()->GetStageNum();

			switch (csvSet) {
			case 1:
				if (m_CheckPointCount == 0) {

					m_Angle = Vec3(0.0f, 0.0f, -1.0f);
					m_CheckPointCount = 1;

					Quat spanQtXm(Vec3(0, 1.0, 0), -77.0f);
					auto qt = GetComponent<Transform>()->GetQuaternion();
					qt *= spanQtXm;
					GetComponent<Transform>()->SetQuaternion(qt);

				}
				else if (m_CheckPointCount == 1) {
					m_Angle = Vec3(1.0f, 0.0f, 0.0f);
					Quat spanQtXm(Vec3(0, 1.0, 0), 77.0f);
					auto qt = GetComponent<Transform>()->GetQuaternion();
					qt *= spanQtXm;
					GetComponent<Transform>()->SetQuaternion(qt);

				}
				break;

			case 2:

				if (m_CheckPointCount == 0) {

					m_Angle = Vec3(-1.0f, 0.0f, 0.0f);
					m_CheckPointCount = 1;

					Quat spanQtXm(Vec3(0, 1.0, 0), -77.0f);
					auto qt = GetComponent<Transform>()->GetQuaternion();
					qt *= spanQtXm;
					GetComponent<Transform>()->SetQuaternion(qt);

				}
				else if (m_CheckPointCount == 1) {
					m_Angle = Vec3(0.0f, 0.0f, 1.0f);
					Quat spanQtXm(Vec3(0, 1.0, 0), 77.0f);
					auto qt = GetComponent<Transform>()->GetQuaternion();
					qt *= spanQtXm;
					GetComponent<Transform>()->SetQuaternion(qt);

				}
				break;

			}
		}
		if (other->FindTag(L"Goal"))
		{
			App::GetApp()->GetScene<Scene>()->SetCheck(0);
			
			auto ptrColl = GetComponent<CollisionObb>();
			ptrColl->AddExcludeCollisionGameObject(other);
			
			App::GetApp()->GetScene<Scene>()->SetUpdateBool(true);

			SetUpdateActive(false);
		}
		if (other->FindTag(L"Enemy1"))
		{
			App::GetApp()->GetScene<Scene>()->SetUpdateBool(true);

			AnimeManager(1);
		}
		if (other->FindTag(L"Enemy2"))
		{
			AnimeManager(1);
		}

	}
}
//end basecross
