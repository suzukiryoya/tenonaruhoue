/*!
@file MyCamera.h
@brief �J����
*/

#pragma once
#include "stdafx.h"

namespace basecross{
	class MyCamera : public Camera {
		weak_ptr<GameObject> m_TargetObject;	//�ڕW�ƂȂ�I�u�W�F�N�g
		float m_ToTargetLerp;	//�ڕW��ǂ�������ۂ̕�Ԓl
		bsm::Vec3 m_TargetToAt;	//�ڕW���王�_�𒲐�����ʒu�x�N�g��

		float m_RadY;
		float m_RadXZ;
		//�J�����̏㉺�X�s�[�h
		float m_CameraUpDownSpeed;
		//�J�����������鉺���p�x
		float m_CameraUnderRot;
		//�r�̒����̐ݒ�
		float m_ArmLen;
		float m_MaxArm;
		float m_MinArm;
		//��]�X�s�[�h
		float m_RotSpeed;
		//�Y�[���X�s�[�h
		float m_ZoomSpeed;
		//���E�X�e�B�b�N�ύX�̃��[�h
		bool m_LRBaseMode;
		//�㉺�X�e�B�b�N�ύX�̃��[�h
		bool m_UDBaseMode;
	public:

		MyCamera();
		//MyCamera(float ArmLen);
		virtual ~MyCamera() {}
		virtual void SetEye(const bsm::Vec3& Eye)override;
		virtual void SetAt(const bsm::Vec3& At)override;
		void OnUpdate();

		shared_ptr<GameObject> GetTargetObject() const;
		//�J�����̖ڕW�I�u�W�F�N�g��ݒ肷��
		void SetTargetObject(const shared_ptr<GameObject>& Obj);
		//�I�u�W�F�N�g��ǂ�������ꍇ�̕�Ԓl�𓾂�
		float GetToTargetLerp() const;
		//�I�u�W�F�N�g��ǂ�������ꍇ�̕�Ԓl��ݒ肷��
		void SetToTargetLerp(float f);

		//void UpdateArmLengh();
	};

	//--------------------------------------------------------------------------------------
	//�@�X�^�[�g�J����
	//--------------------------------------------------------------------------------------
	class StartCamera : public Camera {
	public:
		StartCamera();
		virtual ~StartCamera();
		virtual void OnUpdate()override;
	};

	//--------------------------------------------------------------------------------------
	//�@�X�^�[�g�J�����}��
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
		//�X�e�[�g�}�V�[��
		unique_ptr< StateMachine<StartCameraman> >  m_StateMachine;
	public:
		//�\�z�Ɣj��
		StartCameraman(const shared_ptr<Stage>& StagePtr);
		virtual ~StartCameraman();
		//������
		virtual void OnCreate() override;
		//����
		virtual void OnUpdate() override;
		//�A�N�Z�T
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
