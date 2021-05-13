#pragma once
#include "stdafx.h"

namespace basecross {

	//敵１ 主人公を攻撃
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
		//フォース
		Vec3 m_SoundPos;
		//速度
		Vec3 m_Velocity;
		//アニメーション用
		int m_SaveNum;
		std::shared_ptr<basecross::Action> m_ptraction;
		float m_a;
		int m_switch = 0;
		float m_time = 0.0f;
		Vec3 m_Angle = Vec3(1.0f, 0.0f, 0.0f);
		float m_DieTime = 0;
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
		const Vec3& GetPosition()const {
			return m_SoundPos;
		}
		void SetPosition(const Vec3& f) {
			m_SoundPos = f;
		}
		void ActionClear() {
			m_ptraction->Stop();
			m_ptraction->AllActionClear();
		}
		float GetCount() {
			return m_a;
		}

		const Vec3& GetVelocity()const {
			return m_Velocity;
		}
		void SetVelocity(const Vec3& v) {
			m_Velocity = v;
		}
		void SetTimer() {
			m_time = 0;
		}

		void ApplyForce();
		void ApplyForce2();

		Vec3 GetTargetPos()const;

		virtual ~Enemy1();
		virtual void OnCreate()override;
		virtual void OnUpdate()override;
		virtual void OnCollisionEnter(shared_ptr<GameObject>& Other);
		virtual void OnCollisionExit(shared_ptr<GameObject>& Other);
		void AnimeManager(int num);

		//void OnUpdate();

	};

	//敵２ 敵1と主人公を攻撃
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
		//アニメーション用
		int m_SaveNum;
		float ab = 0;
		float m_MotionTime = 0;

		Vec3 m_Angle = Vec3(1.0f, 0.0f, 0.0f);
		float m_time=0.0f;

	public:
		Enemy2(const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Rotation,
			const Vec3& Position
		);
		virtual ~Enemy2();
		virtual void OnCreate()override;
		void OnUpdate();
		void OnCollisionEnter(shared_ptr<GameObject>& other);

		void AnimeManager(int num);
	};
	//--------------------------------------------------------------------------------------
//	class SeekFarState : public ObjState<SeekObject>;
//	用途: プレイヤーから遠いときの移動
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
	//	用途: プレイヤーから近いときの移動
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



	class SoundBoxState : public ObjState<Enemy1>
	{
		SoundBoxState() {}
	public:
		static shared_ptr<SoundBoxState> Instance();
		virtual void Enter(const shared_ptr<Enemy1>& Obj)override;
		virtual void Execute(const shared_ptr<Enemy1>& Obj)override;
		virtual void Exit(const shared_ptr<Enemy1>& Obj)override;
	};


	class Playerdummy : public GameObject
	{
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;
		wstring m_Mesh;
		//アニメーション用
		int m_SaveNum;
		float ab = 0;
		Vec3 m_Angle = Vec3(1.0f, 0.0f, 0.0f);
		float m_MotionTime = 0;

	public:
		Playerdummy(const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Rotation,
			const Vec3& Position
		);
		virtual ~Playerdummy();
		virtual void OnCreate()override;
		void OnUpdate();
		void AnimeManager(int num);
		void OnCollisionEnter(shared_ptr<GameObject>& other);

	};
}
//end basecross
