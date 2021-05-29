/*!
@file MyCamera.cpp
@brief カメラ
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	MyCamera::MyCamera():
		Camera(),
		m_RadY(0.5f),
		m_RadXZ(0.0f),
		m_CameraUpDownSpeed(0.5f),
		m_CameraUnderRot(0.1f),
		m_ArmLen(5.0f),
		m_MaxArm(20.0f),
		m_MinArm(2.0f),
		m_RotSpeed(1.0f),
		m_ZoomSpeed(0.1f),
		m_LRBaseMode(true),
		m_UDBaseMode(true)
	{}

	void MyCamera::SetEye(const bsm::Vec3& Eye) {
		Camera::SetEye(Eye);
		//UpdateArmLengh();
	}

	void MyCamera::SetAt(const bsm::Vec3& At) {
		Camera::SetAt(At);
		//Vec3 armVec = GetEye() - GetAt();
		//armVec.normalize();
		//armVec *= m_ArmLen;
		//Vec3 newEye = GetAt() + armVec;
		//Camera::SetEye(newEye);
	}

	void MyCamera::OnUpdate()
	{
		Camera::OnUpdate();
	}

	shared_ptr<GameObject> MyCamera::GetTargetObject() const {
		if (!m_TargetObject.expired()) {
			return m_TargetObject.lock();
		}
		return nullptr;
	}

	void MyCamera::SetTargetObject(const shared_ptr<GameObject>& Obj) {
		m_TargetObject = Obj;
	}

	float MyCamera::GetToTargetLerp() const {
		return m_ToTargetLerp;
	}
	void MyCamera::SetToTargetLerp(float f) {
		m_ToTargetLerp = f;
	}
	//--------------------------------------------------------------------------------------
	//　スタートカメラ
	//--------------------------------------------------------------------------------------
	StartCamera::StartCamera() :
		Camera()
	{}
	StartCamera::~StartCamera() {}

	void StartCamera::OnUpdate() {
		auto ptrStartCameraman = dynamic_pointer_cast<StartCameraman>(GetCameraObject());
		if (ptrStartCameraman) {
			auto pos = ptrStartCameraman->GetAtPos();
			SetAt(pos);
		}
		Camera::OnUpdate();
	}

	//--------------------------------------------------------------------------------------
	//　スタートカメラマン
	//--------------------------------------------------------------------------------------
	//構築と破棄
	StartCameraman::StartCameraman(const shared_ptr<Stage>& StagePtr) :
		GameObject(StagePtr),
		m_StartPos(0.0f, 20.0f, -5.0f),
		m_EndPos(0.0f, 20.0f, -5.0f),
		m_AtStartPos(0.0f, 0.0f, 0.0f),
		m_AtEndPos(0.0f, 0.0f, 0.0f),
		m_AtPos(m_AtStartPos),
		m_TotalTime(0.0f)
	{}
	StartCameraman::~StartCameraman() {}
	//初期化
	void StartCameraman::OnCreate() {
		//初期位置などの設定
		auto ptr = GetComponent<Transform>();
		ptr->SetScale(0.25f, 0.25f, 0.25f);	//直径25センチの球体
		ptr->SetRotation(0.0f, 0.0f, 0.0f);
		ptr->SetPosition(m_StartPos);
		//ステートマシンの構築
		m_StateMachine.reset(new StateMachine<StartCameraman>(GetThis<StartCameraman>()));
		//最初のステートをStartCameramanToGoalStateに設定
		m_StateMachine->ChangeState(StartCameramanToGoalState::Instance());
	}
	
	void StartCameraman::SetStartCameraPos(Vec3 playerPos, Vec3 goalPos)
	{
		m_PlayerPos = playerPos;
		m_GoalPos = goalPos;
	}

	//操作
	void StartCameraman::OnUpdate() {
		//ステートマシンのUpdateを行う
		//この中でステートの切り替えが行われる
		m_StateMachine->Update();
	}

	void StartCameraman::ToGoalEnterBehavior(Vec3 startPos, Vec3 goalPos) {
		m_StartPos = Vec3(startPos.x , startPos.y + 20.0f, startPos.z - 5.0f);
		m_EndPos = Vec3(goalPos.x, 10.0f, goalPos.z - 5.0f);
		m_AtStartPos = Vec3(startPos.x, 0.0f, startPos.z);
		m_AtEndPos = Vec3(goalPos.x, 0.0f, goalPos.z);
		m_AtPos = m_AtStartPos;
		m_TotalTime = 0.0f;
	}

	void StartCameraman::ToStartEnterBehavior(Vec3 startPos, Vec3 goalPos) {
		m_StartPos = Vec3(startPos.x, 10.0f, startPos.z - 5.0f);
		m_EndPos = Vec3(goalPos.x, 20.0f, goalPos.z - 5.0f);
		m_AtStartPos = Vec3(startPos.x, 0.0f, startPos.z);
		m_AtEndPos = Vec3(goalPos.x, 0.0f, goalPos.z);
		m_AtPos = m_AtStartPos;
		m_TotalTime = 0.0f;
	}

	bool StartCameraman::ExcuteBehavior(float totaltime) {
		float ElapsedTime = App::GetApp()->GetElapsedTime();
		m_TotalTime += ElapsedTime;
		if (m_TotalTime > totaltime) {
			return true;
		}
		Easing<Vec3> easing;
		auto TgtPos = easing.EaseInOut(EasingType::Cubic, m_StartPos, m_EndPos, m_TotalTime, totaltime);
		m_AtPos = easing.EaseInOut(EasingType::Cubic, m_AtStartPos, m_AtEndPos, m_TotalTime, totaltime);
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetPosition(TgtPos);
		return false;
	}

	void StartCameraman::EndStateEnterBehavior() {
		auto ptrGameGtage = GetTypeStage<GameStage>();
		ptrGameGtage->ToMyCamera();
		//App::GetApp()->GetScene<Scene>()->SetToMyCameraFlag(true);
	}




	//--------------------------------------------------------------------------------------
	//	class StartCameramanToGoalState : public ObjState<StartCameraman>;
	//--------------------------------------------------------------------------------------
	shared_ptr<StartCameramanToGoalState> StartCameramanToGoalState::Instance() {
		static shared_ptr<StartCameramanToGoalState> instance(new StartCameramanToGoalState);
		return instance;
	}
	void StartCameramanToGoalState::Enter(const shared_ptr<StartCameraman>& Obj) {

		Obj->SetStartCameraPos(App::GetApp()->GetScene<Scene>()->GetStartCameraPos(), App::GetApp()->GetScene<Scene>()->GetEndCameraPos());
		Obj->ToGoalEnterBehavior(Obj->GetPlayerPos(), Obj->GetGoalPos());
	}
	void StartCameramanToGoalState::Execute(const shared_ptr<StartCameraman>& Obj) {
		if (Obj->ExcuteBehavior(2.5f)) {
			Obj->GetStateMachine()->ChangeState(StartCameramanToStartState::Instance());
		}
	}
	void StartCameramanToGoalState::Exit(const shared_ptr<StartCameraman>& Obj) {
	}
	//--------------------------------------------------------------------------------------
	//	class StartCameramanToStartState : public ObjState<StartCameraman>;
	//--------------------------------------------------------------------------------------
	shared_ptr<StartCameramanToStartState> StartCameramanToStartState::Instance() {
		static shared_ptr<StartCameramanToStartState> instance(new StartCameramanToStartState);
		return instance;
	}
	void StartCameramanToStartState::Enter(const shared_ptr<StartCameraman>& Obj) {
		Obj->ToStartEnterBehavior(Obj->GetGoalPos(), Obj->GetPlayerPos());
	}
	void StartCameramanToStartState::Execute(const shared_ptr<StartCameraman>& Obj) {
		if (Obj->ExcuteBehavior(2.5f)) {
			Obj->GetStateMachine()->ChangeState(StartCameramanEndState::Instance());
		}
	}
	void StartCameramanToStartState::Exit(const shared_ptr<StartCameraman>& Obj) {
	}

	//--------------------------------------------------------------------------------------
	//	class StartCameramanEndState : public ObjState<StartCameraman>;
	//--------------------------------------------------------------------------------------
	shared_ptr<StartCameramanEndState> StartCameramanEndState::Instance() {
		static shared_ptr<StartCameramanEndState> instance(new StartCameramanEndState);
		return instance;
	}
	void StartCameramanEndState::Enter(const shared_ptr<StartCameraman>& Obj) {
		Obj->EndStateEnterBehavior();
	}
	void StartCameramanEndState::Execute(const shared_ptr<StartCameraman>& Obj) {
	}
	void StartCameramanEndState::Exit(const shared_ptr<StartCameraman>& Obj) {
	}
}
//end basecross