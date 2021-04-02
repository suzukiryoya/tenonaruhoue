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
        m_Position(Position)
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
        PtrColl->SetDrawActive(true);
        PtrColl->SetFixed(true);
        ////�Փ˔����None�ɂ���
        PtrColl->SetAfterCollision(AfterCollision::None);

        AddTag(L"FixedBox1");

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
        PsPtr->SetDrawActive(true);
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
        PtrColl->SetDrawActive(true);
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


    }

    void TriggerBox::OnUpdate() {
        float elapsedTime = App::GetApp()->GetElapsedTime();
        time += elapsedTime;



        if (time >= 3.0f) {

            SetUpdateActive(false);
            SetDrawActive(false);

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

}
//end basecross
