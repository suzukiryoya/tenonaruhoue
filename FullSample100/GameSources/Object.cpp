/*!
@file Character.cpp
@brief キャラクターなど実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

    //--------------------------------------------------------------------------------------
///	物理計算するアクティブなオブジェクトの親
//--------------------------------------------------------------------------------------
    void ActivePsObject::OnUpdate() {
        if (!IsSelected()) {
            return;
        }
        Vec3 Near, Far;
        GetTypeStage<GameStage>()->GetMouseRay(Near, Far);
        auto PsPtr = GetDynamicComponent<RigidbodySingle>(false);
        if (PsPtr) {
            auto PsPos = PsPtr->GetPosition();
            float t;
            Vec3 RayPos;
            //現在位置と一番近いレイ上の点を得る
            HitTest::ClosetPtPointSegment(PsPos, Near, Far, t, RayPos);
            Vec3 ToVec = RayPos - PsPos;
            ToVec *= 2.0f;
            PsPtr->WakeUp();
            PsPtr->SetLinearVelocity(ToVec);
        }
    }




    FixedBox::FixedBox(const shared_ptr<Stage>& StagePtr,
        const Vec3& Scale,
        const Vec3& Rotation,
        const Vec3& Position
    ) :
        ActivePsObject(StagePtr),
        m_Scale(Scale),
        m_Rotation(Rotation),
        m_Position(Position),
        m_Texture(L"Tx_SoundingBlock.png"),
        m_Mesh(L"SoundingBlock01.bmf")
    {
    }
    FixedBox::~FixedBox() {}

	void FixedBox::OnCreate() {
        auto PtrTransform = GetComponent<Transform>();
        PtrTransform->SetScale(m_Scale);
        PtrTransform->SetRotation(m_Rotation);
        PtrTransform->SetPosition(m_Position);
        //衝突判定をつける
        auto PtrGra = AddComponent<Gravity>();

        auto PtrColl = AddComponent<CollisionObb>();
        PtrColl->SetFixed(true);
        ////衝突判定はNoneにする
        PtrColl->SetAfterCollision(AfterCollision::None);

        AddTag(L"FixedBox1");

        //影をつける
        auto ShadowPtr = AddComponent<Shadowmap>();
        ShadowPtr->SetMeshResource(m_Mesh);

        auto PtrDraw = AddComponent<BcPNTStaticModelDraw>();
        PtrDraw->SetFogEnabled(true);
        PtrDraw->SetMeshResource(m_Mesh);
        PtrDraw->SetTextureResource(m_Texture);
        PtrDraw->SetOwnShadowActive(true);

        //物理計算ボックス
        PsBoxParam param(PtrTransform->GetWorldMatrix(), 1.0f, true, PsMotionType::MotionTypeActive);
        auto PsPtr = AddComponent<RigidbodyBox>(param);
        //PsPtr->SetDrawActive(true);
        PtrDraw->SetColorAndAlpha(Col4(1.0f, 0.0f, 0.0f, 1.0f));
	}

    void FixedBox::OnUpdate() {
        auto KeyState = App::GetApp()->GetInputDevice().GetKeyState();
        auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
        if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A) {
            //GetStage()->AddGameObject<TriggerBox>(Vec3(9.0f, 1.0f, 9.0f), Vec3(0.0f), Vec3(0.0f, 1.0f, 0.0f));
        }


    }

    void FixedBox::OnUpdate2() {

    }

    void FixedBox::OnPushA() {


    }

    TriggerBox::TriggerBox(const shared_ptr<Stage>& StagePtr,
        const Vec3& Scale,
        const Vec3& Rotation,
        const Vec3& Position
    ) :
        GameObject(StagePtr),
        m_Scale(Scale),
        m_Rotation(Rotation),
        m_Position(Position)
    {
    }
    TriggerBox::~TriggerBox() {}

    void TriggerBox::OnCreate() {
        auto PtrTransform = GetComponent<Transform>();
        PtrTransform->SetScale(m_Scale);
        PtrTransform->SetRotation(m_Rotation);
        PtrTransform->SetPosition(m_Position);
        
        //タグをつける
        AddTag(L"SoundBox");

        auto PtrColl = AddComponent<CollisionObb>();
        //PtrColl->SetDrawActive(true);
        PtrColl->SetFixed(true);
        ////衝突判定はNoneにする
        PtrColl->SetAfterCollision(AfterCollision::None);

        //影をつける（シャドウマップを描画する）
        auto ShadowPtr = AddComponent<Shadowmap>();
        //影の形（メッシュ）を設定
        ShadowPtr->SetMeshResource(L"DEFAULT_CUBE");
        auto PtrDraw = AddComponent<BcPNTStaticDraw>();
        PtrDraw->SetMeshResource(L"DEFAULT_CUBE");
        PtrDraw->SetFogEnabled(true);
        PtrDraw->SetOwnShadowActive(true);
        //PtrDraw->SetColorAndAlpha(Col4(0.0f, 1.0f, 0.0f, 0.5f));
        PtrDraw->SetDiffuse(Col4(0.0f, 1.0f, 0.0f, 0.1f));

        App::GetApp()->GetScene<Scene>()->PlaySE(L"SoundMachine.wav", 0.1f);
    }

    void TriggerBox::OnUpdate() {
        float elapsedTime = App::GetApp()->GetElapsedTime();
        time += elapsedTime;
		auto PtrDraw = AddComponent<BcPNTStaticDraw>();

		if (time >= 1.0f&&2.0f>=time) {
			PtrDraw->SetDiffuse(Col4(0.5f, 0.5f, 0.0f, 0.1f));

		}
		else if (time >= 2.0f && 3.0f >= time) {

			PtrDraw->SetDiffuse(Col4(1.0f, 0.0f, 0.0f, 0.1f));

		}
        else if (time >= 3.0f) {

            SetUpdateActive(false);
            SetDrawActive(false);
            DeleteObject(this);
        }


    }

    void TriggerBox::OnCollisionEnter(shared_ptr<GameObject>& Other)
    {

    }

	TriggerBox2::TriggerBox2(const shared_ptr<Stage>& StagePtr,
        const Vec3& Scale,
        const Vec3& Rotation,
        const Vec3& Position
    ) :
        GameObject(StagePtr),
        m_Scale(Scale),
        m_Rotation(Rotation),
        m_Position(Position)
    {
    }
    TriggerBox2::~TriggerBox2() {}

    void TriggerBox2::OnCreate() {
        auto PtrTransform = GetComponent<Transform>();
        PtrTransform->SetScale(m_Scale);
        PtrTransform->SetRotation(m_Rotation);
        PtrTransform->SetPosition(m_Position);

        //タグをつける
        AddTag(L"SoundBox");

        auto PtrColl = AddComponent<CollisionObb>();
        //PtrColl->SetDrawActive(true);
        PtrColl->SetFixed(true);
        ////衝突判定はNoneにする
        PtrColl->SetAfterCollision(AfterCollision::None);

		vector<VertexPositionNormalTexture> vertices;
		vector<uint16_t> indices;
		MeshUtill::CreateTorus(1.0f,0.1f,12,vertices, indices);
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

        //影をつける（シャドウマップを描画する）
        auto ShadowPtr = AddComponent<Shadowmap>();
        //影の形（メッシュ）を設定
        //ShadowPtr->SetMeshResource(L"DEFAULT_TORUS");
		auto PtrDraw = AddComponent<BcPNTStaticDraw>();
		PtrDraw->CreateOriginalMesh(vertices, indices);
		PtrDraw->SetOriginalMeshUse(true);
		PtrDraw->SetMeshResource(L"DEFAULT_TORUS");
		PtrDraw->SetFogEnabled(true);
        PtrDraw->SetOwnShadowActive(true);
        //PtrDraw->SetColorAndAlpha(Col4(0.0f, 1.0f, 0.0f, 0.5f));
        //PtrDraw->SetDiffuse(Col4(0.0f, 1.0f, 0.0f, 0.1f));
		PtrDraw->SetDiffuse(Col4(0.0f, 1.0f, 0.0f, 1.0f));

        App::GetApp()->GetScene<Scene>()->PlaySE(L"SoundMachine.wav", 0.5f);
    }

    void TriggerBox2::OnUpdate() {
        float elapsedTime = App::GetApp()->GetElapsedTime();
        time += elapsedTime;
        auto PtrDraw = AddComponent<BcPNTStaticDraw>();

		auto PtrTransform = GetComponent<Transform>();
		m_Scale.x += 1.0f * elapsedTime * m_Speed;
		m_Scale.z += 1.0f * elapsedTime * m_Speed;
		PtrTransform->SetScale(m_Scale);

		if (m_Scale.x >= 10.0f && m_Scale.z >= 10.0f)
		{
			m_Scale.x = 10.0f;
			m_Scale.z = 10.0f;
		}

        if (time >= 1.0f && 2.0f >= time) {
            PtrDraw->SetDiffuse(Col4(0.5f, 0.5f, 0.0f, 0.1f));

        }
        else if (time >= 2.0f && 3.0f >= time) {

            PtrDraw->SetDiffuse(Col4(1.0f, 0.0f, 0.0f, 0.1f));

        }
        else if (time >= 3.0f) {

			App::GetApp()->GetScene<Scene>()->SetSoundFlag(true);

            SetUpdateActive(false);
            SetDrawActive(false);
            DeleteObject(this);
        }
    }
		

//--------------------------------------------------------------------------------------
//	class Player : public GameObject;
//	用途: プレイヤー
//--------------------------------------------------------------------------------------
//構築と破棄
	Kakuninn::Kakuninn(const shared_ptr<Stage>& StagePtr,
        const Vec3& Scale,
        const Vec3& Rotation,
        const Vec3& Position
    ) :
        GameObject(StagePtr),
        m_Scale(Scale),
        m_Rotation(Rotation),
        m_Position(Position)
	{}



	//初期化
	void Kakuninn::OnCreate() {
        auto PtrTransform = GetComponent<Transform>();
        PtrTransform->SetScale(m_Scale);
        PtrTransform->SetRotation(m_Rotation);
        PtrTransform->SetPosition(m_Position);

        ////タグをつける
        //AddTag(L"SoundBox");
        ////影をつける（シャドウマップを描画する）
        //auto ShadowPtr = AddComponent<Shadowmap>();
        ////影の形（メッシュ）を設定
        //ShadowPtr->SetMeshResource(L"DEFAULT_CUBE");
        //auto PtrDraw = AddComponent<BcPNTStaticDraw>();
        //PtrDraw->SetMeshResource(L"DEFAULT_CUBE");
        //PtrDraw->SetFogEnabled(true);
        //PtrDraw->SetOwnShadowActive(true);
        //PtrDraw->SetColorAndAlpha(Col4(0.0f, 1.0f, 0.0f, 0.5f));

        auto ptrString = AddComponent<StringSprite>();



	}

	//更新
	void Kakuninn::OnUpdate() {
	}

	void Kakuninn::OnUpdate2() {
		//文字列の表示
		DrawStrings();
	}


	//文字列の表示
	void Kakuninn::DrawStrings() {

		//オブジェクト数
		auto ObjCount = GetStage()->GetGameObjectVec().size();
		wstring OBJ_COUNT(L"OBJ_COUNT: ");
		OBJ_COUNT += Util::UintToWStr((UINT)ObjCount);
		OBJ_COUNT += L"\n";
		//物理オブジェクト数
		wstring PS_OBJ_COUNT(L"PS_OBJ_COUNT: ");
		PS_OBJ_COUNT += Util::UintToWStr(GetStage()->GetBasePhysics().GetNumBodies());
		PS_OBJ_COUNT += L"\n";
		auto fps = App::GetApp()->GetStepTimer().GetFramesPerSecond();
		wstring FPS(L"FPS: ");
		FPS += Util::UintToWStr(fps);
		FPS += L"\nElapsedTime: ";
		float ElapsedTime = App::GetApp()->GetElapsedTime();
		FPS += Util::FloatToWStr(ElapsedTime);
		FPS += L"\n";

		auto Pos = GetComponent<Transform>()->GetPosition();
		wstring PositionStr(L"Position:\t");
		PositionStr += L"X=" + Util::FloatToWStr(Pos.x, 6, Util::FloatModify::Fixed) + L",\t";
		PositionStr += L"Y=" + Util::FloatToWStr(Pos.y, 6, Util::FloatModify::Fixed) + L",\t";
		PositionStr += L"Z=" + Util::FloatToWStr(Pos.z, 6, Util::FloatModify::Fixed) + L"\n";


		wstring MousePosStr(L"MousePos:\t");
        auto CursorPos = App::GetApp()->GetScene<Scene>()->GetAngle();

		auto MousePos = GetTypeStage<GameStage>()->GetMousePoint();
		MousePosStr += L"X=" + Util::IntToWStr(CursorPos.x + 640) + L",\t";
		MousePosStr += L"Y=" + Util::IntToWStr(CursorPos.y*-1 +400) + L"\n";

		Vec3 Near; Vec3 Far;
		GetTypeStage<GameStage>()->GetMouseRay(Near, Far);

		auto cxScreen = GetSystemMetrics(SM_CXSCREEN);
		auto cyScreen = GetSystemMetrics(SM_CYSCREEN);

		wstring ScreenStr(L"Screen:\t");
		ScreenStr += L"X=" + Util::IntToWStr(cxScreen) + L",\t";
		ScreenStr += L"Y=" + Util::IntToWStr(cyScreen) + L",\n";


		auto viewport = GetTypeStage<GameStage>()->GetView()->GetTargetViewport();
		wstring ViewStr(L"View:\t");
		ViewStr += L"Width=" + Util::FloatToWStr(viewport.Width, 6, Util::FloatModify::Fixed) + L",\t";
		ViewStr += L"Height=" + Util::FloatToWStr(viewport.Height, 6, Util::FloatModify::Fixed) + L",\n";

		wstring MouseRayNearStr(L"RayNear:\t");
		MouseRayNearStr += L"X=" + Util::FloatToWStr(Near.x, 6, Util::FloatModify::Fixed) + L",\t";
		MouseRayNearStr += L"Y=" + Util::FloatToWStr(Near.y, 6, Util::FloatModify::Fixed) + L",\t";
		MouseRayNearStr += L"Z=" + Util::FloatToWStr(Near.z, 6, Util::FloatModify::Fixed) + L"\n";

		wstring MouseRayFarStr(L"RayFar:\t");
		MouseRayFarStr += L"X=" + Util::FloatToWStr(Far.x, 6, Util::FloatModify::Fixed) + L",\t";
		MouseRayFarStr += L"Y=" + Util::FloatToWStr(Far.y, 6, Util::FloatModify::Fixed) + L",\t";
		MouseRayFarStr += L"Z=" + Util::FloatToWStr(Far.z, 6, Util::FloatModify::Fixed) + L"\n";

		wstring updatePerStr(L"UpdatePerformance:\t");
		updatePerStr += Util::FloatToWStr(GetStage()->GetUpdatePerformanceTime());
		updatePerStr += L"\tmillisecond\n";

		wstring drawPerStr(L"DrawPerformance:\t");
		drawPerStr += Util::FloatToWStr(GetStage()->GetDrawPerformanceTime());
		drawPerStr += L"\tmillisecond\n";

		wstring collPerStr(L"CollisionPerform:\t");
		collPerStr += Util::FloatToWStr(GetStage()->GetCollisionPerformanceTime(), 5);
		collPerStr += L"\tmillisecond\n";

		wstring collMiscStr(L"ColMiscPerform:\t");
		collMiscStr += Util::FloatToWStr(GetStage()->GetCollisionManager()->GetMiscPerformanceTime(), 5);
		collMiscStr += L"\tmillisecond\n";

		wstring collTernCountStr(L"CollisionCountOfTern:\t");
		collTernCountStr += Util::UintToWStr(GetStage()->GetCollisionManager()->GetCollisionCountOfTern());
		collTernCountStr += L"\n";


		wstring str =  OBJ_COUNT + PS_OBJ_COUNT + FPS + PositionStr + MousePosStr + ScreenStr + ViewStr
			+ MouseRayNearStr + MouseRayFarStr
			+ updatePerStr + drawPerStr + collPerStr + collMiscStr
			+ collTernCountStr;
		//文字列をつける
		auto PtrString = GetComponent<StringSprite>();
		PtrString->SetText(str);
	}

	//--------------------------------------------------------------------------------------
///	物理計算するアクティブなボックス
//--------------------------------------------------------------------------------------
//構築と破棄
	ActivePsBox::ActivePsBox(const shared_ptr<Stage>& StagePtr,
		const Vec3& Scale,
		const Vec3& Qt,
		const Vec3& Position
	) :
		ActivePsObject(StagePtr),
		m_Scale(Scale),
		m_Qt(Qt),
		m_Position(Position)
	{}

	ActivePsBox::~ActivePsBox() {}
	//初期化
	void ActivePsBox::OnCreate() {
		auto PtrTransform = GetComponent<Transform>();

		PtrTransform->SetScale(m_Scale);
        PtrTransform->SetRotation(m_Qt);
        PtrTransform->SetPosition(m_Position);

		//衝突判定をつける
		auto PtrCol = AddComponent<CollisionObb>();
		//衝突判定はNoneにする
		PtrCol->SetAfterCollision(AfterCollision::None);


		//影をつける
		auto ShadowPtr = AddComponent<Shadowmap>();
		ShadowPtr->SetMeshResource(L"DEFAULT_CUBE");

		auto PtrDraw = AddComponent<BcPNTStaticDraw>();
		PtrDraw->SetFogEnabled(true);
		PtrDraw->SetMeshResource(L"DEFAULT_CUBE");
		PtrDraw->SetOwnShadowActive(true);

		//物理計算ボックス
		PsBoxParam param(PtrTransform->GetWorldMatrix(), 1.0f, true, PsMotionType::MotionTypeActive);
		auto PsPtr = AddComponent<RigidbodyBox>(param);
        //PsPtr->SetAutoTransform(false);

		PsPtr->SetDrawActive(true);
	}


	//構築と破棄
	LineEffect::LineEffect(const shared_ptr<Stage>& StagePtr,
		const Vec3& Scale,
		const Vec3& Rotation,
		const Vec3& Position
	) :
		GameObject(StagePtr),
		m_Scale(Scale),
		m_Rotation(Rotation),
		m_Position(Position)
	{}



	//初期化
	void LineEffect::OnCreate() {
		auto PtrTransform = GetComponent<Transform>();
		PtrTransform->SetScale(m_Scale);
		PtrTransform->SetRotation(m_Rotation);
		PtrTransform->SetPosition(m_Position);

		//タグをつける
		//影をつける（シャドウマップを描画する）
		auto ShadowPtr = AddComponent<Shadowmap>();
		//影の形（メッシュ）を設定
		ShadowPtr->SetMeshResource(L"DEFAULT_CUBE");
		auto PtrDraw = AddComponent<BcPNTStaticDraw>();
		PtrDraw->SetMeshResource(L"DEFAULT_CUBE");
		PtrDraw->SetFogEnabled(true);
		PtrDraw->SetOwnShadowActive(true);
		PtrDraw->SetColorAndAlpha(Col4(0.5f, 0.7f, 0.9f, 1.0f));
		auto PtrColl = AddComponent<CollisionObb>();
		PtrColl->SetAfterCollision(AfterCollision::None);

		auto ptrString = AddComponent<StringSprite>();



	}

	//更新
	void LineEffect::OnUpdate() {
		auto ptrUtil = GetBehavior<UtilBehavior>();
		ptrUtil->RotToHead(1.0f);
		auto elapsedTime = App::GetApp()->GetElapsedTime();


		auto Pos = GetComponent<Transform>()->GetPosition();
		float ElapsedTime = App::GetApp()->GetElapsedTime();
		auto m_Speed = 25.0f;
		Pos += m_Angle * ElapsedTime * m_Speed;
		GetComponent<Transform>()->SetPosition(Pos);

		auto a = Vec3(0.0f, 0.0f, 5.0f);
		auto b = Vec3(0.0f, 0.0f, -12.0f);
		if (a.x - Pos.x<0.5f && a.x - Pos.x > -0.5f && ab == 0) {
			m_Angle = Vec3(0.0f, 0.0f, -1.0f);
			ab = 1;
		}
		if (b.z - Pos.z<0.5f && b.z - Pos.z > -0.5f && ab == 1) {
			m_Angle = Vec3(1.0f, 0.0f, 0.0f);

		}


	}

	void LineEffect::OnCollisionEnter(shared_ptr<GameObject>& other) {
		if (other->FindTag(L"Goal"))
		{
			GetStage()->AddGameObject<LineEffect>(Vec3(1.0f), Vec3(0.0f), Vec3(-8.0f, 0.8f, 5.0f));
			SetUpdateActive(false);
			SetDrawActive(false);

		}


	}

    CheckPointBox::CheckPointBox(const shared_ptr<Stage>& StagePtr,
        const Vec3& Scale,
        const Vec3& Rotation,
        const Vec3& Position
    ) :
        GameObject(StagePtr),
        m_Scale(Scale),
        m_Rotation(Rotation),
        m_Position(Position)
    {
    }
    CheckPointBox::~CheckPointBox() {}

    void CheckPointBox::OnCreate() {
        auto PtrTransform = GetComponent<Transform>();
        PtrTransform->SetScale(m_Scale);
        PtrTransform->SetRotation(m_Rotation);
        PtrTransform->SetPosition(m_Position);

        //タグをつける
        AddTag(L"CheckPointBox");

        auto PtrColl = AddComponent<CollisionCapsule>();
        //PtrColl->SetDrawActive(true);
        PtrColl->SetFixed(true);
        ////衝突判定はNoneにする
        PtrColl->SetAfterCollision(AfterCollision::None);

        //影をつける（シャドウマップを描画する）
        auto ShadowPtr = AddComponent<Shadowmap>();
        //影の形（メッシュ）を設定
        ShadowPtr->SetMeshResource(L"DEFAULT_CUBE");
        auto PtrDraw = AddComponent<BcPNTStaticDraw>();
        PtrDraw->SetMeshResource(L"DEFAULT_CUBE");
        PtrDraw->SetFogEnabled(true);
        PtrDraw->SetOwnShadowActive(true);
        PtrDraw->SetColorAndAlpha(Col4(0.0f, 1.0f, 0.0f, 0.0f));
        PtrDraw->SetDiffuse(Col4(0.0f, 1.0f, 0.0f, 0.1f));
        //SetDrawActive(false);

        App::GetApp()->GetScene<Scene>()->PlaySE(L"SoundMachine.wav", 0.1f);
    }
	//--------------------------------------------------------------------------------------
	//　オープニングカメラマン
	//--------------------------------------------------------------------------------------
	//構築と破棄
	OpeningCameraman::OpeningCameraman(const shared_ptr<Stage>& StagePtr) :
		GameObject(StagePtr),
		m_StartPos(-20.0f, 5.0f, -20.0f),
		m_EndPos(18.0f, 2.0f, 10.0f),
		m_AtStartPos(0.0f, 0.0f, 0.0f),
		m_AtEndPos(18.0f, 0.0f, 18.0f),
		m_AtPos(m_AtStartPos),
		m_TotalTime(0.0f)
	{}
	OpeningCameraman::~OpeningCameraman() {}
	//初期化
	void OpeningCameraman::OnCreate() {
		//初期位置などの設定
		auto ptr = GetComponent<Transform>();
		ptr->SetScale(0.25f, 0.25f, 0.25f);	//直径25センチの球体
		ptr->SetRotation(0.0f, 0.0f, 0.0f);
		ptr->SetPosition(m_StartPos);
		//ステートマシンの構築
		m_StateMachine.reset(new StateMachine<OpeningCameraman>(GetThis<OpeningCameraman>()));
		//最初のステートをOpeningCameramanToGoalStateに設定
		m_StateMachine->ChangeState(OpeningCameramanToGoalState::Instance());
	}
	//操作
	void OpeningCameraman::OnUpdate() {
		//ステートマシンのUpdateを行う
		//この中でステートの切り替えが行われる
		m_StateMachine->Update();
	}

	void OpeningCameraman::ToGoalEnterBehavior() {
		m_StartPos = Vec3(-20.0f, 10.0f, -20.0f);
		m_EndPos = Vec3(18.0f, 2.0f, 10.0f);
		m_AtStartPos = Vec3(-10.0f, 0.0f, 0.0f);
		m_AtEndPos = Vec3(18.0f, 0.0f, 18.0f);
		m_AtPos = m_AtStartPos;
		m_TotalTime = 0.0f;
	}

	void OpeningCameraman::ToStartEnterBehavior() {
		m_StartPos = Vec3(18.0f, 2.0f, 10.0f);
		m_EndPos = Vec3(0.0f, 3.0f, -5.0f);
		m_AtStartPos = Vec3(18.0f, 0.0f, 18.0f);
		m_AtEndPos = Vec3(0.0f, 0.0f, 0.0f);
		m_AtPos = m_AtStartPos;
		m_TotalTime = 0.0f;
	}

	bool OpeningCameraman::ExcuteBehavior(float totaltime) {
		float ElapsedTime = App::GetApp()->GetElapsedTime();
		m_TotalTime += ElapsedTime;
		if (m_TotalTime > totaltime) {
			return true;
		}
		Easing<Vec3> easing;
		auto TgtPos = easing.EaseInOut(EasingType::Cubic, m_StartPos, m_EndPos, m_TotalTime, totaltime);
		m_AtPos = easing.EaseInOut(EasingType::Cubic, m_AtStartPos, m_AtEndPos, m_TotalTime, totaltime);
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetPosition(TgtPos);
		return false;
	}

	void OpeningCameraman::EndStateEnterBehavior() {
		auto ptrGameGtage = GetTypeStage<GameStage>();
		//ptrGameGtage->ToMyCamera();
	}




	//--------------------------------------------------------------------------------------
	//	class OpeningCameramanToGoalState : public ObjState<OpeningCameraman>;
	//--------------------------------------------------------------------------------------
	shared_ptr<OpeningCameramanToGoalState> OpeningCameramanToGoalState::Instance() {
		static shared_ptr<OpeningCameramanToGoalState> instance(new OpeningCameramanToGoalState);
		return instance;
	}
	void OpeningCameramanToGoalState::Enter(const shared_ptr<OpeningCameraman>& Obj) {
		Obj->ToGoalEnterBehavior();
	}
	void OpeningCameramanToGoalState::Execute(const shared_ptr<OpeningCameraman>& Obj) {
		if (Obj->ExcuteBehavior(5.0f)) {
			Obj->GetStateMachine()->ChangeState(OpeningCameramanToStartState::Instance());
		}
	}
	void OpeningCameramanToGoalState::Exit(const shared_ptr<OpeningCameraman>& Obj) {
	}
	//--------------------------------------------------------------------------------------
	//	class OpeningCameramanToStartState : public ObjState<OpeningCameraman>;
	//--------------------------------------------------------------------------------------
	shared_ptr<OpeningCameramanToStartState> OpeningCameramanToStartState::Instance() {
		static shared_ptr<OpeningCameramanToStartState> instance(new OpeningCameramanToStartState);
		return instance;
	}
	void OpeningCameramanToStartState::Enter(const shared_ptr<OpeningCameraman>& Obj) {
		Obj->ToStartEnterBehavior();
	}
	void OpeningCameramanToStartState::Execute(const shared_ptr<OpeningCameraman>& Obj) {
		if (Obj->ExcuteBehavior(3.0f)) {
			Obj->GetStateMachine()->ChangeState(OpeningCameramanEndState::Instance());
		}
	}
	void OpeningCameramanToStartState::Exit(const shared_ptr<OpeningCameraman>& Obj) {
	}

	//--------------------------------------------------------------------------------------
	//	class OpeningCameramanEndState : public ObjState<OpeningCameraman>;
	//--------------------------------------------------------------------------------------
	shared_ptr<OpeningCameramanEndState> OpeningCameramanEndState::Instance() {
		static shared_ptr<OpeningCameramanEndState> instance(new OpeningCameramanEndState);
		return instance;
	}
	void OpeningCameramanEndState::Enter(const shared_ptr<OpeningCameraman>& Obj) {
		Obj->EndStateEnterBehavior();
	}
	void OpeningCameramanEndState::Execute(const shared_ptr<OpeningCameraman>& Obj) {
	}
	void OpeningCameramanEndState::Exit(const shared_ptr<OpeningCameraman>& Obj) {
	}


}
//end basecross
