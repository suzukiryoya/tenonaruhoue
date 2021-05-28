/*!
@file MyCamera.h
@brief カメラ
*/

#pragma once
#include "stdafx.h"

namespace basecross{
	class MyCamera : public Camera {
		weak_ptr<GameObject> m_TargetObject;	//目標となるオブジェクト
		float m_ToTargetLerp;	//目標を追いかける際の補間値
		bsm::Vec3 m_TargetToAt;	//目標から視点を調整する位置ベクトル

		float m_RadY;
		float m_RadXZ;
		//カメラの上下スピード
		float m_CameraUpDownSpeed;
		//カメラを下げる下限角度
		float m_CameraUnderRot;
		//腕の長さの設定
		float m_ArmLen;
		float m_MaxArm;
		float m_MinArm;
		//回転スピード
		float m_RotSpeed;
		//ズームスピード
		float m_ZoomSpeed;
		//左右スティック変更のモード
		bool m_LRBaseMode;
		//上下スティック変更のモード
		bool m_UDBaseMode;
	public:

		MyCamera();
		//MyCamera(float ArmLen);
		virtual ~MyCamera() {}
		virtual void SetEye(const bsm::Vec3& Eye)override;
		virtual void SetAt(const bsm::Vec3& At)override;
		void OnUpdate();

		shared_ptr<GameObject> GetTargetObject() const;
		//カメラの目標オブジェクトを設定する
		void SetTargetObject(const shared_ptr<GameObject>& Obj);
		//オブジェクトを追いかける場合の補間値を得る
		float GetToTargetLerp() const;
		//オブジェクトを追いかける場合の補間値を設定する
		void SetToTargetLerp(float f);

		//void UpdateArmLengh();
	};

	//--------------------------------------------------------------------------------------
	//　スタートカメラ
	//--------------------------------------------------------------------------------------
	class StartCamera : public Camera {
	public:
		StartCamera();
		virtual ~StartCamera();
		virtual void OnUpdate()override;
	};

	//--------------------------------------------------------------------------------------
	//　スタートカメラマン
	//--------------------------------------------------------------------------------------
	class StartCameraman : public GameObject {
		Vec3 m_StartPos;
		Vec3 m_EndPos;
		Vec3 m_AtStartPos;
		Vec3 m_AtEndPos;
		Vec3 m_AtPos;
		Vec3 m_PlayerPos;
		Vec3 m_GoalPos;
		float m_TotalTime;
		//ステートマシーン
		unique_ptr< StateMachine<StartCameraman> >  m_StateMachine;
	public:
		//構築と破棄
		StartCameraman(const shared_ptr<Stage>& StagePtr);
		virtual ~StartCameraman();
		//初期化
		virtual void OnCreate() override;
		//操作
		virtual void OnUpdate() override;
		//アクセサ
		const unique_ptr<StateMachine<StartCameraman>>& GetStateMachine() {
			return m_StateMachine;
		}

		Vec3 GetAtPos() const {
			return m_AtPos;
		}
		Vec3 GetPlayerPos()
		{
			return m_PlayerPos;
		};
		Vec3 GetGoalPos()
		{
			return m_GoalPos;
		};
		void SetStartCameraPos(Vec3 playerPos, Vec3 goalPos);
 		void ToGoalEnterBehavior(Vec3 playerPos, Vec3 goalPos);
		void ToStartEnterBehavior(Vec3 playerPos, Vec3 goalPos);
		bool ExcuteBehavior(float totaltime);
		void EndStateEnterBehavior();
	};

	//--------------------------------------------------------------------------------------
	//	class StartCameramanToGoalState : public ObjState<StartCameraman>;
	//--------------------------------------------------------------------------------------
	class StartCameramanToGoalState : public ObjState<StartCameraman>
	{
		StartCameramanToGoalState() {}
	public:
		static shared_ptr<StartCameramanToGoalState> Instance();
		virtual void Enter(const shared_ptr<StartCameraman>& Obj)override;
		virtual void Execute(const shared_ptr<StartCameraman>& Obj)override;
		virtual void Exit(const shared_ptr<StartCameraman>& Obj)override;
	};

	//--------------------------------------------------------------------------------------
	//	class StartCameramanToStartState : public ObjState<StartCameraman>;
	//--------------------------------------------------------------------------------------
	class StartCameramanToStartState : public ObjState<StartCameraman>
	{
		StartCameramanToStartState() {}
	public:
		static shared_ptr<StartCameramanToStartState> Instance();
		virtual void Enter(const shared_ptr<StartCameraman>& Obj)override;
		virtual void Execute(const shared_ptr<StartCameraman>& Obj)override;
		virtual void Exit(const shared_ptr<StartCameraman>& Obj)override;
	};

	//--------------------------------------------------------------------------------------
	//	class StartCameramanEndState : public ObjState<StartCameraman>;
	//--------------------------------------------------------------------------------------
	class StartCameramanEndState : public ObjState<StartCameraman>
	{
		StartCameramanEndState() {}
	public:
		static shared_ptr<StartCameramanEndState> Instance();
		virtual void Enter(const shared_ptr<StartCameraman>& Obj)override;
		virtual void Execute(const shared_ptr<StartCameraman>& Obj)override;
		virtual void Exit(const shared_ptr<StartCameraman>& Obj)override;
	};
}
//end basecross
