/*!
@file MyCamera.cpp
@brief ÉJÉÅÉâ
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

	void MyCamera::SetEye(float x, float y, float z) {
		Camera::SetEye(x, y, z);
		//UpdateArmLengh();
	}

	//StartCamera::StartCamera() :
	//	Camera(),
	//	m_RadY(0.5f),
	//	m_RadXZ(0.0f),
	//	m_CameraUnderRot(0.1f),
	//	m_ArmLen(5.0f),
	//	m_MaxArm(20.0f),
	//	m_MinArm(2.0f),
	//	m_RotSpeed(1.0f),
	//	m_ZoomSpeed(0.1f)
	//{
	//};

	//void StartCamera::SetEye(const bsm::Vec3& Eye) {
	//
	//};
}
//end basecross