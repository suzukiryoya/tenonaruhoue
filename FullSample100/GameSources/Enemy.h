#pragma once
#include "stdafx.h"

namespace basecross {

	//�G�P ��l�����U��
	class Enemy1 : public GameObject
	{
	private:

		unique_ptr< StateMachine<Enemy1> >  m_StateMachine;

		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;
		//float m_UPic;
		//float m_VPic;
		wstring m_Texture;
		wstring m_Mesh;
		Vec3 m_StartPos;
		float m_StateChangeSize;
		//�t�H�[�X
		Vec3 m_Force;
		//���x
		Vec3 m_Velocity;
		//�A�j���[�V�����p
		int m_SaveNum;
	public:
		Enemy1(const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Rotation,
			const Vec3& Position
			//float UPic,
			//float VPic
		);

		const unique_ptr<StateMachine<Enemy1>>& GetStateMachine() {
			return m_StateMachine;
		}

		float GetStateChangeSize() const {
			return m_StateChangeSize;
		}
		const Vec3& GetForce()const {
			return m_Force;
		}
		void SetForce(const Vec3& f) {
			m_Force = f;
		}
		void AddForce(const Vec3& f) {
			m_Force += f;
		}


		const Vec3& GetVelocity()const {
			return m_Velocity;
		}
		void SetVelocity(const Vec3& v) {
			m_Velocity = v;
		}

		void ApplyForce();
		
		Vec3 GetTargetPos()const;

		virtual ~Enemy1();
		virtual void OnCreate()override;
		virtual void OnUpdate()override;
		virtual void OnCollisionEnter(shared_ptr<GameObject>& Other);
		void AnimeManager(int num);

		//void OnUpdate();

	};

	//�G�Q �G1�Ǝ�l�����U��
	class Enemy2 : public GameObject
	{
	private:
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;
		float m_UPic;
		float m_VPic;
		wstring m_Texture;
		wstring m_Mesh;
		//�A�j���[�V�����p
		int m_SaveNum;

	public:
		Enemy2(const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Rotation,
			const Vec3& Position,
			float UPic,
			float VPic
		);
		virtual ~Enemy2();
		virtual void OnCreate()override;
		void OnUpdate();
		void AnimeManager(int num);
	};
	//--------------------------------------------------------------------------------------
//	class SeekFarState : public ObjState<SeekObject>;
//	�p�r: �v���C���[���牓���Ƃ��̈ړ�
//--------------------------------------------------------------------------------------
	class SeekFarState : public ObjState<Enemy1>
	{
		SeekFarState() {}
	public:
		static shared_ptr<SeekFarState> Instance();
		virtual void Enter(const shared_ptr<Enemy1>& Obj)override;
		virtual void Execute(const shared_ptr<Enemy1>& Obj)override;
		virtual void Exit(const shared_ptr<Enemy1>& Obj)override;
	};

	//--------------------------------------------------------------------------------------
	//	class SeekNearState : public ObjState<SeekObject>;
	//	�p�r: �v���C���[����߂��Ƃ��̈ړ�
	//--------------------------------------------------------------------------------------
	class SeekNearState : public ObjState<Enemy1>
	{
		SeekNearState() {}
	public:
		static shared_ptr<SeekNearState> Instance();
		virtual void Enter(const shared_ptr<Enemy1>& Obj)override;
		virtual void Execute(const shared_ptr<Enemy1>& Obj)override;
		virtual void Exit(const shared_ptr<Enemy1>& Obj)override;
	};



}
//end basecross
