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
        GameObject(StagePtr),
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
        //OBB�Փ�j�����t����
        auto PtrColl = AddComponent<CollisionObb>();
        PtrColl->SetFixed(true);
        //�^�O������
        AddTag(L"FixedBox");

        //�e������i�V���h�E�}�b�v��`�悷��j
        auto ShadowPtr = AddComponent<Shadowmap>();
        //�e�̌`�i���b�V���j��ݒ�
        ShadowPtr->SetMeshResource(L"DEFAULT_CUBE");
        auto PtrDraw = AddComponent<BcPNTStaticDraw>();
        PtrDraw->SetMeshResource(L"DEFAULT_CUBE");
        PtrDraw->SetFogEnabled(true);
        PtrDraw->SetOwnShadowActive(true);
        PtrDraw->SetColorAndAlpha(Col4(1.0f, 0.0f, 0.0f, 1.0f));
	}

    void FixedBox::OnUpdate() {
        auto KeyState = App::GetApp()->GetInputDevice().GetKeyState();
        auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
        if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A) {
            GetStage()->AddGameObject<TriggerBox>(Vec3(3.0f), Vec3(0.0f), Vec3(0.0f, 1.0f, 0.0f));

        }

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
        //�e������i�V���h�E�}�b�v��`�悷��j
        auto ShadowPtr = AddComponent<Shadowmap>();
        //�e�̌`�i���b�V���j��ݒ�
        ShadowPtr->SetMeshResource(L"DEFAULT_CUBE");
        auto PtrDraw = AddComponent<BcPNTStaticDraw>();
        PtrDraw->SetMeshResource(L"DEFAULT_CUBE");
        PtrDraw->SetFogEnabled(true);
        PtrDraw->SetOwnShadowActive(true);
        PtrDraw->SetColorAndAlpha(Col4(0.0f, 1.0f, 0.0f, 0.5f));


    }




}
//end basecross
