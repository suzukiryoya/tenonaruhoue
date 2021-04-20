#pragma once
#include "stdafx.h"

namespace basecross {

	//敵１
	class Enemy1 : public GameObject
	{
	private:
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;
		//float m_UPic;
		//float m_VPic;
		wstring m_Texture;
		wstring m_Mesh;

	public:
		Enemy1(const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Rotation,
			const Vec3& Position
			//float UPic,
			//float VPic
		);
		//float GetStateChangeSize() const {
		//	return m_StateChangeSize;
		//}
		//const Vec3& GetForce()const {
		//	return m_Force;
		//}
		//void SetForce(const Vec3& f) {
		//	m_Force = f;
		//}
		//void AddForce(const Vec3& f) {
		//	m_Force += f;
		//}


		//const Vec3& GetVelocity()const {
		//	return m_Velocity;
		//}
		//void SetVelocity(const Vec3& v) {
		//	m_Velocity = v;
		//}

		//void ApplyForce();

		//Vec3 GetTargetPos()const;

		virtual ~Enemy1();
		virtual void OnCreate()override;
		virtual void OnUpdate()override;
		virtual void OnCollisionEnter(shared_ptr<GameObject>& Other);

		//void OnUpdate();

	};

	//敵２
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
		//void OnUpdate();

	};

	class SeekObject : public GameObject {
		//ステートマシーン
		unique_ptr< StateMachine<SeekObject> >  m_StateMachine;
		Vec3 m_StartPos;
		float m_StateChangeSize;
		//フォース
		Vec3 m_Force;
		//速度
		Vec3 m_Velocity;
	public:
		//構築と破棄
		SeekObject(const shared_ptr<Stage>& StagePtr, const Vec3& StartPos);
		virtual ~SeekObject();
		//初期化
		virtual void OnCreate() override;
		//アクセサ
		const unique_ptr<StateMachine<SeekObject>>& GetStateMachine() {
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


		//操作
		virtual void OnUpdate() override;
		virtual void OnUpdate2() override;
		virtual void OnCollisionEnter(shared_ptr<GameObject>& Other) override;
	};


	//--------------------------------------------------------------------------------------
//	class SeekFarState : public ObjState<SeekObject>;
//	用途: プレイヤーから遠いときの移動
//--------------------------------------------------------------------------------------
	class SeekFarState : public ObjState<SeekObject>
	{
		SeekFarState() {}
	public:
		static shared_ptr<SeekFarState> Instance();
		virtual void Enter(const shared_ptr<SeekObject>& Obj)override;
		virtual void Execute(const shared_ptr<SeekObject>& Obj)override;
		virtual void Exit(const shared_ptr<SeekObject>& Obj)override;
	};

	//--------------------------------------------------------------------------------------
	//	class SeekNearState : public ObjState<SeekObject>;
	//	用途: プレイヤーから近いときの移動
	//--------------------------------------------------------------------------------------
	class SeekNearState : public ObjState<SeekObject>
	{
		SeekNearState() {}
	public:
		static shared_ptr<SeekNearState> Instance();
		virtual void Enter(const shared_ptr<SeekObject>& Obj)override;
		virtual void Execute(const shared_ptr<SeekObject>& Obj)override;
		virtual void Exit(const shared_ptr<SeekObject>& Obj)override;
	};



}
//end basecross
