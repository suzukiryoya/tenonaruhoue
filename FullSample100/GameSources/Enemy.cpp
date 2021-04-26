#include "stdafx.h"
#include "Project.h"

namespace basecross {
	Enemy1::Enemy1(const shared_ptr<Stage>& StagePtr,
		const Vec3& Scale,
		const Vec3& Rotation,
		const Vec3& Position
		//float UPic,
		//float VPic
	) :
		GameObject(StagePtr),
		m_Scale(Scale),
		m_Rotation(Rotation),
		m_Position(Position),
		m_Mesh(L"SecurityRobot_Animation_0001.bmf"),
		m_Texture(L"Tx_SecurityRobot.png")
	{}
	Enemy1::~Enemy1() {}

	void Enemy1::OnCreate() {
		auto PtrTransform = GetComponent<Transform>();

		PtrTransform->SetScale(m_Scale);
		PtrTransform->SetRotation(m_Rotation);
		PtrTransform->SetPosition(m_Position);

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
		//ptrDraw->SetMeshToTransformMatrix(SpanMat);
		ptrDraw->SetTextureResource(m_Texture);
		//ptrDraw->AddAnimation(L"Default", 0, 0, true, 1);

		ptrDraw->AddAnimation(L"Move", 25, 50, true, 25);
		ptrDraw->AddAnimation(L"Attack", 25, 50, true, 25);

		ptrDraw->ChangeCurrentAnimation(L"Move");
		//ステートマシンの構築
		m_StateMachine.reset(new StateMachine<Enemy1>(GetThis<Enemy1>()));
		//最初のステートをSeekFarStateに設定
		m_StateMachine->ChangeState(SeekFarState::Instance());

	}

	void Enemy1::OnUpdate() {
		//m_Force = Vec3(0);
		//ステートマシンのUpdateを行う
		//この中でステートの切り替えが行われる
		m_StateMachine->Update();
		auto ptrUtil = GetBehavior<UtilBehavior>();
		ptrUtil->RotToHead(1.0f);
		auto elapsedTime = App::GetApp()->GetElapsedTime();

		auto ptrDraw = GetComponent<BcPNTBoneModelDraw>();
		ptrDraw->UpdateAnimation(elapsedTime);
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



		if (m_time >= 1.0f) {
			m_StateMachine->ChangeState(SeekNearState::Instance());

		}


		
		//auto PtrAction = AddComponent<Action>();
		////PtrAction->AllActionClear();


		//if (posxcount < 0)
		//{
		//	posxcount = -1 * posxcount;
		//}
		//if (poszcount < 0)
		//{
		//	poszcount = -1 * poszcount;
		//}

		//PtrAction->AddMoveTo(posxcount, Vec3(m_SoundPos.x,pos.y,pos.z));
		////PtrAction->AddMoveTo(poszcount, Vec3(m_SoundPos.x, pos.y, m_SoundPos.z));
		////ループする
		//PtrAction->SetLooped(false);
		////アクション開始
		//if (PtrAction->IsArrived()) {
		//	PtrAction->Stop();
		//	PtrAction->AllActionClear();

		//}

		//PtrAction->Run();

		//PtrAction->ReStart();




	}


	void Enemy1::ApplyForce2() {


	}





	//敵２
	Enemy2::Enemy2(const shared_ptr<Stage>& StagePtr,
		const Vec3& Scale,
		const Vec3& Rotation,
		const Vec3& Position,
		float UPic,
		float VPic
	) :
		GameObject(StagePtr),
		m_Scale(Scale),
		m_Rotation(Rotation),
		m_Position(Position),
		m_UPic(UPic),
		m_VPic(VPic),
		m_Mesh(L"Enemy_robot_4.bmf"),
		m_Texture(L"Tx_Enemy_robot_1.tga")
	{}
	Enemy2::~Enemy2() {}

	void Enemy2::OnCreate() {
		auto PtrTransform = GetComponent<Transform>();

		PtrTransform->SetScale(m_Scale);
		PtrTransform->SetRotation(m_Rotation);
		PtrTransform->SetPosition(m_Position);

		auto PtrGra = AddComponent<Gravity>();

		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetMakedSize(1.0f);

		GetStage()->SetCollisionPerformanceActive(true);
		GetStage()->SetUpdatePerformanceActive(true);
		GetStage()->SetDrawPerformanceActive(true);

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
		//ptrDraw->AddAnimation(L"Default", 0, 25, true, 1.0f);

		ptrDraw->ChangeCurrentAnimation(L"Move");
		//ptrDraw->SetMeshToTransformMatrix(SpanMat);
	}

	void Enemy2::OnUpdate()
	{
		auto elapsedTime = App::GetApp()->GetElapsedTime();

		auto ptrDraw = GetComponent<BcPNTBoneModelDraw>();
		ptrDraw->UpdateAnimation(elapsedTime);
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
			default:
				break;
			}
			m_SaveNum = num;
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
		//auto ptrSeek = Obj->GetBehavior<SeekSteering>();
		//auto ptrSep = Obj->GetBehavior<SeparationSteering>();
		//auto force = Obj->GetForce();
		//force = ptrSeek->Execute(force, Obj->GetVelocity(), Obj->GetTargetPos());
		//force += ptrSep->Execute(force);
		//Obj->SetForce(force);
		//Obj->ApplyForce();
		//float f = bsm::length(Obj->GetComponent<Transform>()->GetPosition() - Obj->GetTargetPos());
		//if (f < Obj->GetStateChangeSize()) {
		//	Obj->GetStateMachine()->ChangeState(SeekNearState::Instance());
		//}
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
		//auto ptrArrive = Obj->GetBehavior<ArriveSteering>();
		//auto ptrSep = Obj->GetBehavior<SeparationSteering>();
		//auto force = Obj->GetForce();
		//force = ptrArrive->Execute(force, Obj->GetVelocity(), Obj->GetTargetPos());
		//force += ptrSep->Execute(force);
		//Obj->SetForce(force);
		//Obj->ApplyForce();
		//float f = bsm::length(Obj->GetComponent<Transform>()->GetPosition() - Obj->GetTargetPos());
		//if (f >= Obj->GetStateChangeSize()) {
		//	Obj->GetStateMachine()->ChangeState(SeekFarState::Instance());
		//}
	}
	void SeekNearState::Exit(const shared_ptr<Enemy1>& Obj) {
	}



	shared_ptr<SoundBoxState> SoundBoxState::Instance() {
		static shared_ptr<SoundBoxState> instance(new SoundBoxState);
		return instance;
	}
	void SoundBoxState::Enter(const shared_ptr<Enemy1>& Obj) {
		//Obj->ApplyForce2();

		//Obj->GetStateMachine()->ChangeState(SeekFarState::Instance());

	}
	void SoundBoxState::Execute(const shared_ptr<Enemy1>& Obj) {
		//float elapsedTime = App::GetApp()->GetElapsedTime();
		//float time = 0;
		//time += elapsedTime;



		//if (time >= Obj->GetCount()) {
		//	Obj->ActionClear();
		//}
		auto pos = App::GetApp()->GetScene<Scene>()->GetSoundPosition();
		Obj->SetPosition(pos);
		Obj->ApplyForce();


	}
	void SoundBoxState::Exit(const shared_ptr<Enemy1>& Obj) {
		//Obj->ApplyForce2();
		Obj->SetTimer();

	}

}
//end basecross
