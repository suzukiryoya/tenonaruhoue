/*!
@file Character.h
@brief �L�����N�^�[�Ȃ�
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
///	�����v�Z����A�N�e�B�u�ȃI�u�W�F�N�g�̐e
//--------------------------------------------------------------------------------------
	class ActivePsObject : public GameObject {
		bool m_Selected;
	protected:
		ActivePsObject(const shared_ptr<Stage>& StagePtr) :
			GameObject(StagePtr), m_Selected(false) {}
		virtual ~ActivePsObject() {}
	public:
		void SetSelected(bool b) {
			m_Selected = b;
			//auto PtrDraw = AddComponent<BcPNTStaticDraw>();
			//if (b) {
			//	PtrDraw->SetEmissive(Col4(1.0f, 1.0f, 0, 0));

			//}
			//else {
			//	PtrDraw->SetEmissive(Col4(0.0f, 0.0f, 0, 0));
			//}

		}
		bool IsSelected() {
			return m_Selected;
		}
		//�X�V
		virtual void OnUpdate() override;
	};

	class FixedBox : public ActivePsObject {
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;
		wstring m_Texture;
		wstring m_Mesh;
	public:
		//�\�z�Ɣj��
		FixedBox(const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Rotation,
			const Vec3& Position
		);
		virtual ~FixedBox();
		//������
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
		virtual void OnUpdate2() override;


		void OnPushA();
		//����
	};


	class TriggerBox : public GameObject {
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;

		float time;
	public:
		//�\�z�Ɣj��
		TriggerBox(const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Rotation,
			const Vec3& Position
		);
		virtual ~TriggerBox();
		//������
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
		virtual void OnCollisionEnter(shared_ptr<GameObject>& Other) override;

		//����

	//end basecross

	};

	//����
	class TriggerBox2 : public GameObject {

		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;

		float m_UPic = 1.0f;
		float m_VPic = 1.0f;
		float m_Speed = 8.5f;
		float time;
	public:
		//�\�z�Ɣj��
		TriggerBox2(const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Rotation,
			const Vec3& Position
		);
		virtual ~TriggerBox2();
		//������
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
	};

	//--------------------------------------------------------------------------------------
	///	�v���C���[
	//--------------------------------------------------------------------------------------
	class Kakuninn : public GameObject {

		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;

		//������̕\��
		void DrawStrings();
	public:
		//�\�z�Ɣj��
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�R���X�g���N�^
		@param[in]	StagePtr	�X�e�[�W
		@param[in]	StartPos	�����ʒu
		*/
		//--------------------------------------------------------------------------------------
		Kakuninn(const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Rotation,
			const Vec3& Position);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�f�X�g���N�^
		*/
		//--------------------------------------------------------------------------------------
		virtual ~Kakuninn() {}
		//�A�N�Z�T
		//������
		virtual void OnCreate() override;
		//�X�V
		virtual void OnUpdate() override;
		virtual void OnUpdate2() override;

	};

	//--------------------------------------------------------------------------------------
///	�����v�Z����A�N�e�B�u�ȃ{�b�N�X
//--------------------------------------------------------------------------------------
	class ActivePsBox : public ActivePsObject {
		Vec3 m_Scale;
		Vec3 m_Qt;
		Vec3 m_Position;
	public:
		//�\�z�Ɣj��
		ActivePsBox(const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Qt,
			const Vec3& Position
		);
		virtual ~ActivePsBox();
		//������
		virtual void OnCreate() override;
	};


	//--------------------------------------------------------------------------------------
