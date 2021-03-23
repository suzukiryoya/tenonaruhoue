/*!
@file Player.cpp
@brief �v���C���[�Ȃǎ���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{
	Player::Player(const shared_ptr<Stage>& StagePtr,
		const Vec3& Scale,
		const Vec3& Rotation,
		const Vec3& Position)
		: GameObject(StagePtr), m_Speed(5.0f), m_GoalPos(12.0f,1.0f,-9.5f), m_Scale(Scale), m_Rotation(Rotation), m_Position(Position), m_Mesh(L"Protagonist_Robot_2_ver2.bmf")
	{
	}

	Player::~Player()
	{
	}

	void Player::OnCreate()
	{
		//�����ʒu�Ȃǂ̐ݒ�
		auto PtrTrans = GetComponent<Transform>();
		PtrTrans->SetScale(m_Scale);
		PtrTrans->SetRotation(m_Rotation);
		PtrTrans->SetPosition(m_Position);

		//CollisionObb�Փ˔����t����
		auto ptrColl = AddComponent<CollisionObb>();
		
		ptrColl->SetMakedSize(1.5f);
		//�d�͂�����
		auto PtrGra = AddComponent<Gravity>();

		GetStage()->SetCollisionPerformanceActive(true);
		GetStage()->SetUpdatePerformanceActive(true);
		GetStage()->SetDrawPerformanceActive(true);

		Mat4x4 SpanMat; // ���f���ƃg�����X�t�H�[���̊Ԃ̍����s��
		SpanMat.affineTransformation(
			Vec3(1.0f, 1.0f, 1.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f));

		//�e������i�V���h�E�}�b�v��`�悷��j
		auto ShadowPtr = AddComponent<Shadowmap>();
		//�e�̌`�i���b�V���j��ݒ�
		ShadowPtr->SetMeshResource(m_Mesh);
		ShadowPtr->SetMeshToTransformMatrix(SpanMat);

		//�����������
		auto ptrString = AddComponent<StringSprite>();
		ptrString->SetText(L"");
		ptrString->SetTextRect(Rect2D<float>(16.0f, 16.0f, 640.0f, 480.0f));

		//�`��R���|�[�l���g�̐ݒ�
		auto ptrDraw = AddComponent<BcPNTStaticModelDraw>();
		ptrDraw->SetFogEnabled(true);
		//�`�悷�郁�b�V����ݒ�
		ptrDraw->SetMeshResource(m_Mesh);
		ptrDraw->SetOwnShadowActive(true);
		//ptrDraw->AddAnimation(L"Wait", 0, 1, true, 20);
		//ptrDraw->AddAnimation(L"Walk", 10, 30, true, 110);
		//ptrDraw->ChangeCurrentAnimation(L"Wait");

		//////�`�悷��e�N�X�`����ݒ�
		//ptrDraw->SetTextureResource(L"PLAYER_TX");


		//SetAlphaActive(true);

		//�J�����𓾂�
		auto ptrCamera = dynamic_pointer_cast<Camera>(OnGetDrawCamera());
		if (ptrCamera) {
			//MyCamera�ł���
			//MyCamera�ɒ��ڂ���I�u�W�F�N�g�i�v���C���[�j�̐ݒ�
			//ptrCamera->SetTargetObject(GetThis<GameObject>());
			//ptrCamera->SetTargetToAt(GetComponent<Transform>()->GetPosition());
		}
	}

	void Player::OnUpdate()
	{
		playerMove();
	}

	void Player::playerMove()
	{
		auto ptrTrans = GetComponent<Transform>();
		auto pos = ptrTrans->GetPosition();
		float elapsedTime = App::GetApp()->GetElapsedTime();
	}

	void Player::OnCollisionEnter(shared_ptr<GameObject>& other)
	{
		//auto ptr = GetStage()->CreateSharedObjectGroup(L"Wall");
		auto trans = GetComponent<Transform>();
		float elapsedTime = App::GetApp()->GetElapsedTime();

		if (other->FindTag(L"Wall"))
		{
			auto pos = trans->GetPosition();
			auto GoalToNowPos = pos - m_GoalPos;
			GoalToNowPos.normalize();

			pos -= GoalToNowPos * elapsedTime * m_Speed;

			trans->SetRotation(-GoalToNowPos.x, 0, 0);
			trans->SetPosition(pos);
		}
	}

}
//end basecross

