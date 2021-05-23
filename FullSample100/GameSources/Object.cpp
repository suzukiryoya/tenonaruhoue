/*!
@file Character.cpp
@brief �L�����N�^�[�Ȃǎ���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

    //--------------------------------------------------------------------------------------
///	�����v�Z����A�N�e�B�u�ȃI�u�W�F�N�g�̐e
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
            //���݈ʒu�ƈ�ԋ߂����C��̓_�𓾂�
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
        //�Փ˔��������
        auto PtrGra = AddComponent<Gravity>();

        auto PtrColl = AddComponent<CollisionObb>();
        PtrColl->SetFixed(true);
        ////�Փ˔����None�ɂ���
        PtrColl->SetAfterCollision(AfterCollision::None);

        AddTag(L"FixedBox1");

        //�e������
        auto ShadowPtr = AddComponent<Shadowmap>();
        ShadowPtr->SetMeshResource(m_Mesh);

        auto PtrDraw = AddComponent<BcPNTStaticModelDraw>();
        PtrDraw->SetFogEnabled(true);
        PtrDraw->SetMeshResource(m_Mesh);
        PtrDraw->SetTextureResource(m_Texture);
        PtrDraw->SetOwnShadowActive(true);

        //�����v�Z�{�b�N�X
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
        
        //�^�O������
        AddTag(L"SoundBox");

        auto PtrColl = AddComponent<CollisionObb>();
        //PtrColl->SetDrawActive(true);
        PtrColl->SetFixed(true);
        ////�Փ˔����None�ɂ���
        PtrColl->SetAfterCollision(AfterCollision::None);

        //�e������i�V���h�E�}�b�v��`�悷��j
        auto ShadowPtr = AddComponent<Shadowmap>();
        //�e�̌`�i���b�V���j��ݒ�
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

        //�^�O������
        AddTag(L"SoundBox");

        auto PtrColl = AddComponent<CollisionObb>();
        //PtrColl->SetDrawActive(true);
        PtrColl->SetFixed(true);
        ////�Փ˔����None�ɂ���
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

        //�e������i�V���h�E�}�b�v��`�悷��j
        auto ShadowPtr = AddComponent<Shadowmap>();
        //�e�̌`�i���b�V���j��ݒ�
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
//	�p�r: �v���C���[
//--------------------------------------------------------------------------------------
//�\�z�Ɣj��
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



	//������
	void Kakuninn::OnCreate() {
        auto PtrTransform = GetComponent<Transform>();
        PtrTransform->SetScale(m_Scale);
        PtrTransform->SetRotation(m_Rotation);
        PtrTransform->SetPosition(m_Position);

        ////�^�O������
        //AddTag(L"SoundBox");
        ////�e������i�V���h�E�}�b�v��`�悷��j
        //auto ShadowPtr = AddComponent<Shadowmap>();
        ////�e�̌`�i���b�V���j��ݒ�
        //ShadowPtr->SetMeshResource(L"DEFAULT_CUBE");
        //auto PtrDraw = AddComponent<BcPNTStaticDraw>();
        //PtrDraw->SetMeshResource(L"DEFAULT_CUBE");
        //PtrDraw->SetFogEnabled(true);
        //PtrDraw->SetOwnShadowActive(true);
        //PtrDraw->SetColorAndAlpha(Col4(0.0f, 1.0f, 0.0f, 0.5f));

        auto ptrString = AddComponent<StringSprite>();



	}

	//�X�V
	void Kakuninn::OnUpdate() {
	}

	void Kakuninn::OnUpdate2() {
		//������̕\��
		DrawStrings();
	}


	//������̕\��
	void Kakuninn::DrawStrings() {

		//�I�u�W�F�N�g��
		auto ObjCount = GetStage()->GetGameObjectVec().size();
		wstring OBJ_COUNT(L"OBJ_COUNT: ");
		OBJ_COUNT += Util::UintToWStr((UINT)ObjCount);
		OBJ_COUNT += L"\n";
		//�����I�u�W�F�N�g��
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
		//�����������
		auto PtrString = GetComponent<StringSprite>();
		PtrString->SetText(str);
	}

	//--------------------------------------------------------------------------------------
///	�����v�Z����A�N�e�B�u�ȃ{�b�N�X
//--------------------------------------------------------------------------------------
//�\�z�Ɣj��
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
	//������
	void ActivePsBox::OnCreate() {
		auto PtrTransform = GetComponent<Transform>();

		PtrTransform->SetScale(m_Scale);
        PtrTransform->SetRotation(m_Qt);
        PtrTransform->SetPosition(m_Position);

		//�Փ˔��������
		auto PtrCol = AddComponent<CollisionObb>();
		//�Փ˔����None�ɂ���
		PtrCol->SetAfterCollision(AfterCollision::None);


		//�e������
		auto ShadowPtr = AddComponent<Shadowmap>();
		ShadowPtr->SetMeshResource(L"DEFAULT_CUBE");

		auto PtrDraw = AddComponent<BcPNTStaticDraw>();
		PtrDraw->SetFogEnabled(true);
		PtrDraw->SetMeshResource(L"DEFAULT_CUBE");
		PtrDraw->SetOwnShadowActive(true);

		//�����v�Z�{�b�N�X
		PsBoxParam param(PtrTransform->GetWorldMatrix(), 1.0f, true, PsMotionType::MotionTypeActive);
		auto PsPtr = AddComponent<RigidbodyBox>(param);
        //PsPtr->SetAutoTransform(false);

		PsPtr->SetDrawActive(true);
	}


	//�\�z�Ɣj��
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



	//������
	void LineEffect::OnCreate() {
		auto PtrTransform = GetComponent<Transform>();
		PtrTransform->SetScale(m_Scale);
		PtrTransform->SetRotation(m_Rotation);
		PtrTransform->SetPosition(m_Position);

		//�^�O������
		//�e������i�V���h�E�}�b�v��`�悷��j
		auto ShadowPtr = AddComponent<Shadowmap>();
		//�e�̌`�i���b�V���j��ݒ�
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

	//�X�V
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

        //�^�O������
        AddTag(L"CheckPointBox");

        auto PtrColl = AddComponent<CollisionCapsule>();
        //PtrColl->SetDrawActive(true);
        PtrColl->SetFixed(true);
        ////�Փ˔����None�ɂ���
        PtrColl->SetAfterCollision(AfterCollision::None);

        //�e������i�V���h�E�}�b�v��`�悷��j
        auto ShadowPtr = AddComponent<Shadowmap>();
        //�e�̌`�i���b�V���j��ݒ�
        ShadowPtr->SetMeshResource(L"DEFAULT_CUBE");
        auto PtrDraw = AddComponent<BcPNTStaticDraw>();
        PtrDraw->SetMeshResource(L"DEFAULT_CUBE");
        PtrDraw->SetFogEnabled(true);
        PtrDraw->SetOwnShadowActive(true);
        PtrDraw->SetColorAndAlpha(Col4(0.0f, 1.0f, 0.0f, 0.0f));
        PtrDraw->SetDiffuse(Col4(0.0f, 1.0f, 0.0f, 0.1f));
        SetDrawActive(false);

        App::GetApp()->GetScene<Scene>()->PlaySE(L"SoundMachine.wav", 0.1f);
    }



}
//end basecross