///	�v���C���[
//--------------------------------------------------------------------------------------
	class LineEffect : public GameObject {

		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;

	public:

		Vec3 m_Angle = Vec3(1.0f, 0.0f, 0.0f);
		float ab = 0;

		//�\�z�Ɣj��
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�R���X�g���N�^
		@param[in]	StagePtr	�X�e�[�W
		@param[in]	StartPos	�����ʒu
		*/
		//--------------------------------------------------------------------------------------
		LineEffect(const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Rotation,
			const Vec3& Position);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�f�X�g���N�^
		*/
		//--------------------------------------------------------------------------------------
		virtual ~LineEffect() {}
		//�A�N�Z�T
		//������
		virtual void OnCreate() override;
		//�X�V
		virtual void OnUpdate() override;
		void OnCollisionEnter(shared_ptr<GameObject>& other);

	};

	class CheckPointBox : public GameObject {
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;

		float time;
	public:
		//�\�z�Ɣj��
		CheckPointBox(const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Rotation,
			const Vec3& Position
		);
		virtual ~CheckPointBox();
		//������
		virtual void OnCreate() override;
	};

	//--------------------------------------------------------------------------------------
//�@�I�[�v�j���O�J�����}��
//--------------------------------------------------------------------------------------
	class OpeningCameraman : public GameObject {
		Vec3 m_StartPos;
		Vec3 m_EndPos;
		Vec3 m_AtStartPos;
		Vec3 m_AtEndPos;
		Vec3 m_AtPos;
		float m_TotalTime;
		//�X�e�[�g�}�V�[��
		unique_ptr< StateMachine<OpeningCameraman> >  m_StateMachine;
	public:
		//�\�z�Ɣj��
		OpeningCameraman(const shared_ptr<Stage>& StagePtr);
		virtual ~OpeningCameraman();
		//������
		virtual void OnCreate() override;
		//����
		virtual void OnUpdate() override;
		//�A�N�Z�T
		const unique_ptr<StateMachine<OpeningCameraman>>& GetStateMachine() {
			return m_StateMachine;
		}

		Vec3 GetAtPos() const {
			return m_AtPos;
		}
		void ToGoalEnterBehavior();
		void ToStartEnterBehavior();
		bool ExcuteBehavior(float totaltime);
		void EndStateEnterBehavior();
	};

	//--------------------------------------------------------------------------------------
	//	class OpeningCameramanToGoalState : public ObjState<OpeningCameraman>;
	//--------------------------------------------------------------------------------------
	class OpeningCameramanToGoalState : public ObjState<OpeningCameraman>
	{
		OpeningCameramanToGoalState() {}
	public:
		static shared_ptr<OpeningCameramanToGoalState> Instance();
		virtual void Enter(const shared_ptr<OpeningCameraman>& Obj)override;
		virtual void Execute(const shared_ptr<OpeningCameraman>& Obj)override;
		virtual void Exit(const shared_ptr<OpeningCameraman>& Obj)override;
	};

	//--------------------------------------------------------------------------------------
	//	class OpeningCameramanToStartState : public ObjState<OpeningCameraman>;
	//--------------------------------------------------------------------------------------
	class OpeningCameramanToStartState : public ObjState<OpeningCameraman>
	{
		OpeningCameramanToStartState() {}
	public:
		static shared_ptr<OpeningCameramanToStartState> Instance();
		virtual void Enter(const shared_ptr<OpeningCameraman>& Obj)override;
		virtual void Execute(const shared_ptr<OpeningCameraman>& Obj)override;
		virtual void Exit(const shared_ptr<OpeningCameraman>& Obj)override;
	};

	//--------------------------------------------------------------------------------------
	//	class OpeningCameramanEndState : public ObjState<OpeningCameraman>;
	//--------------------------------------------------------------------------------------
	class OpeningCameramanEndState : public ObjState<OpeningCameraman>
	{
		OpeningCameramanEndState() {}
	public:
		static shared_ptr<OpeningCameramanEndState> Instance();
		virtual void Enter(const shared_ptr<OpeningCameraman>& Obj)override;
		virtual void Execute(const shared_ptr<OpeningCameraman>& Obj)override;
		virtual void Exit(const shared_ptr<OpeningCameraman>& Obj)override;
	};



}