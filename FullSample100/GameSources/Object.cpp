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
        m_Position(Position)
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
        PtrColl->SetDrawActive(true);
        PtrColl->SetFixed(true);
        ////衝突判定はNoneにする
        PtrColl->SetAfterCollision(AfterCollision::None);

        AddTag(L"FixedBox1");

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
        
        //タグをつける
        AddTag(L"SoundBox");

        auto PtrColl = AddComponent<CollisionObb>();
        PtrColl->SetDrawActive(true);
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

}
//end basecross
